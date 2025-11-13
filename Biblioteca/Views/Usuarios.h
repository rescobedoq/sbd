#ifndef USUARIOS_H
#define USUARIOS_H

#include <QWidget>
#include "../Controllers/UsuarioController.h"

namespace Ui {
class Usuarios;
}

class Usuarios : public QWidget
{
    Q_OBJECT

public:
    explicit Usuarios(UsuarioController* controller, QWidget* parent = nullptr);
    void cargarTabla();
    ~Usuarios();

private slots:
    void on_btnNuevoUsuario_clicked();
    void on_btnEditarUsuario_clicked();
    void on_btnEliminarUsuario_clicked();

private:
    UsuarioController* controllerUsuario;
    Ui::Usuarios *ui;
};

#endif // USUARIOS_H
