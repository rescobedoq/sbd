#ifndef MATERIAL_H
#define MATERIAL_H
#include <QString>

class material {
protected:
    QString titulo;
    QString autor;
    int anio;
    bool disponible;

public:
    material(QString titulo, QString autor, int anio);
    virtual QString obtenerTipo() const = 0;
    QString getTitulo() const;
    QString getAutor() const;
    int getAnio() const;
    bool getDisponible() const;
    void setDisponible(bool valor);
};

#endif // MATERIAL_H


