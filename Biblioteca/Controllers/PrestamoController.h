#ifndef PRESTAMOCONTROLLER_H
#define PRESTAMOCONTROLLER_H

#include <QList>
#include <QDate>
#include <memory>
#include "../Models/Prestamo.h"

#include "../Models/PrestamoDAO.h"

class PrestamoController
{
private:
    PrestamoDAO dao;   // Usa el DAO real

public:
    PrestamoController();

    // Crear un préstamo
    bool crearPrestamo(const std::shared_ptr<Prestamo>& prestamo);

    // Registrar devolución
    bool registrarDevolucion(int prestamoId, const QDate& fechaDev);

    // Consultas
    QList<std::shared_ptr<Prestamo>> obtenerPrestamosActivos();
    QList<std::shared_ptr<Prestamo>> obtenerPrestamosVencidos();
    QList<std::shared_ptr<Prestamo>> obtenerHistorialUsuario(int usuarioId);
};

#endif // PRESTAMOCONTROLLER_H

