#ifndef PRESTAMOSVIEW_H
#define PRESTAMOSVIEW_H

#include <QWidget>
#include "../Models/Prestamo.h"

namespace Ui {
class PrestamosView;
}

class PrestamosView : public QWidget
{
    Q_OBJECT

public:
    explicit PrestamosView( QWidget *parent = nullptr);

    // 💡 CAMBIO: Cambiamos la función de carga de tabla
    void cargarTablaFiltrada();

    ~PrestamosView();

private:
    Ui::PrestamosView *ui;

private slots:
    void on_btnNuevoPrestamo_clicked();
    void on_btnRegistrarDevolucion_clicked();

    // 💡 NUEVO SLOT: Conexión automática al ComboBox llamado "comboBox"
    void on_comboBox_currentIndexChanged(int index);
    void buscarPrestamos();
};

#endif // PRESTAMOSVIEW_H
