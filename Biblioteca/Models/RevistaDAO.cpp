#include "RevistaDAO.h"
#include "BaseDatos.h"

bool RevistaDAO::insertar(const std::shared_ptr<Revista>& revista) {
    QSqlDatabase db = BaseDatos::getBD();

    if (!db.transaction()) {
        qDebug() << "No se pudo iniciar transacción en RevistaDAO::insertar()";
        return false;
    }
    int idGenerado;
    if (!insertarEnMaterial(revista, idGenerado)) {
        db.rollback();
        return false;
    }

    QSqlQuery query(BaseDatos::getBD());
    query.prepare("INSERT INTO Revista (id_material, volumen) VALUES (:id, :volumen)");
    query.bindValue(":id", idGenerado);
    query.bindValue(":volumen", revista->getVolumen());

    if (!query.exec()) {
        qDebug() << "Error SQL en RevistaDAO::insertar():" << query.lastError().text();
        db.rollback();
        return false;
    }

    if (!db.commit()) {
        qDebug() << "Error al confirmar transacción en RevistaDAO::insertar()";
        db.rollback();
        return false;
    }

    return true;
}

bool RevistaDAO::actualizar(const std::shared_ptr<Revista>& revista) {
    bool ok = MaterialDAO::actualizar(revista);
    if (!ok) return false;

    QSqlQuery query(BaseDatos::getBD());
    query.prepare("UPDATE Revista SET volumen = :volumen WHERE id_material = :id");
    query.bindValue(":volumen", revista->getVolumen());
    query.bindValue(":id", revista->getId());

    if (!query.exec()) {
        qDebug() << "Error SQL en RevistaDAO::actualizar():" << query.lastError().text();
        return false;
    }
    return true;
}

bool RevistaDAO::eliminar(int id) {
    QSqlDatabase db = BaseDatos::getBD();
    if (!db.transaction()) {
        qDebug() << "No se pudo iniciar transacción en RevistaDAO::eliminar()";
        return false;
    }

    QSqlQuery q1(BaseDatos::getBD());
    q1.prepare("DELETE FROM Revista WHERE id_material = :id");
    q1.bindValue(":id", id);
    if (!q1.exec()) {
        qDebug() << "Error SQL en RevistaDAO::eliminar() (tabla Revista):" << q1.lastError().text();
        db.rollback();
        return false;
    }

    if (!MaterialDAO::eliminar(id)) {
        db.rollback();
        return false;
    }

    if (!db.commit()) {
        qDebug() << "Error al confirmar transacción en RevistaDAO::eliminar()";
        db.rollback();
        return false;
    }

    return true;
}

QVector<std::shared_ptr<Revista>> RevistaDAO::obtenerRevistas() {
    QVector<std::shared_ptr<Revista>> lista;

    QSqlQuery query(BaseDatos::getBD());
    query.prepare(
        "SELECT m.id_material, m.titulo, m.autor, m.anio_publicacion, m.disponible, r.volumen "
        "FROM Material m "
        "INNER JOIN Revista r ON m.id_material = r.id_material"
        );

    if (!query.exec()) {
        qDebug() << "Error SQL en RevistaDAO::obtenerRevistas():" << query.lastError().text();
        return lista;
    }

    while (query.next()) {
        lista.append(std::make_shared<Revista>(
            query.value("id_material").toInt(),
            query.value("titulo").toString(),
            query.value("autor").toString(),
            query.value("anio_publicacion").toInt(),
            query.value("disponible").toBool(),
            query.value("volumen").toInt()
            ));
    }

    return lista;
}
