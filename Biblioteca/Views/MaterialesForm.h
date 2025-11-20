#ifndef MATERIALESFORM_H
#define MATERIALESFORM_H

#include <QWidget>
#include "../Controllers/MaterialController.h"

namespace Ui {
class MaterialesForm;
}

class MaterialesForm : public QWidget
{
    Q_OBJECT

public:
    explicit MaterialesForm(MaterialController* controller, int tipo, std::shared_ptr<Material> m=nullptr,QWidget *parent=nullptr);
    ~MaterialesForm();

private slots:
    void on_accionMaterialButton_clicked();
    void on_cancelarMaterialButton_clicked();
signals:
    void materialActualizado();

private:

    MaterialController* controllerMaterial;
    int tipoVentana;
    std::shared_ptr<Material> material;
    Ui::MaterialesForm *ui;
};



#endif // MATERIALESFORM_H
