#ifndef TESIS_H
#define TESIS_H

#include "material.h"

class Tesis : public Material {
private:
    QString universidad;

public:
    Tesis(int id, QString titulo, QString autor, int anio, bool disponible, QString universidad);
    QString obtenerTipo() const override;
    QString getUniversidad()const{return universidad;}
};

#endif // TESIS_H


