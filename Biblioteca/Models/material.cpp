// Material.cpp
#include "material.h"

Material::Material(QString titulo, QString autor, int anio, bool disponible)
    : titulo(titulo), autor(autor), anio(anio), disponible(disponible) {}

QString Material::getTitulo() const {
    return titulo;
}

QString Material::getAutor() const {
    return autor;
}

int Material::getAnio() const {
    return anio;
}

bool Material::getDisponible() const {
    return disponible;
}

void Material::setDisponible(bool valor) {
    disponible = valor;
}
