#ifndef USUARIOCONTROLLER_H
#define USUARIOCONTROLLER_H

#include <QVector>
#include <QString>
#include <memory>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include "../Models/usuario.h"

class UsuarioController
{
public:
    UsuarioController();

    bool cargarUsuarios(const QString& archivo);
    bool guardarUsuarios(const QString& archivo);

    void agregarUsuario(std::shared_ptr<Usuario> usuario);
    void eliminarUsuario(int indice);
    QVector<std::shared_ptr<Usuario>>& obtenerUsuarios();

private:
    QVector<std::shared_ptr<Usuario>> usuarios;

    std::shared_ptr<Usuario> crearUsuarioDesdeJson(const QString& nombre,
                                                     const int& id);
};

#endif // USUARIOCONTROLLER_H
