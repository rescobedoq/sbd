#include "TesisDAO.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QDebug>

bool TesisDAO::insertarTesis(const std::shared_ptr<Tesis>& tesis) {
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.transaction()) {
        qDebug() << "No se pudo iniciar transacción en TesisDAO::insertar()";
        return false;
    }

    // Insertar en tabla Material (usa método protegido de la clase base)
    int idGenerado;
    if (!insertarEnMaterial(tesis, idGenerado)) {
        db.rollback();
        return false;
    }

    // Insertar en tabla Tesis
    QSqlQuery query;
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

bool TesisDAO::actualizarTesis(const std::shared_ptr<Tesis>& tesis) {
    // Reutiliza el método de la clase base que ya maneja transacciones
    return MaterialDAO::actualizar(tesis);
}

QVector<std::shared_ptr<Tesis>> TesisDAO::obtenerTesis() {
    QVector<std::shared_ptr<Tesis>> lista;

    QSqlQuery query;
    query.prepare(
        "SELECT m.*, t.universidad "
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
