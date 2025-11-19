#include "PrestamoDAO.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>

// CRUD
bool PrestamoDAO::insertarPrestamo(const std::shared_ptr<Prestamo>& prestamo){
    QSqlQuery query;
    query.prepare("INSERT INTO Prestamo (id_prestamo, id_usuario, id_material,"
                  "fecha_prestamo, fecha_limite, devuelto) "
                  "VALUES (:id, :usuarioID, :materialID, :fechaPres, :fechaLim, 0)");
    query.bindValue(":id", prestamo->getId());
    query.bindValue(":usuarioID", prestamo->getUsuarioId());
    query.bindValue(":materialID", prestamo->getMaterialId());
    query.bindValue(":fechaPres", prestamo->getFechaPrestamo());
    query.bindValue(":fechaLim", prestamo->getFechaLimiteDevolucion());

    if (!query.exec()) {
        qWarning() << "Error SQL en insertarPrestamo():" << query.lastError().text();
        return false;
    }
    return true;
}
std::shared_ptr<Prestamo> PrestamoDAO::obtenerPrestamoPorId(int id){
    QSqlQuery query;
    query.prepare(
        "SELECT id_prestamo, usuario_id, material_id,"
        "fecha_prestamo, fecha_limite, devuelto, fecha_devolucion"
        "FROM Prestamo WHERE id_prestamo = :id"
        );
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Error SQL en obtenerPrestamoPorId(" << id << "):"
                 << query.lastError().text();
        return nullptr;
    }
    if (query.next()) {
        return std::make_shared<Prestamo>(
            query.value("id_prestamo").toInt(),
            query.value("id_usuario").toInt(),
            query.value("id_material").toInt(),
            query.value("fecha_prestamo").toDate(),
            query.value("fecha_limite").toDate(),
            query.value("devuelto").toBool(),
            query.value("fecha_devolucion").toDate()
            );
    }
    return nullptr;
}
QVector<std::shared_ptr<Prestamo>> PrestamoDAO::obtenerPrestamos(){
    QVector<std::shared_ptr<Prestamo>> lista;

    QSqlQuery query;
    query.prepare(
        "SELECT id_prestamo, usuario_id, material_id,"
        "fecha_prestamo, fecha_limite, devuelto, fecha_devolucion"
        "FROM Prestamo "
        "ORDER BY fecha_prestamo DESC"
        );

    if (!query.exec()) {
        qDebug() << "Error SQL en obtenerPrestamos():"
                 << query.lastError().text();
        return lista; // Devuelve lista vacía
    }

    while (query.next()) {
        lista.append(std::make_shared<Prestamo>(
            query.value("id_prestamo").toInt(),
            query.value("id_usuario").toInt(),
            query.value("id_material").toInt(),
            query.value("fecha_prestamo").toDate(),
            query.value("fecha_limite").toDate(),
            query.value("devuelto").toBool(),
            query.value("fecha_devolucion").toDate()
            ));
    }
    return lista;
}

// Consultas específicas
QVector<std::shared_ptr<Prestamo>> PrestamoDAO::obtenerPrestamosPendientes(){
    QVector<std::shared_ptr<Prestamo>> lista;

    QSqlQuery query;
    query.prepare(
        "SELECT id_prestamo, usuario_id, material_id,"
        "fecha_prestamo, fecha_limite, devuelto, fecha_devolucion"
        "FROM Prestamo "
        "WHERE devuelto = 0 "
        "ORDER BY fecha_limite ASC"
        );

    if (!query.exec()) {
        qDebug() << "Error SQL en obtenerPrestamosPendientes():"
                 << query.lastError().text();
        return lista; // Devuelve lista vacía
    }

    while (query.next()) {
        lista.append(std::make_shared<Prestamo>(
            query.value("id_prestamo").toInt(),
            query.value("id_usuario").toInt(),
            query.value("id_material").toInt(),
            query.value("fecha_prestamo").toDate(),
            query.value("fecha_limite").toDate(),
            query.value("devuelto").toBool(),
            query.value("fecha_devolucion").toDate()
        ));
    }
    return lista;
}
QVector<std::shared_ptr<Prestamo>> PrestamoDAO::obtenerPrestamosVencidos(){
    QVector<std::shared_ptr<Prestamo>> lista;

    QSqlQuery query;
    query.prepare(
        "SELECT id_prestamo, usuario_id, material_id,"
        "fecha_prestamo, fecha_limite, devuelto, fecha_devolucion"
        "FROM Prestamo "
        "WHERE devuelto = 0 AND fecha_limite < date('now') "
        "ORDER BY fecha_limite ASC"
        );

    if (!query.exec()) {
        qDebug() << "Error SQL en obtenerPrestamosPendientes():"
                 << query.lastError().text();
        return lista; // Devuelve lista vacía
    }

    while (query.next()) {
        lista.append(std::make_shared<Prestamo>(
            query.value("id_prestamo").toInt(),
            query.value("id_usuario").toInt(),
            query.value("id_material").toInt(),
            query.value("fecha_prestamo").toDate(),
            query.value("fecha_limite").toDate(),
            query.value("devuelto").toBool(),
            query.value("fecha_devolucion").toDate()
        ));
    }
    return lista;
}

// Registrar devolución
bool PrestamoDAO::registrarDevolucion(int prestamoId, const QDate& fechaDevolucion) {
    QSqlQuery query;
    query.prepare("UPDATE Prestamo SET devuelto = 1, fecha_devolucion = :fecha WHERE id_prestamo = :id");
    query.bindValue(":id", prestamoId);
    query.bindValue(":fecha", fechaDevolucion.toString("yyyy-MM-dd"));

    if (!query.exec()) {
        qDebug() << "Error SQL en registrarDevolucion():" << query.lastError().text();
        return false;
    }

    return true;
}

// Consultas mixtas (para ver el nombre del usuario y del material en vez de sus IDs)
