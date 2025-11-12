#include "UsuarioController.h"

UsuarioController::UsuarioController() {}

// Carga de usuarios implementada
bool UsuarioController::cargarUsuarios() {
    usuarios = dao.obtenerUsuarios();
    return true;
}

// Agregar usuario implementada
void UsuarioController::agregarUsuario(const int& id,const QString& nombre) {
    std::shared_ptr<Usuario> usuario;
    usuario = std::make_shared<Usuario>(id, nombre);
    dao.insertarUsuario(usuario);
    usuarios.append(usuario);
}

/* Falta implementar leerUsuario(), actualizarUsuario(), eliminarUsuario(),
* Usar funciones del DAO UsuarioDAO.h: dao.obtenerUsuarioPorId(), dao.actualizarUsuario() y dao.eliminarUsuario()
*/
void UsuarioController::eliminarUsuario(int indice) {
    if (indice >= 0 && indice < usuarios.size()) {
        usuarios.remove(indice);
    }
}

QVector<std::shared_ptr<Usuario>>& UsuarioController::obtenerUsuarios() {
    return usuarios;
}
