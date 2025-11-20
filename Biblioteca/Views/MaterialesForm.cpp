#include "MaterialesForm.h"
#include "ui_MaterialesForm.h"
#include <QMessageBox>

MaterialesForm::MaterialesForm(MaterialController* controller, int tipo, std::shared_ptr<Material> m, QWidget *parent) :
    QWidget(parent), controllerMaterial(controller), tipoVentana(tipo), material(m),
    ui(new Ui::MaterialesForm)
{
    ui->setupUi(this);
    if (tipo == 1) {
        setWindowTitle("Registrar nuevo Material");
        ui->accionMaterialButton->setText("Crear");
    } else if (tipo == 2) {
        setWindowTitle("Editar usuario");
        ui->accionMaterialButton->setText("Guardar");
        ui->txtIDMaterial->setText(QString::number(material->getID()));
        ui->txtTipMaterial->setText(material->obtenerTipo());
        ui->txtTituloMaterial->setText(material->getTitulo());
        ui->txtAutorMaterial->setText(material->getAutor());
        ui->txtAnioMaterial->setText(QString::number(material->getAnio()));
        ui->txtDisponibleMaterial->setText(material->getDisponible()?"Si":"No");
        ui->txtIDMaterial->setReadOnly(true);
        ui->txtIDMaterial->setEnabled(false);
        ui->txtIDMaterial->setFocusPolicy(Qt::NoFocus);
    }
}


MaterialesForm::~MaterialesForm()
{
    delete ui;
}
void MaterialesForm::on_accionMaterialButton_clicked()
{
    QString titulo = ui->txtTituloMaterial->text().trimmed();
    QString autor = ui->txtAutorMaterial->text().trimmed();
    QString anioStr = ui->txtAnioMaterial->text().trimmed();
    QString disponible = ui->txtDisponibleMaterial->text().trimmed();

    // Validaciones básicas
    if (titulo.isEmpty() || autor.isEmpty() || anioStr.isEmpty()) {
        QMessageBox::warning(this, "Error", "Todos los campos son obligatorios");
        return;
    }

    bool ok;
    int anio = anioStr.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Error", "El año debe ser un número válido");
        return;
    }

    if (tipoVentana == 1) {
        // Crear nuevo material
        QString tipoStr = ui->txtTipMaterial->text().trimmed();
        int tipoNum = 0;

        if (tipoStr == "Libro") tipoNum = 1;
        else if (tipoStr == "Revista") tipoNum = 2;
        else if (tipoStr == "Tesis") tipoNum = 3;
        else {
            QMessageBox::warning(this, "Error", "Tipo de material no válido (Libro/Revista/Tesis)");
            return;
        }

        auto nuevoMaterial = controllerMaterial->crearMaterial(tipoNum, titulo, autor, anio, disponible);

        if (nuevoMaterial) {
            QMessageBox::information(this, "Éxito", "Material creado correctamente");
            emit materialActualizado();
            close();
        } else {
            QMessageBox::critical(this, "Error", "No se pudo crear el material");
        }
    }
    else if (tipoVentana == 2) {
        // Actualizar material existente
        if (material) {
            bool exito = controllerMaterial->actualizarMaterial(
                material->getID(), titulo, autor, anio, disponible
                );

            if (exito) {
                QMessageBox::information(this, "Éxito", "Material actualizado correctamente");
                emit materialActualizado();
                close();
            } else {
                QMessageBox::critical(this, "Error", "No se pudo actualizar el material");
            }
        }
    }
}

void MaterialesForm::on_cancelarMaterialButton_clicked()
{
    close();
}
