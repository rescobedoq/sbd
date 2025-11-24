#include "Materiales.h"
#include "ui_Materiales.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QVector>
#include <QMessageBox>
#include "../Models/material.h"
#include "MaterialesForm.h"

/*
 * Modificar interfaz y agregar pantallas para incluir:
 * crear material
 * detalles del material seleccionado
 * modificar material seleccionado
 * eliminar material seleccionado
*/

Materiales::Materiales(MaterialController* controller, QWidget *parent) :
    QWidget(parent), controllerMaterial(controller),
    ui(new Ui::Materiales)
{
    ui->setupUi(this);
    cargarTabla();

}
void Materiales::cargarTabla(){
    // Obtener lista de materiales desde el controlador
    QVector<std::shared_ptr<Material>> materiales = controllerMaterial->listarMateriales();

    // Configura la tabla
    ui->tablaMateriales->setColumnCount(5);
    ui->tablaMateriales->setHorizontalHeaderLabels(
        {"Tipo", "Título", "Autor", "Año", "Disponible"}
        );
    ui->tablaMateriales->setRowCount(materiales.size());

    // Llenar tabla
    for (int i = 0; i < materiales.size(); ++i) {
        std::shared_ptr<Material> m = materiales[i];

        ui->tablaMateriales->setItem(i, 0, new QTableWidgetItem(m->obtenerTipo()));
        ui->tablaMateriales->setItem(i, 1, new QTableWidgetItem(m->getTitulo()));
        ui->tablaMateriales->setItem(i, 2, new QTableWidgetItem(m->getAutor()));
        ui->tablaMateriales->setItem(i, 3, new QTableWidgetItem(QString::number(m->getAnio())));
        ui->tablaMateriales->setItem(i, 4, new QTableWidgetItem(m->getDisponible() ? "Sí" : "No"));
    }

    // Ajustes visuales
    ui->tablaMateriales->resizeColumnsToContents();
    ui->tablaMateriales->resizeRowsToContents();
    ui->tablaMateriales->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    ui->tablaMateriales->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tablaMateriales->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    layout()->activate();   // recalcula el layout
    adjustSize();
    resize(width() + 20, height());
}

Materiales::~Materiales()
{
    delete ui;
}

void Materiales::on_crearMaterialButton_clicked(){
    MaterialesForm *form=new MaterialesForm(controllerMaterial, 1);
    connect(form, &MaterialesForm::materialActualizado, this, &Materiales::cargarTabla);
    form->show();
}
void Materiales::on_editarMaterialButton_clicked(){
    int row = ui->tablaMateriales->currentRow();

    if (row < 0) {
        QMessageBox::warning(this, "Advertencia", "Por favor selecciona un material de la tabla");
        return;
    }

    QVector<std::shared_ptr<Material>> materiales = controllerMaterial->listarMateriales();

    if (row < materiales.size()) {
        MaterialesForm *form = new MaterialesForm(controllerMaterial, 2, materiales[row]);
        connect(form, &MaterialesForm::materialActualizado, this, &Materiales::cargarTabla);
        form->show();
    }
}

void Materiales::on_eliminarMaterialButton_clicked(){
    int row = ui->tablaMateriales->currentRow();

    if (row < 0) {
        QMessageBox::warning(this, "Advertencia", "Por favor selecciona un material de la tabla");
        return;
    }

    QVector<std::shared_ptr<Material>> materiales = controllerMaterial->listarMateriales();

    if (row < materiales.size()) {
        int id = materiales[row]->getID();
        QString titulo = materiales[row]->getTitulo();

        QMessageBox::StandardButton respuesta = QMessageBox::question(
            this,
            "Confirmar eliminación",
            QString("¿Estás seguro de eliminar el material '%1'?").arg(titulo),
            QMessageBox::Yes | QMessageBox::No
            );

        if (respuesta == QMessageBox::Yes) {
            if (controllerMaterial->eliminarMaterial(id)) {
                QMessageBox::information(this, "Éxito", "Material eliminado correctamente");
                cargarTabla();
            } else {
                QMessageBox::critical(this, "Error", "No se pudo eliminar el material");
            }
        }
    }
}

