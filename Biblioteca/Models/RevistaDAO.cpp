#include "RevistaDAO.h"

bool RevistaDAO::insertarRevista(const std::shared_ptr<Revista>& revista) {
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.transaction()) {
        qDebug() << "No se pudo iniciar transacción en RevistaDAO::insertarRevista()";
        return false;
    }

    // Insertar en tabla Material (usa método protegido de la clase base)
    int idGenerado;
    if (!insertarEnMaterial(revista, idGenerado)) {
        db.rollback();
        return false;
    }

    // Insertar en tabla Revista
    QSqlQuery query;
    query.prepare("INSERT INTO Revista (id_material, volumen) VALUES (:id, :volumen)");
    query.bindValue(":id", idGenerado);
    query.bindValue(":volumen", revista->getVolumen());

    if (!query.exec()) {
        qDebug() << "Error SQL en RevistaDAO::insertarRevista():" << query.lastError().text();
        db.rollback();
        return false;
    }

    if (!db.commit()) {
        qDebug() << "Error al confirmar transacción en RevistaDAO::insertarRevista()";
        db.rollback();
        return false;
    }

    return true;
}

bool RevistaDAO::actualizarRevista(const std::shared_ptr<Revista>& revista) {
    // Reutiliza el método de la clase base que ya maneja transacciones
    return MaterialDAO::actualizar(revista);
}

QVector<std::shared_ptr<Revista>> RevistaDAO::obtenerRevistas() {
    QVector<std::shared_ptr<Revista>> lista;

    QSqlQuery query;
    query.prepare(
        "SELECT m.*, r.volumen "
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
