#ifndef TESIS_H
#define TESIS_H

#include "material.h"

class Tesis : public Material {
private:
    QString universidad;

public:
    Tesis(QString titulo, QString autor, int anio, bool disponible, QString universidad);
    QString obtenerTipo() const override;
};

#endif // TESIS_H


