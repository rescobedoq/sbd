#include "PrestamoForm.h"
#include "ui_PrestamoForm.h"
#include <QMessageBox>

PrestamoForm::PrestamoForm(PrestamoController* controller, QWidget *parent) :
    QWidget(parent), controllerPrestamo(controller),
    ui(new Ui::PrestamoForm)
{
    ui->setupUi(this);
}

PrestamoForm::~PrestamoForm()
{
    delete ui;
}

void PrestamoForm::on_btnRegistrarPrestamo_clicked(){
    QMessageBox::information(this, "Prestamo registrado", "El prestamo se registro correctamente."); // Cierra el diálogo
}

void PrestamoForm::on_btnCancelarPrestamo_clicked(){
    close(); // Cierra el diálogo
}
