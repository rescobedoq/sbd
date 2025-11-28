#include "BibliotecaFacade.h"

BibliotecaFacade* BibliotecaFacade::instancia = nullptr;

BibliotecaFacade::BibliotecaFacade(std::shared_ptr<UsuarioController> usuarioCtrl,
                 std::shared_ptr<MaterialController> materialCtrl,
                 std::shared_ptr<PrestamoController> prestamoCtrl)
    : controllerUsuario(usuarioCtrl),
    controllerMaterial(materialCtrl),
    controllerPrestamo(prestamoCtrl) {}

void BibliotecaFacade::inicializar(std::shared_ptr<UsuarioController> usuarioCtrl,
                        std::shared_ptr<MaterialController> materialCtrl,
                        std::shared_ptr<PrestamoController> prestamoCtrl) {
    if (!instancia) {
        instancia = new BibliotecaFacade(usuarioCtrl, materialCtrl, prestamoCtrl);
    }
}

BibliotecaFacade* BibliotecaFacade::obtenerInstancia() {
    return instancia;
}

BibliotecaFacade::ResultadoPrestamo BibliotecaFacade::realizarPrestamo(int usuarioId, int materialId, const QString& nomUsuario, const QString& nomMaterial,
                                   const QDate& fechaPrestamo, const QDate& fechaLimite) {
    // Verificar límite de préstamos activos del usuario (ejemplo: máximo 3)
    auto prestamosActivos = controllerPrestamo->obtenerPrestamosActivosPorUsuario(usuarioId);
    if (prestamosActivos.size() >= 3) {
        return ResultadoPrestamo(false,
                                 QString("El usuario ya tiene %1 préstamos activos. Máximo: 3")
                                     .arg(prestamosActivos.size()));
    }

    // Crear el préstamo
    bool exito = controllerPrestamo->crearPrestamo(
        usuarioId,
        materialId,
        nomUsuario,
        nomMaterial,
        fechaPrestamo,
        fechaLimite
        );

    if (!exito) {
        return ResultadoPrestamo(false, "No se pudo registrar el préstamo");
    }

    // Actualizar disponibilidad del material
    controllerMaterial->cambiarDisponibilidad(materialId, false);
    return ResultadoPrestamo(true,
                             QString("Préstamo registrado. Devolución: %1")
                                 .arg(fechaLimite.toString("dd/MM/yyyy")));
}

BibliotecaFacade::ResultadoPrestamo BibliotecaFacade::devolverPrestamo(int prestamoId) {
    // Obtener el préstamo
    auto prestamo = controllerPrestamo->obtenerPrestamoPorID(prestamoId);
    if (!prestamo) {
        return ResultadoPrestamo(false, "Préstamo no encontrado");
    }

    // Verificar que no esté ya devuelto
    if (prestamo->estaDevuelto()) {
        return ResultadoPrestamo(false, "Este préstamo ya fue devuelto");
    }

    QDate fechaDevolucion = QDate::currentDate();

    // Registrar la devolución
    bool exito = controllerPrestamo->registrarDevolucion(prestamoId, fechaDevolucion);
    if (!exito) {
        return ResultadoPrestamo(false, "No se pudo registrar la devolución");
    }
    controllerMaterial->cambiarDisponibilidad(prestamo->getMaterialId(), true);

    // Calcular si hay retraso
    int diasRetraso = 0;
    QString mensaje = "Devolución registrada correctamente";

    if (fechaDevolucion > prestamo->getFechaLimiteDevolucion()) {
        diasRetraso = prestamo->getFechaLimiteDevolucion().daysTo(fechaDevolucion);
        mensaje = QString("Devolución con %1 día(s) de retraso").arg(diasRetraso);
    }

    return ResultadoPrestamo(true, mensaje, diasRetraso);
}

BibliotecaFacade::ResultadoEliminacion BibliotecaFacade::eliminarUsuario(int usuarioId) {
    // Verificar préstamos activos
    auto prestamosActivos = controllerPrestamo->obtenerPrestamosActivosPorUsuario(usuarioId);

    if (!prestamosActivos.isEmpty()) {
        ResultadoEliminacion resultado(false,
                                       QString("El usuario tiene %1 préstamo(s) activo(s)")
                                           .arg(prestamosActivos.size()));

        for (const auto& prestamo : prestamosActivos) {
            resultado.prestamosActivos.append(
                QString("%1 (vence: %2)")
                    .arg(prestamo->getNombreMaterial())
                    .arg(prestamo->getFechaLimiteDevolucion().toString("dd/MM/yyyy"))
                );
        }

        return resultado;
    }

    // Si no tiene préstamos activos, eliminar
    bool exito = controllerUsuario->eliminarUsuario(usuarioId);
    return ResultadoEliminacion(exito,
                                exito ? "Usuario eliminado correctamente" : "Error al eliminar usuario");
}

BibliotecaFacade::ResultadoEliminacion BibliotecaFacade::eliminarMaterial(int materialId) {
    // Verificar préstamos activos
    auto prestamosActivos = controllerPrestamo->obtenerPrestamosActivosPorMaterial(materialId);

    if (!prestamosActivos.isEmpty()) {
        ResultadoEliminacion resultado(false,
                                       QString("El material está en %1 préstamo(s) activo(s)")
                                           .arg(prestamosActivos.size()));

        for (const auto& prestamo : prestamosActivos) {
            resultado.prestamosActivos.append(
                QString("Prestado a: %1 (vence: %2)")
                    .arg(prestamo->getNombreUsuario())
                    .arg(prestamo->getFechaLimiteDevolucion().toString("dd/MM/yyyy"))
                );
        }

        return resultado;
    }

    // Si no está prestado, eliminar
    bool exito = controllerMaterial->eliminarMaterial(materialId);
    return ResultadoEliminacion(exito,
                                exito ? "Material eliminado correctamente" : "Error al eliminar material");
}

std::shared_ptr<UsuarioController> BibliotecaFacade::usuarios() {
    return controllerUsuario;
}

std::shared_ptr<MaterialController> BibliotecaFacade::materiales() {
    return controllerMaterial;
}

std::shared_ptr<PrestamoController> BibliotecaFacade::prestamos() {
    return controllerPrestamo;
}
