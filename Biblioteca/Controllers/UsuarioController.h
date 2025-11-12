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
#include "../Models/UsuarioDAO.h"

class UsuarioController
{
public:
    UsuarioController();

    bool cargarUsuarios();
    bool guardarUsuarios(const QString& archivo);

    void agregarUsuario(const int& id,const QString& nombre);
    void eliminarUsuario(int indice);
    QVector<std::shared_ptr<Usuario>>& obtenerUsuarios();

private:
    UsuarioDAO dao;
    QVector<std::shared_ptr<Usuario>> usuarios;
};

#endif // USUARIOCONTROLLER_H
