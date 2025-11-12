#include "revista.h"

Revista::Revista(int id, QString titulo, QString autor, int anio, bool disponible, int volumen)
    : Material(id, titulo, autor, anio, disponible), volumen(volumen) {}

QString Revista::obtenerTipo() const {
    return "Revista";
}
