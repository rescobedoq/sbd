#include "MaterialController.h"
#include "../Models/Libro.h"
#include "../Models/Revista.h"
#include "../Models/Tesis.h"
#include <QDebug>

MaterialController::MaterialController() {
    cargarMateriales();
}

void MaterialController::cargarMateriales() {
    materiales.clear();

    auto libros = libroDAO.obtenerLibros();
    auto revistas = revistaDAO.obtenerRevistas();
    auto tesis = tesisDAO.obtenerTesis();

    for (const auto& l : libros) materiales.append(l);
    for (const auto& r : revistas) materiales.append(r);
    for (const auto& t : tesis) materiales.append(t);

    qDebug() << "Materiales cargados:" << materiales.size();
}

std::shared_ptr<Material> MaterialController::crearMaterial(
    int tipo,
    const QString& titulo,
    const QString& autor,
    int anio,
    const QString& extra,
    bool disponible)
{
    Material* raw = MaterialFactory::crearMaterial(tipo);
    if (!raw) return nullptr;

    std::shared_ptr<Material> material(raw);

    material->setTitulo(titulo);
    material->setAutor(autor);
    material->setAnio(anio);
    material->setDisponible(disponible);

    if (tipo == 1) {
        auto libroPtr = std::static_pointer_cast<Libro>(material);
        libroPtr->setGenero(extra);
        libroDAO.insertar(libroPtr);
    }
    else if (tipo == 2) {
        auto revistaPtr = std::static_pointer_cast<Revista>(material);
        revistaPtr->setVolumen(extra.toInt());
        revistaDAO.insertar(revistaPtr);
    }
    else if (tipo == 3) {
        auto tesisPtr = std::static_pointer_cast<Tesis>(material);
        tesisPtr->setUniversidad(extra);
        tesisDAO.insertar(tesisPtr);
    }

    materiales.append(material);
    return material;
}

QVector<std::shared_ptr<Material>> MaterialController::listarMateriales() {
    return materiales;
}

bool MaterialController::actualizarMaterial(
    int id,
    const QString& titulo,
    const QString& autor,
    int anio,
    const QString& extra,
    bool disponible)
{
    for (auto& material : materiales) {
        if (material->getID() == id) {

            material->setTitulo(titulo);
            material->setAutor(autor);
            material->setAnio(anio);
            material->setDisponible(disponible);

            QString tipo = material->obtenerTipo();

            if (tipo == "Libro") {
                auto l = std::static_pointer_cast<Libro>(material);
                l->setGenero(extra);
                libroDAO.actualizar(l);
            }
            else if (tipo == "Revista") {
                auto r = std::static_pointer_cast<Revista>(material);
                r->setVolumen(extra.toInt());
                revistaDAO.actualizar(r);
            }
            else if (tipo == "Tesis") {
                auto t = std::static_pointer_cast<Tesis>(material);
                t->setUniversidad(extra);
                tesisDAO.actualizar(t);
            }

            return true;
        }
    }
    return false;
}

bool MaterialController::eliminarMaterial(int id) {

    for (int i = 0; i < materiales.size(); i++) {
        if (materiales[i]->getID() == id) {

            QString tipo = materiales[i]->obtenerTipo();

            if (tipo == "Libro")          libroDAO.eliminar(id);
            else if (tipo == "Revista")   revistaDAO.eliminar(id);
            else if (tipo == "Tesis")     tesisDAO.eliminar(id);

            materiales.remove(i);
            return true;
        }
    }
    return false;
}
bool MaterialController::cambiarDisponibilidad(int id, bool disponible) {
    for (auto& material : materiales) {
        if (material->getID() == id) {
            materialDAO.actualizarDisponibilidad(id, disponible);
            material->setDisponible(disponible);
            return true;
        }
    }
    return false;
}
