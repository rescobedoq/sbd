#include "Prestamos.h"
#include "ui_Prestamos.h"
#include "PrestamoForm.h"
#include <QMessageBox>

Prestamos::Prestamos(PrestamoController& controller, UsuarioController& usuarioCtrl, MaterialController& materialCtrl, QWidget *parent)
    : QWidget(parent), controllerPrestamo(controller), controllerUsuario(usuarioCtrl), controllerMaterial(materialCtrl),
      ui(new Ui::Prestamos)
{
    ui->setupUi(this);
    cargarTabla();
}

void Prestamos::cargarTabla(){
    QVector<std::shared_ptr<Prestamo>> prestamosRef = controllerPrestamo.obtenerPrestamos();

    // Configura la tabla
    ui->tblPrestamos->setColumnCount(7);
    ui->tblPrestamos->setHorizontalHeaderLabels(
        {"ID", "Usuario", "Material", "F. Prestamo", "F. Limite", "Devuelto", "F. Devolucion"}
        );
    ui->tblPrestamos->setRowCount(prestamosRef.size());

    // Llenar tabla
    for (int i = 0; i < prestamosRef.size(); ++i) {
        std::shared_ptr<Prestamo> p = prestamosRef[i];
        ui->tblPrestamos->setItem(i, 0, new QTableWidgetItem(QString::number(p->getId())));
        ui->tblPrestamos->setItem(i, 1, new QTableWidgetItem(p->getNombreUsuario()));
        ui->tblPrestamos->setItem(i, 2, new QTableWidgetItem(p->getNombreMaterial()));
        ui->tblPrestamos->setItem(i, 3, new QTableWidgetItem(p->getFechaPrestamo().toString("yyyy-MM-dd")));
        ui->tblPrestamos->setItem(i, 4, new QTableWidgetItem(p->getFechaLimiteDevolucion().toString("yyyy-MM-dd")));
        ui->tblPrestamos->setItem(i, 5, new QTableWidgetItem(p->estaDevuelto()? "Si":"No" ));
        ui->tblPrestamos->setItem(i, 6, new QTableWidgetItem(p->getFechaDevolucion().toString("yyyy-MM-dd")));
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
    PrestamoForm *form = new PrestamoForm(controllerPrestamo, controllerUsuario, controllerMaterial, this);
    connect(form, &PrestamoForm::prestamoCreado, this, &Prestamos::cargarTabla);

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

    std::shared_ptr<Prestamo> prestamoSel = controllerPrestamo.obtenerPrestamos()[row];
    QMessageBox::StandardButton respuesta = QMessageBox::question(
        this,
        "Confirmar devolucion",
        QString("¿Estás seguro de registrar la devolucion del material '%1' prestado al usuario '%2'?").arg(prestamoSel->getNombreMaterial(), prestamoSel->getNombreUsuario()),
        QMessageBox::Yes | QMessageBox::No
    );
    if (respuesta == QMessageBox::Yes) {
        if (controllerPrestamo.registrarDevolucion(prestamoSel->getId(), QDate::currentDate())) {
            QMessageBox::information(this, "Éxito", "Devolucion registrada correctamente");
            cargarTabla();
        } else {
            QMessageBox::critical(this, "Error", "No se pudo registrar la devolucion");
        }
    }
}
