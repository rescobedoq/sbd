#include "Usuarios.h"
#include "ui_Usuarios.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QVector>
#include <QMessageBox>
#include "../Models/usuario.h"
#include "UsuarioForm.h"

/*Modificar interfaz y agregar pantallas para incluir:
 * crear usuario
 * detalles del usuario seleccionado
 * modificar usuario seleccionado
 * eliminar usuario seleccionado
*/
Usuarios::Usuarios(UsuarioController* controller, QWidget *parent)
    : QWidget(parent), controllerUsuario(controller)
    , ui(new Ui::Usuarios)
{
    ui->setupUi(this);
    cargarTabla();
}

void Usuarios::cargarTabla() {
    QVector<std::shared_ptr<Usuario>>& usuariosRef = controllerUsuario->obtenerUsuarios();

    // Configura la tabla
    ui->tblUsuarios->setColumnCount(2);
    ui->tblUsuarios->setHorizontalHeaderLabels(
        {"ID", "Nombre"}
        );
    ui->tblUsuarios->setRowCount(usuariosRef.size());

    // Llenar tabla
    for (int i = 0; i < usuariosRef.size(); ++i) {
        std::shared_ptr<Usuario> u = usuariosRef[i];
        ui->tblUsuarios->setItem(i, 0, new QTableWidgetItem(QString::number(u->getId())));
        ui->tblUsuarios->setItem(i, 1, new QTableWidgetItem(u->getNombre()));
    }
    ui->tblUsuarios->resizeColumnsToContents();
    ui->tblUsuarios->resizeRowsToContents();
    ui->tblUsuarios->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    ui->tblUsuarios->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tblUsuarios->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    layout()->activate();   // recalcula el layout
    adjustSize();
    resize(width() + 20, height());

    QHeaderView *header = ui->tblUsuarios->horizontalHeader();

    header->setSectionResizeMode(QHeaderView::Fixed);   // Todas fijas por defecto
    header->setSectionResizeMode(1, QHeaderView::Stretch);
}

void Usuarios::on_btnNuevoUsuario_clicked() {
    // Crear una nueva ventana de detalles
    UsuarioForm *form = new UsuarioForm(controllerUsuario, 1);
    connect(form, &UsuarioForm::usuarioActualizado, this, &Usuarios::cargarTabla);

    // Mostrar la ventana
    form->show();
}

void Usuarios::on_btnEditarUsuario_clicked() {
    int fila = ui->tblUsuarios->currentRow();
    if (fila < 0) return; // nada seleccionado

    std::shared_ptr<Usuario> usuarioSeleccionado = controllerUsuario->obtenerUsuarios()[fila];
    UsuarioForm *form = new UsuarioForm(controllerUsuario, 2, usuarioSeleccionado);
    connect(form, &UsuarioForm::usuarioActualizado, this, &Usuarios::cargarTabla);
    // Mostrar la ventana
    form->show();
}

void Usuarios::on_btnEliminarUsuario_clicked() {
    int fila = ui->tblUsuarios->currentRow();
    if (fila < 0) return; // nada seleccionado

    std::shared_ptr<Usuario> usuarioSeleccionado = controllerUsuario->obtenerUsuarios()[fila];
    if(controllerUsuario->eliminarUsuario(usuarioSeleccionado->getId())){
        QMessageBox::information(this, "Usuario Eliminado", "El usuario se elimino correctamente.");
    } else {
        QMessageBox::warning(this, "Error al eliminar", "No se pudo eliminar el usuario");
    }
    cargarTabla();
}

Usuarios::~Usuarios() {
    delete ui;
}
