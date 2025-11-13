#include "UsuarioController.h"

UsuarioController::UsuarioController() {}

// Carga de usuarios implementada
bool UsuarioController::cargarUsuarios() {
    usuarios = dao.obtenerUsuarios();
    return true;
}

// Agregar usuario implementada
bool UsuarioController::agregarUsuario(const int& id,const QString& nombre) {
    std::shared_ptr<Usuario> usuario;
    usuario = std::make_shared<Usuario>(id, nombre);
    for (const auto& u : usuarios) {
        if (u->getId() == id) {
            qDebug() << "Validación Controller: Usuario duplicado";
            return false;
        }
    }
    if(dao.insertarUsuario(usuario)){
        usuarios.append(usuario);
        return true;
    }
    return false;
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
