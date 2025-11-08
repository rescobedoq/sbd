#ifndef MATERIAL_H
#define MATERIAL_H
#include <QString>

class Material {
protected:
    QString titulo;
    QString autor;
    int anio;
    bool disponible;

public:
    Material(QString titulo, QString autor, int anio, bool disponible);
    virtual QString obtenerTipo() const = 0;
    QString getTitulo() const;
    QString getAutor() const;
    int getAnio() const;
    bool getDisponible() const;
    void setDisponible(bool valor);
};

#endif // MATERIAL_H


