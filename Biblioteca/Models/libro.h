#ifndef LIBRO_H
#define LIBRO_H

#include "material.h"

class libro : public material {
private:
    QString genero;

public:
    libro(QString titulo, QString autor, int anio, QString genero);
    QString obtenerTipo() const override;
};

#endif // LIBRO_H

