#include "UsuarioController.h"

UsuarioController::UsuarioController() {}

bool UsuarioController::cargarUsuarios(const QString& archivo) {
    QFile file(archivo);

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error al abrir el archivo:" << archivo;
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);

    if (!doc.isArray()) {
        qDebug() << "El archivo JSON no contiene un array";
        return false;
    }

    QJsonArray jsonArray = doc.array();
    usuarios.clear();

    for (const QJsonValue& value : jsonArray) {
        if (!value.isObject()) continue;

        QJsonObject obj = value.toObject();

        QString nombre = obj["nombre"].toString();
        int id = obj["id"].toInt();

        std::shared_ptr<Usuario> usuario;
        usuario = std::make_shared<Usuario>(nombre, id);

        if (usuario) {
            usuarios.append(usuario);
        }
    }

    qDebug() << "Usuarios cargados:" << usuarios.size();
    return true;
}

bool UsuarioController::guardarUsuarios(const QString& archivo) {
    QJsonArray jsonArray;

    for (const auto& usuario : usuarios) {
        QJsonObject obj;
        obj["nombre"] = usuario->getNombre();
        obj["id"] = usuario->getId();
        jsonArray.append(obj);
    }

    QJsonDocument doc(jsonArray);

    QFile file(archivo);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Error al abrir el archivo para escritura:" << archivo;
        return false;
    }

    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();

    qDebug() << "Usuarios guardados:" << usuarios.size();
    return true;
}

void UsuarioController::agregarUsuario(std::shared_ptr<Usuario> usuario) {
    usuarios.append(usuario);
}

void UsuarioController::eliminarUsuario(int indice) {
    if (indice >= 0 && indice < usuarios.size()) {
        usuarios.remove(indice);
    }
}

QVector<std::shared_ptr<Usuario>>& UsuarioController::obtenerUsuarios() {
    return usuarios;
}
