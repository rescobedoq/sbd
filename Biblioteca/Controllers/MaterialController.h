#ifndef MATERIALCONTROLLER_H
#define MATERIALCONTROLLER_H

#include <QVector>
#include <QString>
#include <memory>
#include "../Models/material.h"
#include "../Models/LibroDAO.h"
#include "../Models/RevistaDAO.h"
#include "../Models/TesisDAO.h"

class MaterialController {
public:
    MaterialController();

    // Métodos para cargar y guardar materiales
    bool cargarMateriales();
    // Métodos para gestionar la lista de materiales
    void agregarMaterial(std::shared_ptr<Material> material);
    void eliminarMaterial(int indice);
    QVector<std::shared_ptr<Material>>& obtenerMateriales();

private:
    MaterialDAO materialDAO;
    LibroDAO libroDAO;
    RevistaDAO revistaDAO;
    TesisDAO tesisDAO;

    QVector<std::shared_ptr<Material>> materiales;
};

#endif
