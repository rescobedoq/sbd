#include "MaterialesForm.h"
#include "ui_MaterialesForm.h"
#include "../Models/Libro.h"
#include "../Models/Revista.h"
#include "../Models/Tesis.h"
#include <QMessageBox>
#include "../Controllers/BibliotecaFacade.h"

MaterialesForm::MaterialesForm(int tipo, std::shared_ptr<Material> m, QWidget *parent) :
    QWidget(parent), tipoVentana(tipo), material(m),
    ui(new Ui::MaterialesForm)
{
    ui->setupUi(this);

    // Asegurarse de que el ComboBox tenga las opciones
    ui->comboTipoMaterial->clear();
    ui->comboTipoMaterial->addItem("Libro");
    ui->comboTipoMaterial->addItem("Revista");
    ui->comboTipoMaterial->addItem("Tesis");

    // Conectar señal del ComboBox usando lambda
    connect(ui->comboTipoMaterial, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this](int index) {
                // Cambiar la etiqueta según el tipo seleccionado
                switch(index) {
                case 0: // Libro
                    ui->labelExtra->setText("Género");
                    ui->txtExtraMaterial->setPlaceholderText("Ej: Ficción, Biografía, etc.");
                    break;
                case 1: // Revista
                    ui->labelExtra->setText("Volumen");
                    ui->txtExtraMaterial->setPlaceholderText("Ej: 1, 2, 3, etc.");
                    break;
                case 2: // Tesis
                    ui->labelExtra->setText("Universidad");
                    ui->txtExtraMaterial->setPlaceholderText("Ej: Universidad Nacional, etc.");
                    break;
                }

                // Limpiar el campo extra al cambiar de tipo (solo en modo crear)
                if (tipoVentana == 1) {
                    ui->txtExtraMaterial->clear();
                }
            });

    if (tipo == 1) {
        // Crear nuevo material
        setWindowTitle("Registrar nuevo Material");
        ui->accionMaterialButton->setText("Crear");

        // Solo bloquear el ID (es auto-generado)
        ui->txtIDMaterial->setReadOnly(true);
        ui->txtIDMaterial->setEnabled(false);
        ui->txtIDMaterial->setText("Auto");

        // ComboBox HABILITADO para seleccionar tipo
        ui->comboTipoMaterial->setEnabled(true);
        ui->comboTipoMaterial->setCurrentIndex(0); // Seleccionar "Libro" por defecto

        // Por defecto mostrar "Género" para Libro
        ui->labelExtra->setText("Género");
        ui->txtExtraMaterial->setPlaceholderText("Ej: Ficción, Biografía, etc.");

        // Por defecto disponible = true
        ui->checkDisponible->setEnabled(false);
        ui->checkDisponible->setChecked(true);
    }
    else if (tipo == 2) {
        // Editar material existente
        setWindowTitle("Editar Material");
        ui->accionMaterialButton->setText("Guardar");

        if (material) {
            ui->txtIDMaterial->setText(QString::number(material->getId()));
            ui->txtTituloMaterial->setText(material->getTitulo());
            ui->txtAutorMaterial->setText(material->getAutor());
            ui->txtAnioMaterial->setText(QString::number(material->getAnio()));

            // Configurar tipo y campo extra según el material
            QString tipoMaterial = material->obtenerTipo();

            if (tipoMaterial == "Libro") {
                ui->comboTipoMaterial->setCurrentIndex(0);
                auto libro = std::dynamic_pointer_cast<Libro>(material);
                ui->txtExtraMaterial->setText(libro->getGenero());
                ui->labelExtra->setText("Género");
            }
            else if (tipoMaterial == "Revista") {
                ui->comboTipoMaterial->setCurrentIndex(1);
                auto revista = std::dynamic_pointer_cast<Revista>(material);
                ui->txtExtraMaterial->setText(QString::number(revista->getVolumen()));
                ui->labelExtra->setText("Volumen");
            }
            else if (tipoMaterial == "Tesis") {
                ui->comboTipoMaterial->setCurrentIndex(2);
                auto tesis = std::dynamic_pointer_cast<Tesis>(material);
                ui->txtExtraMaterial->setText(tesis->getUniversidad());
                ui->labelExtra->setText("Universidad");
            }

            // Configurar disponibilidad
            ui->checkDisponible->setEnabled(false);
            ui->checkDisponible->setChecked(material->getDisponible());

            ui->txtIDMaterial->setReadOnly(true);
            ui->txtIDMaterial->setEnabled(false);
            ui->comboTipoMaterial->setEnabled(false); // No permitir cambiar tipo al editar
        }
    }
}

MaterialesForm::~MaterialesForm()
{
    delete ui;
}

void MaterialesForm::on_accionMaterialButton_clicked()
{
    auto facade = BibliotecaFacade::obtenerInstancia();
    QString titulo = ui->txtTituloMaterial->text().trimmed();
    QString autor = ui->txtAutorMaterial->text().trimmed();
    QString anioStr = ui->txtAnioMaterial->text().trimmed();
    QString extra = ui->txtExtraMaterial->text().trimmed();
    bool disponible = ui->checkDisponible->isChecked();

    // Validaciones básicas
    if (titulo.isEmpty() || autor.isEmpty() || anioStr.isEmpty() || extra.isEmpty()) {
        QMessageBox::warning(this, "Error", "Todos los campos son obligatorios");
        return;
    }

    bool ok;
    int anio = anioStr.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Error", "El año debe ser un número válido");
        return;
    }

    // Validación específica para Revista (volumen debe ser número)
    int tipoIndex = ui->comboTipoMaterial->currentIndex();
    if (tipoIndex == 1) { // Revista
        int volumen = extra.toInt(&ok);
        if (!ok || volumen <= 0) {
            QMessageBox::warning(this, "Error", "El volumen debe ser un número válido mayor a 0");
            return;
        }
    }

    if (tipoVentana == 1) {
        // Crear nuevo material
        // Convertir índice del combo a tipo numérico: 0=Libro(1), 1=Revista(2), 2=Tesis(3)
        int tipoNum = tipoIndex + 1;
        if (facade->materiales()->crearMaterial(tipoNum, titulo, autor, anio, extra, disponible)) {
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
            bool exito = facade->materiales()->actualizarMaterial(
                material->getId(), titulo, autor, anio, extra, disponible
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
