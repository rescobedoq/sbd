// usuario.h
#ifndef USUARIO_H
#define USUARIO_H

#include <QString>

class usuario {
private:
    QString nombre;
    int id;

public:
    usuario(QString nombre, int id);
    QString getNombre() const;
    int getId() const;
};

#endif // USUARIO_H




