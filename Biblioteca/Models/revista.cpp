#include "revista.h"

Revista::Revista(QString titulo, QString autor, int anio, bool disponible, int volumen)
    : Material(titulo, autor, anio, disponible), volumen(volumen) {}

QString Revista::obtenerTipo() const {
    return "Revista";
}
