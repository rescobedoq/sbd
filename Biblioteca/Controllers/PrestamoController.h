#ifndef PRESTAMOCONTROLLER_H
#define PRESTAMOCONTROLLER_H

#include <QList>
#include "../Models/Repositorio.h"
#include <QDate>
#include <memory>
#include "../Models/Prestamo.h"
#include "../Models/PrestamoDAO.h"

class PrestamoController
{
private:
    PrestamoDAO dao;   // Usa el DAO real

    // cache en memoria (según la guía)        // lista completa cargada desde DAO
    Repositorio<Prestamo> prestamosFiltrados; // la vista muestra esta

    // estado actual de búsqueda (útil si quieres mantenerlo)
    QString busquedaActual;
    int estadoActual;   // Usa el DAO real
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
    const QList<std::shared_ptr<Prestamo>> getPrestamosFiltrados() const;
    std::shared_ptr<Prestamo> obtenerPrestamoPorID(int id);
    std::shared_ptr<Prestamo> obtenerPrestamoPorIndice(const int& indice);
    QVector<std::shared_ptr<Prestamo>> obtenerPrestamosActivosPorUsuario(int usuarioId);
    QVector<std::shared_ptr<Prestamo>> obtenerPrestamosActivosPorMaterial(int materialId);
    // Búsqueda + filtros (lo que te toca implementar)
    // filtroEstado: 0 = Todos, 1 = Pendientes, 2 = Devueltos, 3 = Vencidos
    void filtrarPrestamos(const QString& busqueda, int filtroEstado);

};

#endif // PRESTAMOCONTROLLER_H

