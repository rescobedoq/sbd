#ifndef USUARIOS_H
#define USUARIOS_H

#include <QWidget>
#include "../Models/usuario.h"

namespace Ui {
class Usuarios;
}

class Usuarios : public QWidget
{
    Q_OBJECT

public:
    explicit Usuarios(QWidget* parent = nullptr);
    void cargarTabla(const QVector<std::shared_ptr<Usuario>>& usuarios);
    ~Usuarios();

private slots:
    void on_btnNuevoUsuario_clicked();
    void on_btnEditarUsuario_clicked();
    void on_btnEliminarUsuario_clicked();
    void on_btnBuscarUsuario_clicked();
    void on_btnRecargar_clicked();

private:
    Ui::Usuarios *ui;
};

#endif // USUARIOS_H
