#include "PrestamoController.h"
#include "BaseDatos.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

PrestamoController::PrestamoController() {}

bool PrestamoController::crearPrestamo(const Prestamo& p)
{
    QSqlQuery query(BaseDatos::getBD());
    query.prepare("INSERT INTO Prestamo (id, usuarioId, materialId, "
                  "fechaPrestamo, fechaLimiteDevolucion, devuelto, fechaDevolucion) "
                  "VALUES (:id, :usuarioId, :materialId, :fechaPrestamo, "
                  ":fechaLimite, :devuelto, :fechaDevolucion)");

    query.bindValue(":id", p.getId());
    query.bindValue(":usuarioId", p.getUsuarioId());
    query.bindValue(":materialId", p.getMaterialId());
    query.bindValue(":fechaPrestamo", p.getFechaPrestamo());
    query.bindValue(":fechaLimite", p.getFechaLimiteDevolucion());
    query.bindValue(":devuelto", p.estaDevuelto());
    query.bindValue(":fechaDevolucion", p.getFechaDevolucion());

    if(!query.exec()) {
        qDebug() << "Error al crear préstamo:" << query.lastError().text();
        return false;
    }
    return true;
}

bool PrestamoController::registrarDevolucion(int prestamoId, const QDate& fechaDev)
{
    QSqlQuery query(BaseDatos::getBD());
    query.prepare("UPDATE Prestamo SET devuelto = 1, fechaDevolucion = :fechaDev "
                  "WHERE id = :id");

    query.bindValue(":fechaDev", fechaDev);
    query.bindValue(":id", prestamoId);

    if(!query.exec()) {
        qDebug() << "Error al registrar devolución:" << query.lastError().text();
        return false;
    }
    return true;
}

QList<Prestamo> PrestamoController::obtenerPrestamosActivos()
{
    QList<Prestamo> lista;
    QSqlQuery query("SELECT * FROM Prestamo WHERE devuelto = 0", BaseDatos::getBD());

    while(query.next()) {
        Prestamo p(
            query.value("id").toInt(),
            query.value("usuarioId").toInt(),
            query.value("materialId").toInt(),
            query.value("fechaPrestamo").toDate(),
            query.value("fechaLimiteDevolucion").toDate(),
            false,
            query.value("fechaDevolucion").toDate()
            );
        lista.append(p);
    }
    return lista;
}

QList<Prestamo> PrestamoController::obtenerPrestamosVencidos()
{
    QList<Prestamo> lista;
    QDate hoy = QDate::currentDate();

    QSqlQuery query(BaseDatos::getBD());
    query.prepare("SELECT * FROM Prestamo WHERE devuelto = 0 AND fechaLimiteDevolucion < :hoy");
    query.bindValue(":hoy", hoy);
    query.exec();

    while(query.next()) {
        Prestamo p(
            query.value("id").toInt(),
            query.value("usuarioId").toInt(),
            query.value("materialId").toInt(),
            query.value("fechaPrestamo").toDate(),
            query.value("fechaLimiteDevolucion").toDate(),
            false,
            query.value("fechaDevolucion").toDate()
            );
        lista.append(p);
    }
    return lista;
}

QList<Prestamo> PrestamoController::obtenerHistorialUsuario(int usuarioId)
{
    QList<Prestamo> lista;

    QSqlQuery query(BaseDatos::getBD());
    query.prepare("SELECT * FROM Prestamo WHERE usuarioId = :usuarioId");
    query.bindValue(":usuarioId", usuarioId);
    query.exec();

    while(query.next()) {
        Prestamo p(
            query.value("id").toInt(),
            query.value("usuarioId").toInt(),
            query.value("materialId").toInt(),
            query.value("fechaPrestamo").toDate(),
            query.value("fechaLimiteDevolucion").toDate(),
            query.value("devuelto").toBool(),
            query.value("fechaDevolucion").toDate()
            );
        lista.append(p);
    }
    return lista;
}

