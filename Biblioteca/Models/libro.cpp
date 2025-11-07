#include "libro.h"

libro::libro(QString titulo, QString autor, int anio, QString genero)
    : material(titulo, autor, anio), genero(genero) {}

QString libro::obtenerTipo() const {
    return "Libro";
}

