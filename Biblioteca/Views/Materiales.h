#ifndef MATERIALES_H
#define MATERIALES_H

#include <QWidget>
#include "../Models/material.h"

namespace Ui {
class Materiales;
}

class Materiales : public QWidget
{
    Q_OBJECT

public:
    explicit Materiales(QWidget *parent = nullptr);
    void cargarTabla(const QVector<std::shared_ptr<Material>>& materiales);
    ~Materiales();

private slots:
    void on_crearMaterialButton_clicked();
    void on_editarMaterialButton_clicked();
    void on_eliminarMaterialButton_clicked();

private:
    Ui::Materiales *ui;
};

#endif // MATERIALES_H
