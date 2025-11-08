#include "usuario.h"

Usuario::Usuario(QString nombre, int id)
    : nombre(nombre), id(id) {}

QString Usuario::getNombre() const {
    return nombre;
}

int Usuario::getId() const {
    return id;
}
