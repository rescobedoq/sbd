#include "tesis.h"

Tesis::Tesis(QString titulo, QString autor, int anio, bool disponible, QString universidad)
    : Material(titulo, autor, anio, disponible), universidad(universidad) {}

QString Tesis::obtenerTipo() const {
    return "Tesis";
}

