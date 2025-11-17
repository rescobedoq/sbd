#ifndef MATERIAL_H
#define MATERIAL_H

#include <QString>

class Material {
protected:
    int id;
    QString titulo;
    QString autor;
    int anio;
    bool disponible;

public:
    Material(int id, QString titulo, QString autor, int anio, bool disponible);

    // GETTERS
    int getID() const;
    QString getTitulo() const;
    QString getAutor() const;
    int getAnio() const;
    bool getDisponible() const;

    // SETTERS NUEVOS
    void setID(int nuevoID);
    void setTitulo(const QString& t);
    void setAutor(const QString& a);
    void setAnio(int n);
    void setDisponible(bool valor);

    virtual QString obtenerTipo() const = 0;
};

#endif

