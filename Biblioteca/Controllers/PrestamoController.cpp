#include "PrestamoController.h"
#include "../Models/Prestamo.h"
#include <QDebug>

// ----------------------------------------------------
// Constructor
// ----------------------------------------------------
PrestamoController::PrestamoController()
{
    // No requiere inicialización adicional
}

// ----------------------------------------------------
// Crear préstamo usando PrestamoDAO
// ----------------------------------------------------
bool PrestamoController::crearPrestamo(const std::shared_ptr<Prestamo>& prestamo)
{
    return dao.insertarPrestamo(prestamo);
}

// ----------------------------------------------------
// Registrar devolución usando el DAO
// ----------------------------------------------------
bool PrestamoController::registrarDevolucion(int prestamoId, const QDate& fechaDev)
{
    return dao.registrarDevolucion(prestamoId, fechaDev);
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

