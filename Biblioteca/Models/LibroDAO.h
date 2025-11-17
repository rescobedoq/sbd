#ifndef LIBRODAO_H
#define LIBRODAO_H

#include "MaterialDAO.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QDebug>

class LibroDAO : public MaterialDAO {
public:
    bool insertar(const std::shared_ptr<Libro>& libro);
    bool actualizar(const std::shared_ptr<Libro>& libro);
    bool eliminar(int id);
    QVector<std::shared_ptr<Libro>> obtenerLibros();
};

#endif // LIBRODAO_H

