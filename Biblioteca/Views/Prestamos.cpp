#include "Prestamos.h"
#include "ui_Prestamos.h"
#include "PrestamoForm.h"
#include "../Controllers/BibliotecaFacade.h"
#include <QMessageBox>
#include <QDebug>
#include <QTableWidgetItem>
#include <QLineEdit> //

// CONSTRUCTOR
// =================================================================
Prestamos::Prestamos(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::Prestamos)
{
    ui->setupUi(this);
    auto facade = BibliotecaFacade::obtenerInstancia();

    // NUEVO: 1. CONEXIÓN DEL CAMPO DE BÚSQUEDA
    // Asumimos que el QLineEdit se llama 'txtBusqueda'
    QLineEdit* txtBusqueda = ui->txtBusqueda;

    if (txtBusqueda) {
        // Conectamos la señal textChanged() al nuevo slot buscarPrestamos()
        connect(txtBusqueda, &QLineEdit::textChanged,
                this, &Prestamos::buscarPrestamos);
    } else {
        qDebug() << "ERROR: No se encontró el campo de búsqueda 'txtBusqueda'. Verifique Prestamos.ui.";
    }
    // 2. Lógica de carga inicial del filtro (llama a la nueva función de filtrado)
    facade->prestamos()->filtrarPrestamos("", 0);
    cargarTablaFiltrada();
}

// =================================================================
// FUNCIÓN DE BÚSQUEDA (NUEVA IMPLEMENTACIÓN)
// =================================================================
void Prestamos::buscarPrestamos() {
    // 1. Obtener el texto de búsqueda y el índice de estado
    QString busqueda = ui->txtBusqueda->text();
    int estadoIndex = ui->comboBox->currentIndex();

    // 2. Llamar al controlador para aplicar ambos filtros
    auto facade = BibliotecaFacade::obtenerInstancia();
    facade->prestamos()->filtrarPrestamos(busqueda, estadoIndex);

    // 3. Recargar la tabla con la nueva lista filtrada
    cargarTablaFiltrada();

    qDebug() << "Búsqueda aplicada. Texto: '" << busqueda << "' Estado Index:" << estadoIndex
             << " Mostrando " << facade->prestamos()->getPrestamosFiltrados().size() << " préstamos.";
}

// FUNCIÓN DE CARGA FILTRADA
// =================================================================
void Prestamos::cargarTablaFiltrada(){
    auto facade = BibliotecaFacade::obtenerInstancia();
    const QList<std::shared_ptr<Prestamo>>& prestamosFiltrados =
        facade->prestamos()->getPrestamosFiltrados();

    // Configura la tabla
    ui->tblPrestamos->setColumnCount(7);
    ui->tblPrestamos->setHorizontalHeaderLabels(
        {"ID", "Usuario", "Material", "F. Prestamo", "F. Limite", "Devuelto", "F. Devolucion"}
        );
    ui->tblPrestamos->setRowCount(prestamosFiltrados.size());

    // Llenar tabla
    for (int i = 0; i < prestamosFiltrados.size(); ++i) {
        std::shared_ptr<Prestamo> p = prestamosFiltrados.at(i);
        QString estadoDevuelto = p->estaDevuelto()? "Si":"No";
        QString fechaDev = p->getFechaDevolucion().isValid() ?
                               p->getFechaDevolucion().toString("yyyy-MM-dd") :
                               "";

        ui->tblPrestamos->setItem(i, 0, new QTableWidgetItem(QString::number(p->getId())));
        ui->tblPrestamos->setItem(i, 1, new QTableWidgetItem(p->getNombreUsuario()));
        ui->tblPrestamos->setItem(i, 2, new QTableWidgetItem(p->getNombreMaterial()));
        ui->tblPrestamos->setItem(i, 3, new QTableWidgetItem(p->getFechaPrestamo().toString("yyyy-MM-dd")));
        ui->tblPrestamos->setItem(i, 4, new QTableWidgetItem(p->getFechaLimiteDevolucion().toString("yyyy-MM-dd")));
        ui->tblPrestamos->setItem(i, 5, new QTableWidgetItem(estadoDevuelto));
        ui->tblPrestamos->setItem(i, 6, new QTableWidgetItem(fechaDev));
    }

    // ... (Tu código de redimensionado de tabla) ...
    ui->tblPrestamos->resizeColumnsToContents();
    ui->tblPrestamos->resizeRowsToContents();
    ui->tblPrestamos->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    ui->tblPrestamos->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tblPrestamos->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    layout()->activate();
    adjustSize();
    resize(width() + 20, height());

    QHeaderView *header = ui->tblPrestamos->horizontalHeader();

    header->setSectionResizeMode(QHeaderView::Fixed);
    header->setSectionResizeMode(1, QHeaderView::Stretch);
    header->setSectionResizeMode(2, QHeaderView::Stretch);
}

// =================================================================
// SLOT DEL FILTRO (MODIFICADO para llamar a buscarPrestamos)
// =================================================================
void Prestamos::on_comboBox_currentIndexChanged(int index) {

    Q_UNUSED(index);
    buscarPrestamos();
}
// DESTRUCTOR Y OTROS SLOTS (Ajustados)
// =================================================================
Prestamos::~Prestamos()
{
    delete ui;
}

void Prestamos::on_btnNuevoPrestamo_clicked(){
    auto facade = BibliotecaFacade::obtenerInstancia();
    PrestamoForm *form = new PrestamoForm(this);
    // Conectar a la lógica unificada de refresco (buscarPrestamos)
    connect(form, &PrestamoForm::prestamoCreado, this, &Prestamos::buscarPrestamos);

    form->setModal(true);
    form->exec();
}
void Prestamos::on_btnRegistrarDevolucion_clicked(){
    int row = ui->tblPrestamos->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Advertencia", "Por favor selecciona un prestamo de la tabla");
        return;
    }

    int id = ui->tblPrestamos->item(row, 0)->text().toInt();
    QString nombreUsuario = ui->tblPrestamos->item(row, 1)->text();
    QString nombreMaterial = ui->tblPrestamos->item(row, 2)->text();

    QMessageBox::StandardButton respuesta = QMessageBox::question(
        this,
        "Confirmar devolucion",
        QString("¿Estás seguro de registrar la devolucion del material '%1' prestado al usuario '%2'?").arg(nombreMaterial, nombreUsuario),
        QMessageBox::Yes | QMessageBox::No
        );

    if (respuesta != QMessageBox::Yes) {
        return;
    }

    auto facade = BibliotecaFacade::obtenerInstancia();
    auto resultado = facade->devolverPrestamo(id);

    if (resultado.exito) {
        QMessageBox::information(this, "Éxito", resultado.mensaje);
        // Para filtros
        /*QString filtro = ui->txtBuscarNombre->text().trimmed();
        if (filtro.isEmpty()) {
            cargarTabla(facade->prestamos()->obtenerPrestamos());
        } else {
            cargarTabla(facade->prestamos()->buscarUsuario(filtro));
        }*/
        buscarPrestamos();
    } else {
        QString mensaje = resultado.mensaje + "\n\n";
        QMessageBox::warning(this, "No se puede registrar la devolucion", mensaje);
    }
}
