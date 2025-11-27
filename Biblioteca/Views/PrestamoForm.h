#ifndef PRESTAMOFORM_H
#define PRESTAMOFORM_H

#include <QDialog>
#include "../Controllers/PrestamoController.h"
#include "../Controllers/UsuarioController.h"

namespace Ui {
class PrestamoForm;
}

class PrestamoForm : public QDialog
{
    Q_OBJECT

public:
    explicit PrestamoForm(PrestamoController& controller, UsuarioController& usuarioCtrl, MaterialController& materialCtrl, QWidget *parent = nullptr);
    ~PrestamoForm();

private:
    UsuarioController& controllerUsuario;
    MaterialController& controllerMaterial;
    PrestamoController& controllerPrestamo;
    Ui::PrestamoForm *ui;

private slots:
    void on_btnRegistrarPrestamo_clicked();
    void on_btnCancelarPrestamo_clicked();

signals:
    void prestamoCreado();
};

#endif // PRESTAMOFORM_H
