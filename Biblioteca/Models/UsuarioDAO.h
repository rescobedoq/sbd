#ifndef USUARIODAO_H
#define USUARIODAO_H
#include "Usuario.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVector>

class UsuarioDAO {
public:
    static bool insertarUsuario(const std::shared_ptr<Usuario>& usuario);
    static bool actualizarUsuario(const std::shared_ptr<Usuario>& usuario);
    static bool eliminarUsuario(int id);
    static QVector<std::shared_ptr<Usuario>> obtenerUsuarios();
    static std::shared_ptr<Usuario> obtenerUsuarioPorId(int id);
};

#endif // USUARIODAO_H
