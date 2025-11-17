#ifndef TESIS_H
#define TESIS_H

#include "material.h"

class Tesis : public Material {
private:
    QString universidad;

public:
    // Constructor por defecto
    Tesis() : Material(0, "", "", 0, true), universidad("") {}

    Tesis(int id, QString titulo, QString autor, int anio, bool disponible, QString universidad);

    QString obtenerTipo() const override;

    // GETTER
    QString getUniversidad() const { return universidad; }

    // SETTER (agregado)
    void setUniversidad(const QString& u) { universidad = u; }
};

#endif




