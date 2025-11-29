#include "TesisDAO.h"
#include "BaseDatos.h"

bool TesisDAO::insertar(const std::shared_ptr<Tesis>& tesis) {
    QSqlDatabase db = BaseDatos::getBD();

    if (!db.transaction()) {
        qDebug() << "No se pudo iniciar transacción en TesisDAO::insertar()";
        return false;
    }
    int idGenerado;
    if (!insertarEnMaterial(tesis, idGenerado)) {
        db.rollback();
        return false;
    }

    QSqlQuery query(BaseDatos::getBD());
    query.prepare("INSERT INTO Tesis (id_material, universidad) VALUES (:id, :universidad)");
    query.bindValue(":id", idGenerado);
    query.bindValue(":universidad", tesis->getUniversidad());

    if (!query.exec()) {
        qDebug() << "Error SQL en TesisDAO::insertar():" << query.lastError().text();
        db.rollback();
        return false;
    }

    if (!db.commit()) {
        qDebug() << "Error al confirmar transacción en TesisDAO::insertar()";
        db.rollback();
        return false;
    }

    return true;
}

bool TesisDAO::actualizar(const std::shared_ptr<Tesis>& tesis) {
    bool ok = MaterialDAO::actualizar(tesis);
    if (!ok) return false;

    QSqlQuery query(BaseDatos::getBD());
    query.prepare("UPDATE Tesis SET universidad = :universidad WHERE id_material = :id");
    query.bindValue(":universidad", tesis->getUniversidad());
    query.bindValue(":id", tesis->getId());

    if (!query.exec()) {
        qDebug() << "Error SQL en TesisDAO::actualizar():" << query.lastError().text();
        return false;
    }
    return true;
}

bool TesisDAO::eliminar(int id) {
    QSqlDatabase db = BaseDatos::getBD();
    if (!db.transaction()) {
        qDebug() << "No se pudo iniciar transacción en TesisDAO::eliminar()";
        return false;
    }

    QSqlQuery q1(BaseDatos::getBD());
    q1.prepare("DELETE FROM Tesis WHERE id_material = :id");
    q1.bindValue(":id", id);
    if (!q1.exec()) {
        qDebug() << "Error SQL en TesisDAO::eliminar() (tabla Tesis):" << q1.lastError().text();
        db.rollback();
        return false;
    }

    if (!MaterialDAO::eliminar(id)) {
        db.rollback();
        return false;
    }

    if (!db.commit()) {
        qDebug() << "Error al confirmar transacción en TesisDAO::eliminar()";
        db.rollback();
        return false;
    }

    return true;
}

QVector<std::shared_ptr<Tesis>> TesisDAO::obtenerTesis() {
    QVector<std::shared_ptr<Tesis>> lista;

    QSqlQuery query(BaseDatos::getBD());
    query.prepare(
        "SELECT m.id_material, m.titulo, m.autor, m.anio_publicacion, m.disponible, t.universidad "
        "FROM Material m "
        "INNER JOIN Tesis t ON m.id_material = t.id_material"
        );

    if (!query.exec()) {
        qDebug() << "Error SQL en TesisDAO::obtenerTesis():" << query.lastError().text();
        return lista;
    }

    while (query.next()) {
        lista.append(std::make_shared<Tesis>(
            query.value("id_material").toInt(),
            query.value("titulo").toString(),
            query.value("autor").toString(),
            query.value("anio_publicacion").toInt(),
            query.value("disponible").toBool(),
            query.value("universidad").toString()
            ));
    }

    return lista;
}
