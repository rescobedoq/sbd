#include "UsuariosView.h"
#include "ui_UsuariosView.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QVector>
#include <QMessageBox>
#include "../Models/usuario.h"
#include "../Controllers/BibliotecaFacade.h"
#include "UsuarioForm.h"

UsuariosView::UsuariosView(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::UsuariosView)
{
    ui->setupUi(this);
    auto facade = BibliotecaFacade::obtenerInstancia();
    ui->tblUsuarios->setColumnCount(2);
    ui->tblUsuarios->setHorizontalHeaderLabels(
        {"ID", "Nombre"}
    );
    cargarTabla(facade->usuarios()->obtenerUsuarios());

    QHeaderView *header = ui->tblUsuarios->horizontalHeader();
    ui->tblUsuarios->setColumnWidth(0, 50);
    header->setSectionResizeMode(QHeaderView::Fixed);
    header->setSectionResizeMode(1, QHeaderView::Stretch);
}

void UsuariosView::cargarTabla(const QVector<std::shared_ptr<Usuario>>& usuarios) {
    ui->tblUsuarios->setRowCount(0);

    for (auto &u : usuarios)
    {
        int row = ui->tblUsuarios->rowCount();  // siguiente fila
        ui->tblUsuarios->insertRow(row);
        ui->tblUsuarios->setItem(row, 0, new QTableWidgetItem(QString::number(u->getId())));
        ui->tblUsuarios->setItem(row, 1, new QTableWidgetItem(u->getNombre()));
    }
}

void UsuariosView::on_btnNuevoUsuario_clicked() {
    UsuarioForm *form = new UsuarioForm(1);
    connect(form, &UsuarioForm::usuarioActualizado, this, [this]() {
        ui->txtBuscarNombre->clear();
        auto facade = BibliotecaFacade::obtenerInstancia();
        cargarTabla(facade->usuarios()->obtenerUsuarios());
    });
    form->show();
}

void UsuariosView::on_btnEditarUsuario_clicked() {
    auto facade = BibliotecaFacade::obtenerInstancia();
    int fila = ui->tblUsuarios->currentRow();
    if (fila < 0) return;
    std::shared_ptr<Usuario> usuarioSeleccionado = facade->usuarios()->obtenerUsuarioPorIndice(fila);
    UsuarioForm *form = new UsuarioForm(2, usuarioSeleccionado);
    connect(form, &UsuarioForm::usuarioActualizado, this, [this]() {
        ui->txtBuscarNombre->clear();
        auto facade = BibliotecaFacade::obtenerInstancia();
        cargarTabla(facade->usuarios()->obtenerUsuarios());
    });
    form->show();
}

void UsuariosView::on_btnEliminarUsuario_clicked() {
    int fila = ui->tblUsuarios->currentRow();

    if (fila < 0) {
        QMessageBox::warning(this, "Advertencia", "Selecciona un usuario de la tabla");
        return;
    }

    // Obtener ID de la celda
    int id = ui->tblUsuarios->item(fila, 0)->text().toInt();
    QString nombre = ui->tblUsuarios->item(fila, 1)->text();

    // Confirmación
    QMessageBox::StandardButton respuesta = QMessageBox::question(
        this,
        "Confirmar eliminación",
        QString("¿Estás seguro de eliminar al usuario '%1'?").arg(nombre),
        QMessageBox::Yes | QMessageBox::No
        );

    if (respuesta != QMessageBox::Yes) {
        return;
    }

    // Eliminar con validaciones
    auto facade = BibliotecaFacade::obtenerInstancia();
    auto resultado = facade->eliminarUsuario(id);

    if (resultado.exito) {
        QMessageBox::information(this, "Éxito", resultado.mensaje);
        QString filtro = ui->txtBuscarNombre->text().trimmed();
        if (filtro.isEmpty()) {
            cargarTabla(facade->usuarios()->obtenerUsuarios());
        } else {
            cargarTabla(facade->usuarios()->buscarUsuario(filtro));
        }
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

void UsuariosView::on_btnBuscarUsuario_clicked(){
    QString texto = ui->txtBuscarNombre->text().trimmed();

    if (texto.isEmpty()) {
        QMessageBox::warning(this, "Advertencia", "Ingrese un nombre para buscar");
        return;
    }

    auto facade = BibliotecaFacade::obtenerInstancia();
    auto resultados = facade->usuarios()->buscarUsuario(texto);

    if (resultados.isEmpty()) {
        QMessageBox::information(this, "Sin resultados",
                                 QString("No se encontraron usuarios con '%1'").arg(texto));
        return;
    }

    cargarTabla(resultados);
}

void UsuariosView::on_btnRecargar_clicked(){
    auto facade = BibliotecaFacade::obtenerInstancia();
    cargarTabla(facade->usuarios()->obtenerUsuarios());
}

UsuariosView::~UsuariosView() {
    delete ui;
}
