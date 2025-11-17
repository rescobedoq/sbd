#ifndef REVISTA_H
#define REVISTA_H

#include "material.h"

class Revista : public Material {
private:
    int volumen;

public:
    // Constructor por defecto
    Revista() : Material(0, "", "", 0, true), volumen(0) {}

    Revista(int id, QString titulo, QString autor, int anio, bool disponible, int volumen);

    QString obtenerTipo() const override;

    // GETTER
    int getVolumen() const { return volumen; }

    // SETTER (agregado)
    void setVolumen(int v) { volumen = v; }
};

#endif


