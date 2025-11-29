#include "MaterialController.h"
#include "../Models/Libro.h"
#include "../Models/Revista.h"
#include "../Models/Tesis.h"
#include <QDebug>

MaterialController::MaterialController() {
    cargarMateriales();
}

bool MaterialController::cargarMateriales() {
    if (cacheInicializada) return true;
    repositorio.limpiar();

    auto libros = libroDAO.obtenerLibros();
    auto revistas = revistaDAO.obtenerRevistas();
    auto tesis = tesisDAO.obtenerTesis();

    for (const auto& l : libros) repositorio.agregar(l);
    for (const auto& r : revistas) repositorio.agregar(r);
    for (const auto& t : tesis) repositorio.agregar(t);

    qDebug() << "Materiales cargados:" << repositorio.contar();
    return true;
}

bool MaterialController::crearMaterial(
    int tipo,
    const QString& titulo,
    const QString& autor,
    int anio,
    const QString& extra,
    bool disponible)
{
    Material* raw = MaterialFactory::crearMaterial(tipo);
    if (!raw){
        qDebug() << "Error en MaterialController.crearMaterial(): Creacion en Factory fallida";
        return false;
    }

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

    repositorio.agregar(material);
    return true;
}

bool MaterialController::actualizarMaterial(
    int id,
    const QString& titulo,
    const QString& autor,
    int anio,
    const QString& extra,
    bool disponible)
{

    auto material = repositorio.buscarPorId(id);
    if (!material) {
        qDebug() << "Error en MaterialController.actualizarMaterial(): No se encontro el material a actualizar";
        return false;
    }

    // Actualizar campos base
    material->setTitulo(titulo);
    material->setAutor(autor);
    material->setAnio(anio);
    material->setDisponible(disponible);

    // Actualizar según tipo
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

bool MaterialController::eliminarMaterial(int id) {
    auto material = repositorio.buscarPorId(id);
    if (!material) {
        qDebug() << "Error en MaterialController.eliminarMaterial(): No se encontro el material a eliminar";
        return false;
    }

    QString tipo = material->obtenerTipo();

    if (tipo == "Libro") {
        if(!libroDAO.eliminar(id)){
            return false;
        }
    } else if (tipo == "Revista") {
        if(!revistaDAO.eliminar(id)){
            return false;
        }

    } else if (tipo == "Tesis") {
        if(!tesisDAO.eliminar(id)){
            return false;
        }
    }
    repositorio.remover(id);
    return true;
}

bool MaterialController::cambiarDisponibilidad(int id, bool disponible) {
    auto material = repositorio.buscarPorId(id);
    if (!material) {
        qDebug() << "Error en MaterialController.cambiarDisponibilidad(): No se encontro el material a modificar";
        return false;
    }
    materialDAO.actualizarDisponibilidad(id, disponible);
    material->setDisponible(disponible);
    return true;
}

QVector<std::shared_ptr<Material>> MaterialController::obtenerMateriales() {
    return repositorio.obtenerTodos();
}

std::shared_ptr<Material> MaterialController::obtenerMaterialPorID(int id) {
    return repositorio.buscarPorId(id);
}

QVector<std::shared_ptr<Material>> MaterialController::obtenerMaterialesDisponibles() {
    return repositorio.filtrar([](const std::shared_ptr<Material>& m){
        return m->getDisponible();
    });
}

std::shared_ptr<Material> MaterialController::obtenerMaterialPorIndice(const int& indice) {
    return repositorio.at(indice);
}
// Agregar estos tres métodos al final del archivo

QVector<std::shared_ptr<Material>> MaterialController::buscarMaterialPorNombre(const QString& nombre) {
    if (nombre.trimmed().isEmpty()) {
        return repositorio.obtenerTodos();
    }

    QString nombreLower = nombre.toLower();
    return repositorio.filtrar([nombreLower](const std::shared_ptr<Material>& m) {
        return m->getTitulo().toLower().contains(nombreLower);
    });
}

QVector<std::shared_ptr<Material>> MaterialController::filtrarPorDisponibilidad(bool disponible) {
    return repositorio.filtrar([disponible](const std::shared_ptr<Material>& m) {
        return m->getDisponible() == disponible;
    });
}

QVector<std::shared_ptr<Material>> MaterialController::buscarYFiltrar(const QString& nombre, int filtroDisponibilidad) {
    QString nombreLower = nombre.trimmed().toLower();

    return repositorio.filtrar([nombreLower, filtroDisponibilidad](const std::shared_ptr<Material>& m) {
        // Filtro por nombre (si está vacío, acepta todos)
        bool cumpleNombre = nombreLower.isEmpty() || m->getTitulo().toLower().contains(nombreLower);

        // Filtro por disponibilidad
        // 0 = Todos, 1 = Disponibles, 2 = No disponibles
        bool cumpleDisponibilidad = true;
        if (filtroDisponibilidad == 1) {
            cumpleDisponibilidad = m->getDisponible();
        } else if (filtroDisponibilidad == 2) {
            cumpleDisponibilidad = !m->getDisponible();
        }

        return cumpleNombre && cumpleDisponibilidad;
    });
}
