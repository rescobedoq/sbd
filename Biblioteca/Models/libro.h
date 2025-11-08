#ifndef LIBRO_H
#define LIBRO_H

#include "material.h"

class Libro : public Material {
private:
    QString genero;

public:
    Libro(QString titulo, QString autor, int anio, bool disponible, QString genero);
    QString obtenerTipo() const override;
};

#endif // LIBRO_H

