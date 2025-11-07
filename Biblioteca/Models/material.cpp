// Material.cpp
#include "material.h"

material::material(QString titulo, QString autor, int anio)
    : titulo(titulo), autor(autor), anio(anio) {}

QString material::getTitulo() const {
    return titulo;
}

QString material::getAutor() const {
    return autor;
}

int material::getAnio() const {
    return anio;
}
