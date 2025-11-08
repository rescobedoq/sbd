#ifndef MATERIALES_H
#define MATERIALES_H

#include <QWidget>

namespace Ui {
class Materiales;
}

class Materiales : public QWidget
{
    Q_OBJECT

public:
    explicit Materiales(QWidget *parent = nullptr);
    ~Materiales();

private:
    Ui::Materiales *ui;
};

#endif // MATERIALES_H
