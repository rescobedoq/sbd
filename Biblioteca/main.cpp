#include <QApplication>
#include <QDebug>
#include "Models/libro.h"
#include "Models/revista.h"
#include "Models/tesis.h"
#include "Models/usuario.h"
#include "Views/Materiales.h"
#include "Views/Usuarios.h"
#include "Controllers/controllerMaterial.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Mostrando ventana de materiales
    Usuarios u;
    u.show();
    Materiales m;
    m.show();
    return a.exec();

    // Crear controlador
    controllerMaterial controller;
    QString ruta = QCoreApplication::applicationDirPath() + "/../../materiales.json";

    // Cargar materiales desde JSON
    if (controller.cargarMateriales(ruta)) {
        qDebug() << "Materiales cargados exitosamente";

        // Mostrar materiales cargados
        for (const auto& material : controller.obtenerMateriales()) {
            qDebug() << "Tipo:" << material->obtenerTipo()
            << "- Título:" << material->getTitulo()
            << "- Autor:" << material->getAutor()
            << "- Año:" << material->getAnio()
            << "- Disponible:" << material->getDisponible();
        }
    }

    // Agregar un nuevo material
    auto nuevoLibro = std::make_shared<Libro>(
        "El Quijote", "Cervantes", 1605, true, "Novela"
        );
    controller.agregarMaterial(nuevoLibro);

    // Guardar materiales (con el nuevo material agregado)
    if (controller.guardarMateriales("materiales_salida.json")) {
        qDebug() << "Materiales guardados exitosamente";
    }
}




