#include "usuario.h"

usuario::usuario(QString nombre, int id)
    : nombre(nombre), id(id) {}

QString usuario::getNombre() const {
    return nombre;
}

int usuario::getId() const {
    return id;
}
