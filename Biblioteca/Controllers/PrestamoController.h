#ifndef PRESTAMOCONTROLLER_H
#define PRESTAMOCONTROLLER_H

#include <QList>
#include <QDate>
#include <memory>
#include "../Models/Prestamo.h"
#include "MaterialController.h"
#include "../Models/PrestamoDAO.h"

class PrestamoController
{
private:
    MaterialController& materialController;
    PrestamoDAO dao;   // Usa el DAO real
    QVector<std::shared_ptr<Prestamo>> prestamos;

public:
    PrestamoController(MaterialController& materialController);
    bool cargarPrestamos();
    // Crear un préstamo
    bool crearPrestamo(int usuarioID, int materialID, const QString& nomUsuario, const QString& nomMaterial,
                       const QDate& fechaPrestamo, const QDate& fechaLimite);

    // Registrar devolución
    bool registrarDevolucion(int prestamoId, const QDate& fechaDev);

    // Consultas
    QList<std::shared_ptr<Prestamo>> obtenerPrestamosActivos();
    QList<std::shared_ptr<Prestamo>> obtenerPrestamosVencidos();
    QList<std::shared_ptr<Prestamo>> obtenerHistorialUsuario(int usuarioId);
    QVector<std::shared_ptr<Prestamo>>& obtenerPrestamos();
};

#endif // PRESTAMOCONTROLLER_H

