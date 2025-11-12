#ifndef MATERIALDAO_H
#define MATERIALDAO_H
#include <QVector>
#include <QString>
#include <QSqlQuery>
#include <memory>
#include "Material.h"
#include "Libro.h"
#include "Revista.h"
#include "Tesis.h"

class MaterialDAO {
protected:
    // Métodos protegidos para uso de clases derivadas
    bool insertarEnMaterial(const std::shared_ptr<Material>& m, int& idGenerado);
    bool actualizarEnMaterial(const std::shared_ptr<Material>& m);
    std::shared_ptr<Material> crearMaterialDesdeQuery(QSqlQuery& query);

public:
    // Operaciones comunes para todos los materiales
    QVector<std::shared_ptr<Material>> obtenerTodos();
    std::shared_ptr<Material> buscarMaterialPorId(int id);
    bool actualizar(const std::shared_ptr<Material>& m);
    bool eliminar(int id);
    bool actualizarDisponibilidad(int id, bool disponible);

    // Búsquedas generales
    QVector<std::shared_ptr<Material>> buscarPorTitulo(const QString& titulo);
    QVector<std::shared_ptr<Material>> buscarPorAutor(const QString& autor);
    QVector<std::shared_ptr<Material>> filtrarPorAnio(int anioInicio, int anioFin);
    QVector<std::shared_ptr<Material>> filtrarPorDisponibilidad(bool disponible);
};


#endif // MATERIALDAO_H
