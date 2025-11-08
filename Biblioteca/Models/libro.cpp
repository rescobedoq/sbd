#include "libro.h"

Libro::Libro(QString titulo, QString autor, int anio, bool disponible, QString genero)
    : Material(titulo, autor, anio, disponible), genero(genero) {}

QString Libro::obtenerTipo() const {
    return "Libro";
}
