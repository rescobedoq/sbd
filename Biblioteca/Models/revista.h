#ifndef REVISTA_H
#define REVISTA_H

#include "material.h"

class Revista : public Material {
private:
    int volumen;

public:
    Revista(QString titulo, QString autor, int anio, bool disponible, int volumen);
    QString obtenerTipo() const override;
    int getVolumen()const{return volumen;}
};

#endif // REVISTA_H
