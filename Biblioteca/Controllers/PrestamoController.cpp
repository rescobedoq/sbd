#include "PrestamoController.h"
#include "../Models/Prestamo.h"
#include "MaterialController.h"
#include <QDebug>

// Constructor
// Rebibe un MaterialController para actualizar su cache
PrestamoController::PrestamoController(MaterialController& mc) : materialController(mc) {}

bool PrestamoController::cargarPrestamos() {
    prestamos = dao.obtenerPrestamos();
    return true;
}

bool PrestamoController::crearPrestamo(int usuarioID, int materialID, QDate& fechaPrestamo, QDate& fechaLimite)
{   
    std::shared_ptr<Prestamo> prestamo;
    //prestamo = std::make_shared<Prestamo>(usuarioID, materialID, fechaPrestamo, fechaLimite);
    for (const auto& p : prestamos) {
        if (p->getMaterialId() == materialID) {
            qDebug() << "Validación PrestamoController::crearPrestamo(): Material ya prestado";
            return false;
        }
    }
    int idGenerado;
    if(dao.insertarPrestamo(prestamo, idGenerado)){
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
            // Marca el material como disponible en BD y cache
            if (!materialController.cambiarDisponibilidad(p->getMaterialId(), true)) {
                qDebug() << "Error al actualizar disponibilidad del material";
                return false;
            }
            return true; // retorno tras actualizar el préstamo encontrado
        }
    }

    qDebug() << "Prestamo no encontrado en cache";
    return false;
}

// ----------------------------------------------------
// Obtener préstamos activos (devuelto = 0)
// ----------------------------------------------------
QList<std::shared_ptr<Prestamo>> PrestamoController::obtenerPrestamosActivos()
{
    QList<std::shared_ptr<Prestamo>> lista;
    auto datos = dao.obtenerPrestamosPendientes();

    for (auto& p : datos)
        lista.append(p);

    return lista;
}

// ----------------------------------------------------
// Obtener préstamos vencidos
// ----------------------------------------------------
QList<std::shared_ptr<Prestamo>> PrestamoController::obtenerPrestamosVencidos()
{
    QList<std::shared_ptr<Prestamo>> lista;
    auto datos = dao.obtenerPrestamosVencidos();

    for (auto& p : datos)
        lista.append(p);

    return lista;
}

// ----------------------------------------------------
// Historial completo de un usuario
// ----------------------------------------------------
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
