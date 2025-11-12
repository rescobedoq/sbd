#ifndef LIBRODAO_H
#define LIBRODAO_H
#include "MaterialDAO.h"

#include <QSqlError>

class LibroDAO : public MaterialDAO {
public:
    bool insertarLibro(const std::shared_ptr<Libro>& libro);
    bool actualizarLibro(const std::shared_ptr<Libro>& libro);
    QVector<std::shared_ptr<Libro>> obtenerLibros();
};

#endif // LIBRODAO_H
