#include "UsuarioForm.h"
#include "ui_UsuarioForm.h"
#include <QMessageBox>
// int tipo, std::shared_ptr<Usuario> u, QWidget *parent = nullptr
UsuarioForm::UsuarioForm(UsuarioController* controller, int tipo, std::shared_ptr<Usuario> u, QWidget *parent) :
    QWidget(parent), controllerUsuario(controller), tipoVentana(tipo), usuario(u),
    ui(new Ui::UsuarioForm)
{
    ui->setupUi(this);
    if (tipo == 1) {
        setWindowTitle("Registrar nuevo usuario");
        ui->btnAccionUsuario->setText("Crear");
    } else if (tipo == 2) {
        setWindowTitle("Editar usuario");
        ui->btnAccionUsuario->setText("Guardar");
        ui->txtIDUsuario->setText(QString::number(usuario->getId()));
        ui->txtNombreUsuario->setText(usuario->getNombre());
    }
}

UsuarioForm::~UsuarioForm()
{
    delete ui;
}

void UsuarioForm::on_btnAccionUsuario_clicked(){
    QString nombre = ui->txtNombreUsuario->text();
    int id = ui->txtIDUsuario->text().toInt();
    if (ui->txtIDUsuario->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Campo requerido", "El ID es obligatorio");
        ui->txtIDUsuario->setFocus();
        return;  // No llama al controller
    }

    if (ui->txtNombreUsuario->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Campo requerido", "El nombre es obligatorio");
        ui->txtNombreUsuario->setFocus();
        return;
    }
    if (tipoVentana == 1) {
        if(controllerUsuario->agregarUsuario(id, nombre)){
            QMessageBox::information(this, "Usuario creado", "El usuario se agregó correctamente.");
        } else {
            QMessageBox::warning(this, "Error al crear", "No se pudo crear nuevo usuario");
        }

    } else if (tipoVentana == 2) {
       qDebug() << "llamando a actulizarUsuario():";
        QMessageBox::information(this, "Usuario actualizado", "Los cambios fueron guardados.");
    }
    emit usuarioActualizado();
    close();
}

void UsuarioForm::on_btnCancelarUsuario_clicked(){
    close(); // Cierra el diálogo
}
