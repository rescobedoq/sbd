#include "usuario.h"

Usuario::Usuario(int id, QString nombre)
    : id(id), nombre(nombre) {}

QString Usuario::getNombre() const {
    return nombre;
}

int Usuario::getId() const {
    return id;
}
