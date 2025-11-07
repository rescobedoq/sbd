#ifndef REVISTA_H
#define REVISTA_H

#include "material.h"

class revista : public material {
private:
    int volumen;

public:
    revista(QString titulo, QString autor, int anio, int volumen);
    QString obtenerTipo() const override;
};

#endif // REVISTA_H
