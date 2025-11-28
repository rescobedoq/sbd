#include "Materiales.h"
#include "ui_Materiales.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QVector>
#include <QMessageBox>
#include "MaterialesForm.h"
#include "../Controllers/BibliotecaFacade.h"

Materiales::Materiales(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Materiales)
{
    ui->setupUi(this);
    auto facade = BibliotecaFacade::obtenerInstancia();
    // Configura la tabla
    ui->tablaMateriales->setColumnCount(6);
    ui->tablaMateriales->setHorizontalHeaderLabels(
        {"ID", "Tipo", "Título", "Autor", "Año", "Disponible"}
        );

    cargarTabla(facade->materiales()->obtenerMateriales());

    ui->tablaMateriales->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    ui->tablaMateriales->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tablaMateriales->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QHeaderView *header = ui->tablaMateriales->horizontalHeader();

    header->setSectionResizeMode(QHeaderView::Fixed);   // Todas fijas por defecto
    header->setSectionResizeMode(2, QHeaderView::Stretch);
    header->setSectionResizeMode(3, QHeaderView::Stretch);

}

void Materiales::cargarTabla(const QVector<std::shared_ptr<Material>>& materiales) {
    ui->tablaMateriales->setRowCount(0);

    for (auto &m : materiales)
    {
        int row = ui->tablaMateriales->rowCount();  // siguiente fila
        ui->tablaMateriales->insertRow(row);

        ui->tablaMateriales->setItem(row, 0, new QTableWidgetItem(QString::number(m->getId())));
        ui->tablaMateriales->setItem(row, 1, new QTableWidgetItem(m->obtenerTipo()));
        ui->tablaMateriales->setItem(row, 2, new QTableWidgetItem(m->getTitulo()));
        ui->tablaMateriales->setItem(row, 3, new QTableWidgetItem(m->getAutor()));
        ui->tablaMateriales->setItem(row, 4, new QTableWidgetItem(QString::number(m->getAnio())));
        ui->tablaMateriales->setItem(row, 5, new QTableWidgetItem(m->getDisponible() ? "Sí" : "No"));
    }
    ui->tablaMateriales->resizeColumnsToContents();
    ui->tablaMateriales->resizeRowsToContents();

    // Ajustar layout y ventana al nuevo contenido
    layout()->activate();
    adjustSize();
    resize(width() + 20, height());
}


Materiales::~Materiales()
{
    delete ui;
}

void Materiales::on_crearMaterialButton_clicked(){
    MaterialesForm *form=new MaterialesForm(1);
    connect(form, &MaterialesForm::materialActualizado, this, [this]() {
        //Si es que se aplican filtros
        //ui->txtBuscarNombre->clear();
        auto facade = BibliotecaFacade::obtenerInstancia();
        cargarTabla(facade->materiales()->obtenerMateriales());
    });
    form->show();
}

void Materiales::on_editarMaterialButton_clicked(){
    auto facade = BibliotecaFacade::obtenerInstancia();
    int row = ui->tablaMateriales->currentRow();

    if (row < 0) {
        QMessageBox::warning(this, "Advertencia", "Por favor selecciona un material de la tabla");
        return;
    }

    std::shared_ptr<Material> materialSeleccionado = facade->materiales()->obtenerMaterialPorIndice(row);
    MaterialesForm *form = new MaterialesForm(2, materialSeleccionado);
    connect(form, &MaterialesForm::materialActualizado, this, [this]() {
        //Si es que se aplican filtros
        //ui->txtBuscarNombre->clear();
        auto facade = BibliotecaFacade::obtenerInstancia();
        cargarTabla(facade->materiales()->obtenerMateriales());
    });
    form->show();
}

void Materiales::on_eliminarMaterialButton_clicked(){
    int row = ui->tablaMateriales->currentRow();

    if (row < 0) {
        QMessageBox::warning(this, "Advertencia", "Por favor selecciona un material de la tabla");
        return;
    }

    // Obtener ID de la celda
    int id = ui->tablaMateriales->item(row, 0)->text().toInt();
    QString nombre = ui->tablaMateriales->item(row, 1)->text();

    // Confirmación
    QMessageBox::StandardButton respuesta = QMessageBox::question(
        this,
        "Confirmar eliminación",
        QString("¿Estás seguro de eliminar el material '%1'?").arg(nombre),
        QMessageBox::Yes | QMessageBox::No
        );

    if (respuesta != QMessageBox::Yes) {
        return;
    }

    // Eliminar con validaciones
    auto facade = BibliotecaFacade::obtenerInstancia();
    auto resultado = facade->eliminarMaterial(id);

    if (resultado.exito) {
        QMessageBox::information(this, "Éxito", resultado.mensaje);
        // Para filtros
        /*QString filtro = ui->txtBuscarNombre->text().trimmed();
        if (filtro.isEmpty()) {
            cargarTabla(facade->usuarios()->obtenerUsuarios());
        } else {
            cargarTabla(facade->usuarios()->buscarUsuario(filtro));
        }*/
        cargarTabla(facade->materiales()->obtenerMateriales());
    } else {
        QString mensaje = resultado.mensaje + "\n\n";
        if (!resultado.prestamosActivos.isEmpty()) {
            mensaje += "Préstamos activos:\n";
            for (const auto& prestamo : resultado.prestamosActivos) {
                mensaje += "• " + prestamo + "\n";
            }
            mensaje += "\nRegistre las devoluciones antes de eliminar.";
        }
        QMessageBox::warning(this, "No se puede eliminar", mensaje);
    }
}

