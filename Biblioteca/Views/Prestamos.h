#ifndef PRESTAMOS_H
#define PRESTAMOS_H

#include <QWidget>
#include "../Models/Prestamo.h"

namespace Ui {
class Prestamos;
}

class Prestamos : public QWidget
{
    Q_OBJECT

public:
    explicit Prestamos( QWidget *parent = nullptr);

    // 💡 CAMBIO: Cambiamos la función de carga de tabla
    void cargarTablaFiltrada();

    ~Prestamos();

private:
    Ui::Prestamos *ui;

private slots:
    void on_btnNuevoPrestamo_clicked();
    void on_btnRegistrarDevolucion_clicked();

    // 💡 NUEVO SLOT: Conexión automática al ComboBox llamado "comboBox"
    void on_comboBox_currentIndexChanged(int index);
    void buscarPrestamos();
};

#endif // PRESTAMOS_H
