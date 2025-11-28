#ifndef PRESTAMOCONTROLLER_H
#define PRESTAMOCONTROLLER_H

#include <QList>
#include <QDate>
#include <memory>
#include "../Models/Prestamo.h"
#include "MaterialController.h"
#include "../Models/PrestamoDAO.h"
#include "../Models/Repositorio.h"

class PrestamoController
{
private:
    PrestamoDAO dao;   // Usa el DAO real
    Repositorio<Prestamo> repositorio;
    bool cacheInicializada = false;

public:
    PrestamoController();
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
    QVector<std::shared_ptr<Prestamo>> obtenerPrestamos();
    QVector<std::shared_ptr<Prestamo>> obtenerPrestamosActivosPorUsuario(int usuarioId);
    QVector<std::shared_ptr<Prestamo>> obtenerPrestamosActivosPorMaterial(int materialId);
    std::shared_ptr<Prestamo> obtenerPrestamoPorID(int id);
    std::shared_ptr<Prestamo> obtenerPrestamoPorIndice(const int& indice);
};

#endif // PRESTAMOCONTROLLER_H

