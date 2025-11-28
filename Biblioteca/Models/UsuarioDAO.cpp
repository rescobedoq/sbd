#include "UsuarioDAO.h"
#include "BaseDatos.h"
#include <QDebug>

bool UsuarioDAO::insertarUsuario(const std::shared_ptr<Usuario>& usuario) {
    QSqlQuery query(BaseDatos::getBD());
    query.prepare("INSERT INTO Usuario (id_usuario, nombre) VALUES (:id, :nombre)");
    query.bindValue(":id", usuario->getId());
    query.bindValue(":nombre", usuario->getNombre());

    if (!query.exec()) {
        qWarning() << "Error SQL en insertarUsuario():" << query.lastError().text();
        return false;
    }
    return true;
}

bool UsuarioDAO::actualizarUsuario(const std::shared_ptr<Usuario>& usuario) {
    QSqlQuery query(BaseDatos::getBD());
    query.prepare("UPDATE Usuario SET nombre = :nombre WHERE id_usuario = :id");
    query.bindValue(":nombre", usuario->getNombre());
    query.bindValue(":id", usuario->getId());

    if (!query.exec()) {
        qWarning() << "Error SQL en actualizarUsuario():" << query.lastError().text();
        return false;
    }
    return true;
}

bool UsuarioDAO::eliminarUsuario(int id) {
    QSqlQuery query(BaseDatos::getBD());
    query.prepare("UPDATE Usuario SET activo = 0 WHERE id_usuario = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qWarning() << "Error SQL eliminarUsuario():" << query.lastError().text();
        return false;
    }
    return true;
}

QVector<std::shared_ptr<Usuario>> UsuarioDAO::obtenerUsuarios() {
    QVector<std::shared_ptr<Usuario>> lista;

    QSqlQuery query(BaseDatos::getBD());
    query.prepare("SELECT id_usuario, nombre FROM Usuario WHERE activo = 1");

    if (!query.exec()) {
        qDebug() << "Error SQL en obtenerUsuarios():"
                 << query.lastError().text();
        return lista; // Devuelve lista vacía
    }

    while (query.next()) {
        lista.append(std::make_shared<Usuario>(
            query.value("id_usuario").toInt(),
            query.value("nombre").toString()
            ));
    }
    return lista;
}

std::shared_ptr<Usuario> UsuarioDAO::obtenerUsuarioPorId(int id) {
    QSqlQuery query(BaseDatos::getBD());
    query.prepare("SELECT id_usuario, nombre FROM Usuario WHERE id_usuario = :id AND activo = 1");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Error SQL en obtenerUsuarioPorId(" << id << "):"
                 << query.lastError().text();
        return nullptr;
    }
    if (query.next()) {
        return std::make_shared<Usuario>(
            query.value("id_usuario").toInt(),
            query.value("nombre").toString()
            );
    }
    return nullptr;
}
