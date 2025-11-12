#include "libro.h"

Libro::Libro(int id, QString titulo, QString autor, int anio, bool disponible, QString genero)
    : Material(id, titulo, autor, anio, disponible), genero(genero) {}

QString Libro::obtenerTipo() const {
    return "Libro";
}
