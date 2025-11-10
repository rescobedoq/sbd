#ifndef CONTROLLERMATERIAL_H
#define CONTROLLERMATERIAL_H

#include <QVector>
#include <QString>
#include <memory>
#include "../Models/material.h"

class controllerMaterial {
public:
    controllerMaterial();

    // Métodos para cargar y guardar materiales
    bool cargarMateriales(const QString& archivo);
    bool guardarMateriales(const QString& archivo);

    // Métodos para gestionar la lista de materiales
    void agregarMaterial(std::shared_ptr<Material> material);
    void eliminarMaterial(int indice);
    QVector<std::shared_ptr<Material>>& obtenerMateriales();

private:
    QVector<std::shared_ptr<Material>> materiales;

    // Métodos auxiliares para crear objetos específicos
    std::shared_ptr<Material> crearMaterialDesdeJson(const QString& tipo,
                                                     const QString& titulo,
                                                     const QString& autor,
                                                     int anio,
                                                     bool disponible,
                                                     const QString& extra);
};

#endif
