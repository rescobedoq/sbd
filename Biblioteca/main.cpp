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

    // Crear controlador
    controllerMaterial controller;

    // Cargar materiales desde JSON
    if (controller.cargarMateriales("materiales.json")) {
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

    // Mostrar ventana de usuarios
    Usuarios w;
    w.show();

    return a.exec();
}




