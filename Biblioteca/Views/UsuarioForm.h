#ifndef USUARIOFORM_H
#define USUARIOFORM_H

#include <QWidget>
#include "../Models/usuario.h"
namespace Ui {
class UsuarioForm;
}

class UsuarioForm : public QWidget
{
    Q_OBJECT

public:
    explicit UsuarioForm(int tipo, std::shared_ptr<Usuario> u = nullptr, QWidget *parent = nullptr);
    ~UsuarioForm();

private slots:
    void on_btnAccionUsuario_clicked();
    void on_btnCancelarUsuario_clicked();

signals:
    void usuarioActualizado();

private:
    //Tipo de ventana (1: Nuevo, 2: Edicion)
    int tipoVentana;
    std::shared_ptr<Usuario> usuario;
    Ui::UsuarioForm *ui;
};

#endif // USUARIOFORM_H
