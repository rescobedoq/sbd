#include "UsuarioController.h"

UsuarioController::UsuarioController() {}

// Carga de usuarios en memoria
bool UsuarioController::cargarUsuarios() {
    if (cacheInicializada) return true;
    repositorio.limpiar();
    repositorio.setItems( dao.obtenerUsuarios() );
    return true;
}

// Agregar usuario implementada
bool UsuarioController::agregarUsuario(const int& id,const QString& nombre) {
    std::shared_ptr<Usuario> usuario;
    usuario = std::make_shared<Usuario>(id, nombre);
    if(repositorio.existe(id)){
        qDebug() << "Validación UsuarioController.agregarUsuario(): Usuario duplicado";
        return false;
    }
    if(dao.insertarUsuario(usuario)){
        repositorio.agregar(usuario);
        return true;
    }
    return false;
}

bool UsuarioController::actualizarUsuario(const int& id,const QString& nombre) {
    std::shared_ptr<Usuario> usuario;
    usuario = std::make_shared<Usuario>(id, nombre);
    if(dao.actualizarUsuario(usuario)){
        repositorio.actualizar(usuario);
        return true;
    }
    return false;
}

bool UsuarioController::eliminarUsuario(int id) {
    if (id >= 0) {
        if(dao.eliminarUsuario(id)){
            repositorio.remover(id);
            return true;
        }
    } else {
        qWarning() << "Error de Controller en eliminarUsuario(): ID invalido" << Qt::endl;
        return false;
    }
    return false;
}

QVector<std::shared_ptr<Usuario>> UsuarioController::obtenerUsuarios() {
    return repositorio.obtenerTodos();
}

QVector<std::shared_ptr<Usuario>> UsuarioController::buscarUsuario(const QString& nombre) {
    return repositorio.filtrar([nombre](const std::shared_ptr<Usuario>& u){
        return u->getNombre().contains(nombre);
    });
}

std::shared_ptr<Usuario> UsuarioController::obtenerUsuarioPorID(int id) {
    return repositorio.buscarPorId(id);
}

std::shared_ptr<Usuario> UsuarioController::obtenerUsuarioPorIndice(const int& indice) {
    return repositorio.at(indice);
}

