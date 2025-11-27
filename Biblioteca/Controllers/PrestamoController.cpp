#include "PrestamoController.h"
#include "../Models/Prestamo.h"
#include "MaterialController.h"
#include <QDebug>

PrestamoController::PrestamoController(MaterialController& mc) : materialController(mc) {}

bool PrestamoController::cargarPrestamos() {
    prestamos = dao.obtenerPrestamos();
    return true;
}

bool PrestamoController::crearPrestamo(int usuarioID, int materialID, const QString& nomUsuario, const QString& nomMaterial,
                                       const QDate& fechaPrestamo, const QDate& fechaLimite)
{
    std::shared_ptr<Prestamo> prestamo = std::make_shared<Prestamo>(usuarioID, materialID, nomUsuario, nomMaterial,
                                                                    fechaPrestamo, fechaLimite);

    for (const auto& p : prestamos) {
        if (p->getMaterialId() == materialID) {
            qDebug() << "Validación PrestamoController::crearPrestamo(): Material ya prestado";
            return false;
        }
    }
    int idGenerado;

    if(dao.insertarPrestamo(prestamo, idGenerado)){
        prestamo->setID(idGenerado);
        prestamos.append(prestamo);
        materialController.cambiarDisponibilidad(materialID,false);
        return true;
    }
    return false;
}

bool PrestamoController::registrarDevolucion(int prestamoId, const QDate& fechaDev) {
    if (!dao.registrarDevolucion(prestamoId, fechaDev)) {
        qDebug() << "Error al registrar devolución en la BD";
        return false;
    }

    // Actualiza el objeto en memoria (cache de préstamos)
    for (const auto& p : prestamos) {
        if (p->getId() == prestamoId) {
            p->setDevuelto(true);
            p->setFechaDevolucionReal(fechaDev);
            // Marca el material como disponible en BD y cache
            if (!materialController.cambiarDisponibilidad(p->getMaterialId(), true)) {
                qDebug() << "Error al actualizar disponibilidad del material";
                return false;
            }
            return true;
        }
    }

    qDebug() << "Prestamo no encontrado en cache";
    return false;
}

QList<std::shared_ptr<Prestamo>> PrestamoController::obtenerPrestamosActivos()
{
    QList<std::shared_ptr<Prestamo>> lista;
    auto datos = dao.obtenerPrestamosPendientes();

    for (auto& p : datos)
        lista.append(p);

    return lista;
}

QList<std::shared_ptr<Prestamo>> PrestamoController::obtenerPrestamosVencidos()
{
    QList<std::shared_ptr<Prestamo>> lista;
    auto datos = dao.obtenerPrestamosVencidos();

    for (auto& p : datos)
        lista.append(p);

    return lista;
}

QList<std::shared_ptr<Prestamo>> PrestamoController::obtenerHistorialUsuario(int usuarioId)
{
    QList<std::shared_ptr<Prestamo>> lista;

    // auto datos = dao.obtenerPorUsuario(usuarioId);  //

    // for (auto& p : datos)
    //     lista.append(p);

    return lista;
}

QVector<std::shared_ptr<Prestamo>>& PrestamoController::obtenerPrestamos() {
    return prestamos;
}
