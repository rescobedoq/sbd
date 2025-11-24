#ifndef PRESTAMOS_H
#define PRESTAMOS_H

#include <QWidget>
#include "../Controllers/PrestamoController.h"

namespace Ui {
class Prestamos;
}

class Prestamos : public QWidget
{
    Q_OBJECT

public:
    explicit Prestamos(PrestamoController* controller, QWidget *parent = nullptr);
    void cargarTabla();
    ~Prestamos();

private:
    PrestamoController* controllerPrestamo;
    Ui::Prestamos *ui;

private slots:
    void on_btnNuevoPrestamo_clicked();
    void on_btnRegistrarDevolucion_clicked();
};

#endif // PRESTAMOS_H
