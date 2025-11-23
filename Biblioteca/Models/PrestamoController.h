#ifndef PRESTAMOCONTROLLER_H
#define PRESTAMOCONTROLLER_H

#include <QList>
#include "Prestamo.h"

class PrestamoController
{
public:
    PrestamoController();

    bool crearPrestamo(const Prestamo& prestamo);
    bool registrarDevolucion(int prestamoId, const QDate& fechaDev);

    QList<Prestamo> obtenerPrestamosActivos();
    QList<Prestamo> obtenerPrestamosVencidos();
    QList<Prestamo> obtenerHistorialUsuario(int usuarioId);
};

#endif // PRESTAMOCONTROLLER_H
