#ifndef MATERIALCONTROLLER_H
#define MATERIALCONTROLLER_H

#include <QVector>
#include <QString>
#include <memory>

#include "../Models/material.h"
#include "../Models/LibroDAO.h"
#include "../Models/RevistaDAO.h"
#include "../Models/TesisDAO.h"
#include "../Models/MaterialFactory.h"

class MaterialController {
public:
    MaterialController();

    // Cargar todos los materiales desde la BD
    void cargarMateriales();

    // READ - devolver copia
    QVector<std::shared_ptr<Material>> listarMateriales();

    // CREATE – usando FACTORY
    std::shared_ptr<Material> crearMaterial(
        int tipo,              // 1=Libro, 2=Revista, 3=Tesis
        const QString& titulo,
        const QString& autor,
        int anio,
        const QString& extra,
        bool disponible = true  // Por defecto disponible
        );

    // UPDATE
    bool actualizarMaterial(
        int id,
        const QString& titulo,
        const QString& autor,
        int anio,
        const QString& extra,
        bool disponible = true
        );

    // DELETE
    bool eliminarMaterial(int id);

private:
    // DAOs
    LibroDAO libroDAO;
    RevistaDAO revistaDAO;
    TesisDAO tesisDAO;

    // Lista en memoria
    QVector<std::shared_ptr<Material>> materiales;
};

#endif // MATERIALCONTROLLER_H
