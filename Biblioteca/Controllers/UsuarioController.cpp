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

//
std::shared_ptr<Usuario> UsuarioController::obtenerUsuario(const int& pos) {
    return usuarios[pos];
}

bool UsuarioController::actualizarUsuario(const int& id,const QString& nombre) {
    std::shared_ptr<Usuario> usuario;
    usuario = std::make_shared<Usuario>(id, nombre);
    if(dao.actualizarUsuario(usuario)){
        int pos = obtenerIndicePorID(id);
        if (pos != -1) {
            usuarios[pos] = usuario;
            return true;
        }
        qWarning() << "Error de Controller en actualizarUsuario()" << Qt::endl;
        return false;
    }
    return false;
}

bool UsuarioController::eliminarUsuario(int id) {
    if (id >= 0) {
        if(dao.eliminarUsuario(id)){
            int pos = obtenerIndicePorID(id);
            if (pos != -1) {
                usuarios.remove(pos);
                return true;
            }
            qWarning() << "Error de Controller en eliminarUsuario(): Usuario no encontrado en memoria" << Qt::endl;
            return false;
        }
    }
    qWarning() << "Error de Controller en eliminarUsuario(): ID invalido" << Qt::endl;
    return false;
}

int UsuarioController::obtenerIndicePorID(int id){
    int pos = -1;
    for (int i = 0; i < usuarios.size(); ++i) {
        if (usuarios[i]->getId() == id) {
            pos = i;
        }
    }
    return pos;
}

std::shared_ptr<Usuario> UsuarioController::obtenerUsuarioPorID(int id) {
    for (auto &u : usuarios) {
        if (u->getId() == id) {
            return u;
        }
    }
    return nullptr;
}

QVector<std::shared_ptr<Usuario>>& UsuarioController::obtenerUsuarios() {
    return usuarios;
}
