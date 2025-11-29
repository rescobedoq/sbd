#include <QApplication>
#include <QDebug>
#include <iostream>
#include "Models/Prestamo.h"
#include "Models/PrestamoDAO.h"
#include "Models/BaseDatos.h"
#include "Views/MaterialesView.h"
#include "Views/UsuariosView.h"
#include "Views/PrestamosView.h"
#include "Controllers/MaterialController.h"
#include "Models/LibroDAO.h"
#include "Controllers/BibliotecaFacade.h"
#include "Controllers/UsuarioController.h"
#include "Controllers/PrestamoController.h"
#include "Views/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString rutaDB = QCoreApplication::applicationDirPath() + "/../../Biblioteca.db";
    if (!BaseDatos::conectar(rutaDB)) {
        qDebug() << "Error: no se pudo conectar a la base de datos.";
        return -1;
    }

    auto usuarioController = std::make_shared<UsuarioController>();
    auto materialController = std::make_shared<MaterialController>();
    auto prestamoController = std::make_shared<PrestamoController>();

    BibliotecaFacade::inicializar(usuarioController, materialController, prestamoController);
    LibroDAO libroDAO;
    RevistaDAO revistaDAO;
    TesisDAO tesisDAO;
    PrestamoDAO prestamoDAO;
    //Codigo de prueba
    /*controllerUsuario.agregarUsuario(1, "Gustavo Turpo");
    controllerUsuario.agregarUsuario(2, "Daniel Torres");
    controllerUsuario.agregarUsuario(3, "María López");
    controllerUsuario.agregarUsuario(4, "Carlos Pérez");
    std::shared_ptr<Libro> libro;
    libro = std::make_shared<Libro>(2, "Libro 2", "Jose Lopez", 2025, 1, "Novela");
    libroDAO.insertarLibro(libro);

    std::shared_ptr<Revista> revista;
    revista = std::make_shared<Revista>(3, "Revista 1", "Jose Lopez", 2025, 1, 20);
    revistaDAO.insertarRevista(revista);

    std::shared_ptr<Tesis> tesis;
    tesis = std::make_shared<Tesis>(4, "Tesis 1", "Juan Perez", 2025, 1, "UNSA");
    tesisDAO.insertarTesis(tesis);

    QDate hoy = QDate::currentDate();
    QDate limite = hoy.addDays(7);
    std::shared_ptr<Prestamo> prestamo;
    prestamo = std::make_shared<Prestamo>(2, 2, 2, hoy, limite);
    prestamoDAO.insertarPrestamo(prestamo);
    prestamoDAO.registrarDevolucion(1, hoy);*/

    usuarioController->cargarUsuarios();
    materialController->cargarMateriales();
    prestamoController->cargarPrestamos();

    // Mostrando ventana de materiales
    /*UsuariosView *u = new UsuariosView();
    u->show();
    MaterialesView *m = new MaterialesView();
    m->show();
    PrestamosView *p = new PrestamosView();
    p->show();*/

    MainWindow *w = new MainWindow();
    w->show();

    return a.exec();
}
