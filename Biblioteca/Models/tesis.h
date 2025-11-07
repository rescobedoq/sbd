#ifndef TESIS_H
#define TESIS_H

#include "material.h"

class tesis : public material {
private:
    QString universidad;

public:
    tesis(QString titulo, QString autor, int anio, QString universidad);
    QString obtenerTipo() const override;
};

#endif // TESIS_H


