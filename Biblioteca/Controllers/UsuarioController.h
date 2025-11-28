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
#include "../Models/Repositorio.h"

class UsuarioController
{
private:
    UsuarioDAO dao;
    Repositorio<Usuario> repositorio;
    bool cacheInicializada = false;

public:
    UsuarioController();

    // Metodos del CRUD
    bool actualizarUsuario(const int& id,const QString& nombre);
    bool agregarUsuario(const int& id,const QString& nombre);
    bool eliminarUsuario(int id);

    // Metodos utilitarios
    bool cargarUsuarios();
    bool guardarUsuarios(const QString& archivo);
    QVector<std::shared_ptr<Usuario>> obtenerUsuarios();
    std::shared_ptr<Usuario> obtenerUsuarioPorIndice(const int& indice);

    // Metodos para busqueda
    std::shared_ptr<Usuario> obtenerUsuarioPorID(int id);


};

#endif // USUARIOCONTROLLER_H
