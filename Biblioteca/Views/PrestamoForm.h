#ifndef PRESTAMOFORM_H
#define PRESTAMOFORM_H

#include <QWidget>
#include "../Controllers/PrestamoController.h"

namespace Ui {
class PrestamoForm;
}

class PrestamoForm : public QWidget
{
    Q_OBJECT

public:
    explicit PrestamoForm(PrestamoController* controller, QWidget *parent = nullptr);
    ~PrestamoForm();

private:
    PrestamoController* controllerPrestamo;
    Ui::PrestamoForm *ui;

private slots:
    void on_btnRegistrarPrestamo_clicked();
    void on_btnCancelarPrestamo_clicked();

signals:
    void prestamoActualizado();
};

#endif // PRESTAMOFORM_H
