#ifndef BIBLIOTECAFACADE_H
#define BIBLIOTECAFACADE_H
/* Aplicacion del patron Facade en los controllers
 * - Resuelve problemas de acoplamiento en PrestamoController:
 *   Para crear un Prestamo y registrar su devolucion se tenia que usar el MaterialController
 *   para cambiar la disponibilidad del material, ahora esas dos funciones se van a mover aqui
 * - Resuelve problemas de acoplamiento en UsuarioController:
 *   Al eliminar un Usuario se usaba el PrestamoController para saber si no tenia un prestamo asignado
 *   esa comprobacion se va a mover aqui
 * - Resuelve problemas de acoplamiento en MaterialController:
 *   Al eliminar un Material se usaba el PrestamoController para saber si no tenia un prestamo asignado
 *   esa comprobacion se va a mover aqui
 */
#include <memory>
#include <QDate>
#include <QString>
#include <QMessageBox>
#include "../Controllers/UsuarioController.h"
#include "../Controllers/MaterialController.h"
#include "../Controllers/PrestamoController.h"

class BibliotecaFacade {
private:
    std::shared_ptr<UsuarioController> controllerUsuario;
    std::shared_ptr<MaterialController> controllerMaterial;
    std::shared_ptr<PrestamoController> controllerPrestamo;

    static BibliotecaFacade* instancia;

    BibliotecaFacade(std::shared_ptr<UsuarioController> usuarioCtrl,
                     std::shared_ptr<MaterialController> materialCtrl,
                     std::shared_ptr<PrestamoController> prestamoCtrl);

public:
    static void inicializar(std::shared_ptr<UsuarioController> usuarioCtrl,
                            std::shared_ptr<MaterialController> materialCtrl,
                            std::shared_ptr<PrestamoController> prestamoCtrl);

    static BibliotecaFacade* obtenerInstancia();

    struct ResultadoPrestamo {
        bool exito;
        QString mensaje;

        ResultadoPrestamo(bool ok, const QString& msg = "", int dias = 0)
            : exito(ok), mensaje(msg) {}
    };

    struct ResultadoEliminacion {
        bool exito;
        QString mensaje;
        QVector<QString> prestamosActivos;  // Lista de préstamos que impiden eliminar

        ResultadoEliminacion(bool ok, const QString& msg = "")
            : exito(ok), mensaje(msg) {}
    };

    ResultadoPrestamo realizarPrestamo(int usuarioId, int materialId, const QString& nomUsuario, const QString& nomMaterial,
                                       const QDate& fechaPrestamo, const QDate& fechaLimite);

    ResultadoPrestamo devolverPrestamo(int prestamoId);
    ResultadoEliminacion eliminarUsuario(int usuarioId);
    ResultadoEliminacion eliminarMaterial(int materialId);
    std::shared_ptr<UsuarioController> usuarios();
    std::shared_ptr<MaterialController> materiales();
    std::shared_ptr<PrestamoController> prestamos();
};

#endif // BIBLIOTECAFACADE_H
