#ifndef PRESTAMODAO_H
#define PRESTAMODAO_H
#include "Prestamo.h"

class PrestamoDAO {
public:
    // CRUD
    bool insertarPrestamo(const std::shared_ptr<Prestamo>& prestamo);
    std::shared_ptr<Prestamo> obtenerPrestamoPorId(int id);
    QVector<std::shared_ptr<Prestamo>> obtenerPrestamos();

    // Consultas específicas
    QVector<std::shared_ptr<Prestamo>> obtenerPrestamosPendientes();
    QVector<std::shared_ptr<Prestamo>> obtenerPrestamosVencidos();

    // Pendiente de implementar
    // En vista de usuario para ver sus prestamos realizados o pendientes
    //QVector<std::shared_ptr<Prestamo>> obtenerPorUsuario(int usuarioId);

    // Registrar devolución
    bool registrarDevolucion(int prestamoId, const QDate& fechaDevolucion);

    // Verificaciones (Pendiente de implementar)
    // Si que quiere restringir el prestamo a un usuario
    bool usuarioTienePrestamosVencidos(int usuarioId);
    // En vista de usuario para ver el numero de sus prestamos realizados o pendientes
    int contarPrestamosActivosDeUsuario(int usuarioId);
};

#endif // PRESTAMODAO_H
