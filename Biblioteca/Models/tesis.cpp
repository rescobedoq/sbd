#include "tesis.h"

Tesis::Tesis(int id, QString titulo, QString autor, int anio, bool disponible, QString universidad)
    : Material(id, titulo, autor, anio, disponible), universidad(universidad) {}

QString Tesis::obtenerTipo() const {
    return "Tesis";
}

