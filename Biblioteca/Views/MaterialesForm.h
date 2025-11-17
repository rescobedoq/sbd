#ifndef MATERIALESFORM_H
#define MATERIALESFORM_H

#include <QWidget>

namespace Ui {
class MaterialesForm;
}

class MaterialesForm : public QWidget
{
    Q_OBJECT

public:
    explicit MaterialesForm(QWidget *parent = nullptr);
    ~MaterialesForm();

private:
    Ui::MaterialesForm *ui;
};

#endif // MATERIALESFORM_H
