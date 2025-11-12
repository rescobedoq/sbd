#include "MaterialController.h"
#include "../Models/Libro.h"
#include "../Models/Revista.h"
#include "../Models/tesis.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

MaterialController::MaterialController() {}

bool MaterialController::cargarMateriales() {
    materiales.clear();

    // Cargar todos los tipos
    auto libros = libroDAO.obtenerLibros();
    auto revistas = revistaDAO.obtenerRevistas();
    auto tesis = tesisDAO.obtenerTesis();

    // Agregar al caché unificado
    for (const auto& libro : libros) {
        materiales.append(libro);
    }
    for (const auto& revista : revistas) {
        materiales.append(revista);
    }
    for (const auto& t : tesis) {
        materiales.append(t);
    }

    qDebug() << "Materiales cargados:" << materiales.size();
    return true;
}

/* Usar patron factory method con las funciones de los DAO:
 * libroDAO.insertar(libro)
 * revistaDAO.insertar(revista)
 * tesisDAO.insertar(tesis)
 */
void MaterialController::agregarMaterial(std::shared_ptr<Material> material) {
    materiales.append(material);
}

/* Falta implementar leerMaterial()
 * Usar funciones del DAO materialDAO:
 * materialDAO.buscarMaterialPorId()
 *
 * Falta implementar actualizarMaterial()
 * Usar funciones del DAO materialDAO:
 * materialDAO.actualizar()
 *
 * Falta implementar  eliminarMaterial()
 * Usar funciones del DAO materialDAO:
 * materialDAO.eliminar()
 */

void MaterialController::eliminarMaterial(int indice) {
    if (indice >= 0 && indice < materiales.size()) {
        materiales.remove(indice);
    }
}

QVector<std::shared_ptr<Material>>& MaterialController::obtenerMateriales() {
    return materiales;
}
