#include "Prestamos.h"
#include "ui_Prestamos.h"
#include "PrestamoForm.h"
#include <QMessageBox>
#include "../Controllers/BibliotecaFacade.h"

Prestamos::Prestamos(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::Prestamos)
{
    ui->setupUi(this);
    auto facade = BibliotecaFacade::obtenerInstancia();
    // Configura la tabla
    ui->tblPrestamos->setColumnCount(7);
    ui->tblPrestamos->setHorizontalHeaderLabels(
        {"ID", "Usuario", "Material", "F. Prestamo", "F. Limite", "Devuelto", "F. Devolucion"}
        );
    cargarTabla(facade->prestamos()->obtenerPrestamos());
    ui->tblPrestamos->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    ui->tblPrestamos->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tblPrestamos->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QHeaderView *header = ui->tblPrestamos->horizontalHeader();

    header->setSectionResizeMode(QHeaderView::Fixed);   // Todas fijas por defecto
    header->setSectionResizeMode(1, QHeaderView::Stretch);
    header->setSectionResizeMode(2, QHeaderView::Stretch);
}

void Prestamos::cargarTabla(const QVector<std::shared_ptr<Prestamo>>& prestamos) {
    ui->tblPrestamos->setRowCount(0);

    // 2️⃣ Recorrer la lista de usuarios y agregarlos a la tabla
    for (auto &p : prestamos)
    {
        int row = ui->tblPrestamos->rowCount();  // siguiente fila
        ui->tblPrestamos->insertRow(row);

        // 3️⃣ Insertar columnas (ID, Nombre, Apellido, Correo)
        ui->tblPrestamos->setItem(row, 0, new QTableWidgetItem(QString::number(p->getId())));
        ui->tblPrestamos->setItem(row, 1, new QTableWidgetItem(p->getNombreUsuario()));
        ui->tblPrestamos->setItem(row, 2, new QTableWidgetItem(p->getNombreMaterial()));
        ui->tblPrestamos->setItem(row, 3, new QTableWidgetItem(p->getFechaPrestamo().toString("yyyy-MM-dd")));
        ui->tblPrestamos->setItem(row, 4, new QTableWidgetItem(p->getFechaLimiteDevolucion().toString("yyyy-MM-dd")));
        ui->tblPrestamos->setItem(row, 5, new QTableWidgetItem(p->estaDevuelto()? "Si":"No" ));
        ui->tblPrestamos->setItem(row, 6, new QTableWidgetItem(p->getFechaDevolucion().toString("yyyy-MM-dd")));
    }
    ui->tblPrestamos->resizeColumnsToContents();
    ui->tblPrestamos->resizeRowsToContents();

    // Ajustar layout y ventana al nuevo contenido
    layout()->activate();
    adjustSize();
    resize(width() + 20, height());
}

Prestamos::~Prestamos()
{
    delete ui;
}

void Prestamos::on_btnNuevoPrestamo_clicked(){
    PrestamoForm *form = new PrestamoForm(this);
    connect(form, &PrestamoForm::prestamoCreado, this, [this]() {
        //Si es que se aplican filtros
        //ui->txtBuscarNombre->clear();
        auto facade = BibliotecaFacade::obtenerInstancia();
        cargarTabla(facade->prestamos()->obtenerPrestamos());
    });

    // Mostrar la ventana
    form->setModal(true);
    form->exec();
}

void Prestamos::on_btnRegistrarDevolucion_clicked(){
    int row = ui->tblPrestamos->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Advertencia", "Por favor selecciona un prestamo de la tabla");
        return;
    }

    int id = ui->tblPrestamos->item(row, 0)->text().toInt();
    QString nombreUsuario = ui->tblPrestamos->item(row, 1)->text();
    QString nombreMaterial = ui->tblPrestamos->item(row, 2)->text();

    QMessageBox::StandardButton respuesta = QMessageBox::question(
        this,
        "Confirmar devolucion",
        QString("¿Estás seguro de registrar la devolucion del material '%1' prestado al usuario '%2'?").arg(nombreMaterial, nombreUsuario),
        QMessageBox::Yes | QMessageBox::No
    );

    if (respuesta != QMessageBox::Yes) {
        return;
    }

    auto facade = BibliotecaFacade::obtenerInstancia();
    auto resultado = facade->devolverPrestamo(id);

    if (resultado.exito) {
        QMessageBox::information(this, "Éxito", resultado.mensaje);
        // Para filtros
        /*QString filtro = ui->txtBuscarNombre->text().trimmed();
        if (filtro.isEmpty()) {
            cargarTabla(facade->prestamos()->obtenerPrestamos());
        } else {
            cargarTabla(facade->prestamos()->buscarUsuario(filtro));
        }*/
        cargarTabla(facade->prestamos()->obtenerPrestamos());
    } else {
        QString mensaje = resultado.mensaje + "\n\n";
        QMessageBox::warning(this, "No se puede registrar la devolucion", mensaje);
    }
}
