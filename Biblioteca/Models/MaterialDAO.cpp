#include "MaterialDAO.h"
#include "BaseDatos.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QDebug>

bool MaterialDAO::insertarEnMaterial(const std::shared_ptr<Material>& m, int& idGenerado) {
    QSqlQuery query(BaseDatos::getBD());
    query.prepare(
        "INSERT INTO Material (titulo, autor, anio_publicacion, disponible) "
        "VALUES (:titulo, :autor, :anio, :disponible)"
        );
    query.bindValue(":titulo", m->getTitulo());
    query.bindValue(":autor", m->getAutor());
    query.bindValue(":anio", m->getAnio());
    query.bindValue(":disponible", m->getDisponible());

    if (!query.exec()) {
        qDebug() << "Error SQL en insertarEnMaterial():" << query.lastError().text();
        return false;
    }

    idGenerado = query.lastInsertId().toInt();
    return true;
}

bool MaterialDAO::actualizarEnMaterial(const std::shared_ptr<Material>& m) {
    QSqlQuery query(BaseDatos::getBD());
    query.prepare(
        "UPDATE Material SET titulo = :titulo, autor = :autor, "
        "anio_publicacion = :anio, disponible = :disponible "
        "WHERE id_material = :id"
        );
    query.bindValue(":id", m->getID());
    query.bindValue(":titulo", m->getTitulo());
    query.bindValue(":autor", m->getAutor());
    query.bindValue(":anio", m->getAnio());
    query.bindValue(":disponible", m->getDisponible());

    if (!query.exec()) {
        qDebug() << "Error SQL en actualizarMaterial():" << query.lastError().text();
        return false;
    }

    return true;
}

std::shared_ptr<Material> MaterialDAO::crearMaterialDesdeQuery(QSqlQuery& query) {
    int id = query.value("id_material").toInt();
    QString titulo = query.value("titulo").toString();
    QString autor = query.value("autor").toString();
    int anio = query.value("anio_publicacion").toInt();
    bool disponible = query.value("disponible").toBool();

    // Determinar tipo según qué campo no sea nulo
    if (!query.value("genero").isNull()) {
        return std::make_shared<Libro>(
            id, titulo, autor, anio, disponible,
            query.value("genero").toString()
            );
    }
    else if (!query.value("volumen").isNull()) {
        return std::make_shared<Revista>(
            id, titulo, autor, anio, disponible,
            query.value("volumen").toInt()
            );
    }
    else if (!query.value("universidad").isNull()) {
        return std::make_shared<Tesis>(
            id, titulo, autor, anio, disponible,
            query.value("universidad").toString()
            );
    }

    return nullptr;
}

QVector<std::shared_ptr<Material>> MaterialDAO::obtenerTodos() {
    QVector<std::shared_ptr<Material>> lista;

    QSqlQuery query(BaseDatos::getBD());
    query.prepare(
        "SELECT m.*, l.genero, r.volumen, t.universidad "
        "FROM Material m "
        "LEFT JOIN Libro l ON m.id_material = l.id_material "
        "LEFT JOIN Revista r ON m.id_material = r.id_material "
        "LEFT JOIN Tesis t ON m.id_material = t.id_material"
        );

    if (!query.exec()) {
        qDebug() << "Error SQL en obtenerTodos():" << query.lastError().text();
        return lista;
    }

    while (query.next()) {
        auto material = crearMaterialDesdeQuery(query);
        if (material) {
            lista.append(material);
        }
    }

    return lista;
}

std::shared_ptr<Material> MaterialDAO::buscarMaterialPorId(int id) {
    QSqlQuery query(BaseDatos::getBD());
    query.prepare(
        "SELECT m.*, l.genero, r.volumen, t.universidad "
        "FROM Material m "
        "LEFT JOIN Libro l ON m.id_material = l.id_material "
        "LEFT JOIN Revista r ON m.id_material = r.id_material "
        "LEFT JOIN Tesis t ON m.id_material = t.id_material "
        "WHERE m.id_material = :id"
        );
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Error SQL en buscarPorId(" << id << "):" << query.lastError().text();
        return nullptr;
    }

    if (query.next()) {
        return crearMaterialDesdeQuery(query);
    }

    return nullptr;
}

bool MaterialDAO::actualizar(const std::shared_ptr<Material>& m) {
    QSqlDatabase db = BaseDatos::getBD();

    if (!db.transaction()) {
        qDebug() << "No se pudo iniciar transacción en actualizar()";
        return false;
    }

    // Actualizar tabla Material
    if (!actualizarEnMaterial(m)) {
        db.rollback();
        return false;
    }

    // Actualizar tabla hija según tipo
    QString tipo = m->obtenerTipo();
    bool exitoHija = false;
    QSqlQuery query(BaseDatos::getBD());

    if (tipo == "Libro") {
        auto libro = std::dynamic_pointer_cast<Libro>(m);
        query.prepare("UPDATE Libro SET genero = :genero WHERE id_material = :id");
        query.bindValue(":id", libro->getID());
        query.bindValue(":genero", libro->getGenero());
        exitoHija = query.exec();
    }
    else if (tipo == "Revista") {
        auto revista = std::dynamic_pointer_cast<Revista>(m);
        query.prepare("UPDATE Revista SET volumen = :volumen WHERE id_material = :id");
        query.bindValue(":id", revista->getID());
        query.bindValue(":volumen", revista->getVolumen());
        exitoHija = query.exec();
    }
    else if (tipo == "Tesis") {
        auto tesis = std::dynamic_pointer_cast<Tesis>(m);
        query.prepare("UPDATE Tesis SET universidad = :universidad WHERE id_material = :id");
        query.bindValue(":id", tesis->getID());
        query.bindValue(":universidad", tesis->getUniversidad());
        exitoHija = query.exec();
    }

    if (!exitoHija) {
        qDebug() << "Error SQL al actualizar tabla hija:" << query.lastError().text();
        db.rollback();
        return false;
    }

    if (!db.commit()) {
        qDebug() << "Error al confirmar transacción en actualizar()";
        db.rollback();
        return false;
    }

    return true;
}

bool MaterialDAO::eliminar(int id) {
    QSqlDatabase db = BaseDatos::getBD();

    // Eliminar de tablas hijas (por foreign key cascade o manualmente)
    // Si tienes ON DELETE CASCADE configurado, solo necesitas eliminar de Material
    QSqlQuery check(BaseDatos::getBD());
    check.exec("PRAGMA foreign_key_check;");
    while (check.next()) {
        qDebug() << "FK FAIL -> Tabla:" << check.value(0).toString()
        << "Fila:" << check.value(1).toInt()
        << "ID:" << check.value(2).toString()
        << "FK Info:" << check.value(3).toString();
    }
    QSqlQuery query(BaseDatos::getBD());
    query.prepare("DELETE FROM Material WHERE id_material = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Error SQL en MaterialDAO::eliminar(" << id << "):" << query.lastError().text();
        db.rollback();
        return false;
    }
    return true;
}

bool MaterialDAO::actualizarDisponibilidad(int id, bool disponible) {
    QSqlQuery query(BaseDatos::getBD());
    query.prepare("UPDATE Material SET disponible = :disponible WHERE id_material = :id");
    query.bindValue(":id", id);
    query.bindValue(":disponible", disponible);

    if (!query.exec()) {
        qDebug() << "Error SQL en actualizarDisponibilidad():" << query.lastError().text();
        return false;
    }

    return true;
}
