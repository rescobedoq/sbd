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

    // ---------------------------------------
    // CONTROLADORES
    // ---------------------------------------
    UsuarioController controllerUsuario;
    MaterialController controllerMateriales;

    // ---------------------------------------
    // DAOs
    // ---------------------------------------
    LibroDAO libroDAO;
    RevistaDAO revistaDAO;
    TesisDAO tesisDAO;

    // ---------------------------------------
    // USUARIOS DE PRUEBA
    // ---------------------------------------
    controllerUsuario.agregarUsuario(1, "Gustavo Turpo");
    controllerUsuario.agregarUsuario(2, "Daniel Torres");
    controllerUsuario.agregarUsuario(3, "María López");
    controllerUsuario.agregarUsuario(4, "Carlos Pérez");

    controllerUsuario.cargarUsuarios();

    // ---------------------------------------
    // Cargar materiales ANTES DE abrir ventana
    // ---------------------------------------
    controllerMateriales.cargarMateriales();  //

    // ---------------------------------------
    // Vistas
    // ---------------------------------------
    Usuarios u(&controllerUsuario);
    u.show();

    Materiales m(&controllerMateriales);
    m.show();

    return a.exec();
}





