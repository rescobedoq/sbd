#include <QApplication>
#include <QDebug>
#include "Models/libro.h"
#include "Models/revista.h"
#include "Models/tesis.h"
#include "Models/usuario.h"
#include "Models/BaseDatos.h"
#include "Views/Materiales.h"
#include "Views/Usuarios.h"
#include "Controllers/MaterialController.h"
#include "Models/LibroDAO.h"
#include "Controllers/UsuarioController.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString rutaDB = QCoreApplication::applicationDirPath() + "/../../Biblioteca.db";
    if (!BaseDatos::conectar(rutaDB)) {
        qDebug() << "❌ Error: no se pudo conectar a la base de datos.";
        return -1;
    }

    UsuarioController controllerUsuario;
    MaterialController controllerMateriales;
    LibroDAO libroDAO;
    RevistaDAO revistaDAO;
    TesisDAO tesisDAO;
    controllerUsuario.agregarUsuario(1, "Gustavo Turpo");
    controllerUsuario.agregarUsuario(2, "Daniel Torres");
    controllerUsuario.agregarUsuario(3, "María López");
    controllerUsuario.agregarUsuario(4, "Carlos Pérez");
    /*
    std::shared_ptr<Libro> libro;
    libro = std::make_shared<Libro>(2, "Libro 2", "Jose Lopez", 2025, 1, "Novela");
    libroDAO.insertarLibro(libro);

    std::shared_ptr<Revista> revista;
    revista = std::make_shared<Revista>(3, "Revista 1", "Jose Lopez", 2025, 1, 20);
    revistaDAO.insertarRevista(revista);

    std::shared_ptr<Tesis> tesis;
    tesis = std::make_shared<Tesis>(4, "Tesis 1", "Juan Perez", 2025, 1, "UNSA");
    tesisDAO.insertarTesis(tesis);
    */
    controllerUsuario.cargarUsuarios();
    controllerMateriales.cargarMateriales();

    // Mostrando ventana de materiales
    Usuarios u(&controllerUsuario);
    u.show();
    Materiales m(&controllerMateriales);
    m.show();
    return a.exec();


}




