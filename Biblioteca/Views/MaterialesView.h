#ifndef MATERIALESVIEW_H
#define MATERIALESVIEW_H

#include <QWidget>
#include "../Models/material.h"

namespace Ui {
class MaterialesView;
}

class MaterialesView : public QWidget
{
    Q_OBJECT

public:
    explicit MaterialesView(QWidget *parent = nullptr);
    void cargarTabla(const QVector<std::shared_ptr<Material>>& materiales);
    ~MaterialesView();

private slots:
    void on_crearMaterialButton_clicked();
    void on_editarMaterialButton_clicked();
    void on_eliminarMaterialButton_clicked();
    void on_buscarButton_clicked();
    void aplicarFiltros();

private:
    Ui::MaterialesView *ui;
};

#endif // MATERIALESVIEW_H
