#ifndef MATERIALCONTROLLER_H
#define MATERIALCONTROLLER_H

#include <QVector>
#include <QString>
#include <memory>

#include "../Models/material.h"
#include "../Models/LibroDAO.h"
#include "../Models/RevistaDAO.h"
#include "../Models/TesisDAO.h"
#include "../Models/Repositorio.h"
#include "../Models/MaterialFactory.h"

class MaterialController {
private:
    // DAOs
    MaterialDAO materialDAO;
    LibroDAO libroDAO;
    RevistaDAO revistaDAO;
    TesisDAO tesisDAO;

    Repositorio<Material> repositorio;
    bool cacheInicializada = false;

public:
    MaterialController();

    // Cargar todos los materiales desde la BD
    bool cargarMateriales();

    bool crearMaterial(
        int tipo,              // 1=Libro, 2=Revista, 3=Tesis
        const QString& titulo,
        const QString& autor,
        int anio,
        const QString& extra,
        bool disponible = true  // Por defecto disponible
        );

    bool actualizarMaterial(
        int id,
        const QString& titulo,
        const QString& autor,
        int anio,
        const QString& extra,
        bool disponible = true
        );

    bool eliminarMaterial(int id);

    bool cambiarDisponibilidad(int id, bool disponible);
    QVector<std::shared_ptr<Material>> obtenerMateriales();
    QVector<std::shared_ptr<Material>> obtenerMaterialesDisponibles();
    std::shared_ptr<Material> obtenerMaterialPorID(int id);
    std::shared_ptr<Material> obtenerMaterialPorIndice(const int& indice);
};

#endif // MATERIALCONTROLLER_H
