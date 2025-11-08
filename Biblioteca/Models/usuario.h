// usuario.h
#ifndef USUARIO_H
#define USUARIO_H

#include <QString>

class Usuario {
private:
    QString nombre;
    int id;

public:
    Usuario(QString nombre, int id);
    QString getNombre() const;
    int getId() const;
};

#endif // USUARIO_H




