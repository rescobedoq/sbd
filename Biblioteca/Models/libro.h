#ifndef LIBRO_H
#define LIBRO_H

#include "material.h"

class Libro : public Material {
private:
    QString genero;

public:
    Libro(int id, QString titulo, QString autor, int anio, bool disponible, QString genero);
    QString obtenerTipo() const override;
    QString getGenero() const {return genero;}
};

#endif // LIBRO_H

