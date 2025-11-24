#ifndef MATERIALES_H
#define MATERIALES_H

#include <QWidget>
#include "../Controllers/MaterialController.h"

namespace Ui {
class Materiales;
}

class Materiales : public QWidget
{
    Q_OBJECT

public:
    explicit Materiales(MaterialController* controller, QWidget *parent = nullptr);
    void cargarTabla();
    ~Materiales();

private slots:
    void on_crearMaterialButton_clicked();
    void on_editarMaterialButton_clicked();
    void on_eliminarMaterialButton_clicked();

private:
    MaterialController* controllerMaterial;
    Ui::Materiales *ui;
};

#endif // MATERIALES_H

