#include "tesis.h"

tesis::tesis(QString titulo, QString autor, int anio, QString universidad)
    : material(titulo, autor, anio), universidad(universidad) {}

QString tesis::obtenerTipo() const {
    return "Tesis";
}

