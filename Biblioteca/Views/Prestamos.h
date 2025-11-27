#ifndef PRESTAMOS_H
#define PRESTAMOS_H

#include <QWidget>
#include "../Controllers/PrestamoController.h"
#include "../Controllers/UsuarioController.h"

namespace Ui {
class Prestamos;
}

class Prestamos : public QWidget
{
    Q_OBJECT

public:
    explicit Prestamos(PrestamoController& controller, UsuarioController& usuarioCtrl, MaterialController& materialCtrl, QWidget *parent = nullptr);
    void cargarTabla();
    ~Prestamos();

private:
    UsuarioController& controllerUsuario;
    MaterialController& controllerMaterial;
    PrestamoController& controllerPrestamo;
    Ui::Prestamos *ui;

private slots:
    void on_btnNuevoPrestamo_clicked();
    void on_btnRegistrarDevolucion_clicked();
};

#endif // PRESTAMOS_H
