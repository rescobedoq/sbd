#ifndef USUARIOSVIEW_H
#define USUARIOSVIEW_H

#include <QWidget>
#include "../Models/usuario.h"

namespace Ui {
class UsuariosView;
}

class UsuariosView : public QWidget
{
    Q_OBJECT

public:
    explicit UsuariosView(QWidget* parent = nullptr);
    void cargarTabla(const QVector<std::shared_ptr<Usuario>>& usuarios);
    ~UsuariosView();

private slots:
    void on_btnNuevoUsuario_clicked();
    void on_btnEditarUsuario_clicked();
    void on_btnEliminarUsuario_clicked();
    void on_btnBuscarUsuario_clicked();
    void on_btnRecargar_clicked();

private:
    Ui::UsuariosView *ui;
};

#endif // USUARIOSVIEW_H
