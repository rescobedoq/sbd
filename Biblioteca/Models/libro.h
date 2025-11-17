#ifndef LIBRO_H
#define LIBRO_H

#include "material.h"

class Libro : public Material {
private:
    QString genero;

public:
    // Constructor por defecto necesario para el Factory Method
    Libro() : Material(0, "", "", 0, true), genero("") {}

    Libro(int id, QString titulo, QString autor, int anio, bool disponible, QString genero);

    QString obtenerTipo() const override;

    // GETTER
    QString getGenero() const { return genero; }

    // SETTER (agregado)
    void setGenero(const QString& g) { genero = g; }
};

#endif



