#include "PrestamoForm.h"
#include "ui_PrestamoForm.h"
#include <QMessageBox>

PrestamoForm::PrestamoForm(PrestamoController& controller, UsuarioController& usuarioCtrl, MaterialController& materialCtrl, QWidget *parent) :
    QDialog(parent), controllerPrestamo(controller), controllerUsuario(usuarioCtrl), controllerMaterial(materialCtrl),
    ui(new Ui::PrestamoForm)
{
    ui->setupUi(this);
    QVector<std::shared_ptr<Usuario>> usuariosRef = controllerUsuario.obtenerUsuarios();
    QVector<std::shared_ptr<Material>> materialesRef = controllerMaterial.listarMateriales();
    for (const auto& u : usuariosRef) {
        ui->cmbUsuarios->addItem(u->getNombre());
    }
    for (const auto& m : materialesRef) {
        ui->cmbMateriales->addItem(m->getTitulo());
    }
    QDate hoy = QDate::currentDate();
    ui->dteFechaPrestamo->setDate(hoy);
    ui->dteFechaPrestamo->setReadOnly(true);
    ui->dteFechaLimite->setDate(hoy);
    ui->dteFechaLimite->setCalendarPopup(true);
    ui->dteFechaLimite->setMinimumDate(hoy);
    ui->dteFechaLimite->setMaximumDate(hoy.addYears(1));
}

PrestamoForm::~PrestamoForm()
{
    delete ui;
}

void PrestamoForm::on_btnRegistrarPrestamo_clicked(){
    int indiceU = ui->cmbUsuarios->currentIndex();
    int indiceM = ui->cmbMateriales->currentIndex();
    if (indiceU < 0 || indiceM < 0) return; // nada seleccionado
    std::shared_ptr<Usuario> usuarioSeleccionado = controllerUsuario.obtenerUsuarios()[indiceU];
    std::shared_ptr<Material> materialSeleccionado = controllerMaterial.listarMateriales()[indiceM];
    QDate fechaPrestamo = ui->dteFechaPrestamo->date();
    QDate fechaLimite = ui->dteFechaLimite->date();
    if(controllerPrestamo.crearPrestamo(usuarioSeleccionado->getId(),
                                        materialSeleccionado->getID(),
                                        usuarioSeleccionado->getNombre(),
                                        materialSeleccionado->getTitulo(),
                                        fechaPrestamo, fechaLimite))
    {
        qDebug() << "Creado correctamente.";
        QMessageBox::information(this, "Prestamo creado", "El prestamo se creo correctamente.");
        emit prestamoCreado();
        close();
    } else {
        QMessageBox::warning(this, "Error al crear", "No se pudo crear el usuario");
    }
}

void PrestamoForm::on_btnCancelarPrestamo_clicked(){
    close(); // Cierra el diálogo
}
