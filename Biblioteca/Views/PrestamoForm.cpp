#include "PrestamoForm.h"
#include "ui_PrestamoForm.h"
#include <QMessageBox>
#include "../Controllers/BibliotecaFacade.h"

PrestamoForm::PrestamoForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrestamoForm)
{
    ui->setupUi(this);
    auto facade = BibliotecaFacade::obtenerInstancia();

    auto usuariosRef = facade->usuarios()->obtenerUsuarios();
    auto materialesRef = facade->materiales()->obtenerMaterialesDisponibles();
    for (const auto& u : usuariosRef) {
        ui->cmbUsuarios->addItem(u->getNombre(), u->getId());
    }
    for (const auto& m : materialesRef) {
        ui->cmbMateriales->addItem(m->getTitulo(), m->getId());
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

    if (indiceU < 0 || indiceM < 0){
        QMessageBox::warning(this, "Advertencia", "Por favor selecciona un usuario y un material");
        return;
    }
    int usuarioId = ui->cmbUsuarios->currentData().toInt();
    int materialId = ui->cmbMateriales->currentData().toInt();
    QString nombreUsuario = ui->cmbUsuarios->currentText();
    QString nombreMaterial = ui->cmbMateriales->currentText();
    QDate fechaPrestamo = ui->dteFechaPrestamo->date();
    QDate fechaLimite = ui->dteFechaLimite->date();

    auto facade = BibliotecaFacade::obtenerInstancia();
    auto resultado = facade->realizarPrestamo(usuarioId, materialId, nombreUsuario, nombreMaterial,
                                              fechaPrestamo, fechaLimite);

    if (resultado.exito) {
        QMessageBox::information(this, "Éxito", resultado.mensaje);
        // Para filtros
        /*QString filtro = ui->txtBuscarNombre->text().trimmed();
        if (filtro.isEmpty()) {
            cargarTabla(facade->prestamos()->obtenerPrestamos());
        } else {
            cargarTabla(facade->prestamos()->buscarUsuario(filtro));
        }*/
        emit prestamoCreado();
        close();
    } else {
        QString mensaje = resultado.mensaje + "\n\n";
        QMessageBox::warning(this, "No se puede registrar el prestamos", mensaje);
    }
}

void PrestamoForm::on_btnCancelarPrestamo_clicked(){
    close(); // Cierra el diálogo
}
