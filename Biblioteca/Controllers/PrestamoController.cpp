#include "PrestamoController.h"
#include "../Models/Prestamo.h"
#include "MaterialController.h"
#include <QDebug>

PrestamoController::PrestamoController() {}

bool PrestamoController::cargarPrestamos() {
    if (cacheInicializada) return true;
    repositorio.limpiar();
    repositorio.setItems( dao.obtenerPrestamos() );
    return true;
}

bool PrestamoController::crearPrestamo(int usuarioID, int materialID, const QString& nomUsuario, const QString& nomMaterial,
                                       const QDate& fechaPrestamo, const QDate& fechaLimite)
{
    std::shared_ptr<Prestamo> prestamo = std::make_shared<Prestamo>(usuarioID, materialID, nomUsuario, nomMaterial,
                                                                    fechaPrestamo, fechaLimite);

    int idGenerado;

    if(dao.insertarPrestamo(prestamo, idGenerado)){
        prestamo->setID(idGenerado);
        repositorio.agregar(prestamo);
        return true;
    }
    return false;
}

bool PrestamoController::registrarDevolucion(int prestamoId, const QDate& fechaDev) {
    auto prestamo = repositorio.buscarPorId(prestamoId);
    if (!prestamo) {
        qDebug() << "Error en PrestamoController.cambiarDisponibilidad(): No se encontro el prestamo a modificar";
        return false;
    }
    if (dao.registrarDevolucion(prestamoId, fechaDev)) {
        prestamo->setDevuelto(true);
        prestamo->setFechaDevolucionReal(fechaDev);
        return true;
    }
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

QVector<std::shared_ptr<Prestamo>> PrestamoController::obtenerPrestamos() {
    return repositorio.obtenerTodos();
}

QVector<std::shared_ptr<Prestamo>> PrestamoController::obtenerPrestamosActivosPorUsuario(int usuarioId) {
    return repositorio.filtrar([usuarioId](const auto& prestamo) {
        return prestamo->getUsuarioId() == usuarioId &&
               !prestamo->estaDevuelto();
    });
}

QVector<std::shared_ptr<Prestamo>> PrestamoController::obtenerPrestamosActivosPorMaterial(int materialId) {
    return repositorio.filtrar([materialId](const auto& prestamo) {
        return prestamo->getMaterialId() == materialId &&
               !prestamo->estaDevuelto();
    });
}

std::shared_ptr<Prestamo> PrestamoController::obtenerPrestamoPorID(int id) {
    return repositorio.buscarPorId(id);
}

std::shared_ptr<Prestamo> PrestamoController::obtenerPrestamoPorIndice(const int& indice) {
    return repositorio.at(indice);
}
