#include "Prestamos.h"
#include "ui_Prestamos.h"
#include "PrestamoForm.h"

Prestamos::Prestamos(PrestamoController* controller, QWidget *parent)
    : QWidget(parent), controllerPrestamo(controller)
    , ui(new Ui::Prestamos)
{
    ui->setupUi(this);
    cargarTabla();
}

void Prestamos::cargarTabla(){
    QVector<std::shared_ptr<Prestamo>>& prestamosRef = controllerPrestamo->obtenerPrestamos();

    // Configura la tabla
    ui->tblPrestamos->setColumnCount(5);
    ui->tblPrestamos->setHorizontalHeaderLabels(
        {"ID", "Usuario", "Material", "F. Prestamo", "F. Limite"}
        );
    ui->tblPrestamos->setRowCount(prestamosRef.size());

    // Llenar tabla
    for (int i = 0; i < prestamosRef.size(); ++i) {
        std::shared_ptr<Prestamo> p = prestamosRef[i];
        ui->tblPrestamos->setItem(i, 0, new QTableWidgetItem(QString::number(p->getId())));
        ui->tblPrestamos->setItem(i, 1, new QTableWidgetItem(p->getNombreUsuario()));
        ui->tblPrestamos->setItem(i, 2, new QTableWidgetItem(p->getNombreMaterial()));
        ui->tblPrestamos->setItem(i, 3, new QTableWidgetItem(p->getFechaDevolucion().toString("yyyy-MM-dd")));
        ui->tblPrestamos->setItem(i, 4, new QTableWidgetItem(p->getFechaLimiteDevolucion().toString("yyyy-MM-dd")));
    }
    ui->tblPrestamos->resizeColumnsToContents();
    ui->tblPrestamos->resizeRowsToContents();
    ui->tblPrestamos->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    ui->tblPrestamos->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tblPrestamos->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    layout()->activate();   // recalcula el layout
    adjustSize();
    resize(width() + 20, height());

    QHeaderView *header = ui->tblPrestamos->horizontalHeader();

    header->setSectionResizeMode(QHeaderView::Fixed);   // Todas fijas por defecto
    header->setSectionResizeMode(1, QHeaderView::Stretch);
    header->setSectionResizeMode(2, QHeaderView::Stretch);
}

Prestamos::~Prestamos()
{
    delete ui;
}

void Prestamos::on_btnNuevoPrestamo_clicked(){
    PrestamoForm *form = new PrestamoForm(controllerPrestamo);
    connect(form, &PrestamoForm::prestamoActualizado, this, &Prestamos::cargarTabla);

    // Mostrar la ventana
    form->show();
}
void Prestamos::on_btnRegistrarDevolucion_clicked(){

}
