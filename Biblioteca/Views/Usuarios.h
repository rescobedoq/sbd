#ifndef USUARIOS_H
#define USUARIOS_H

#include <QWidget>

namespace Ui {
class Usuarios;
}

class Usuarios : public QWidget
{
    Q_OBJECT

public:
    explicit Usuarios(QWidget *parent = nullptr);
    ~Usuarios();

private:
    Ui::Usuarios *ui;
};

#endif // USUARIOS_H
