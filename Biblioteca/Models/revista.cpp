#include "revista.h"

revista::revista(QString titulo, QString autor, int anio, int volumen)
    : material(titulo, autor, anio), volumen(volumen) {}

QString revista::obtenerTipo() const {
    return "Revista";
}
