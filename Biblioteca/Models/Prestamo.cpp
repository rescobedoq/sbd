#include "Prestamo.h"

Prestamo::Prestamo(int id, int usuarioId, int materialId, const QString& nombreUsuario,
                   const QString& nombreMaterial, const QDate& fechaPrestamo, const QDate& fechaLimite,
                   bool devuelto, const QDate& fechaDev)
    : id(id), usuarioId(usuarioId), materialId(materialId), fechaPrestamo(fechaPrestamo),
      nombreMaterial(nombreMaterial), nombreUsuario(nombreUsuario),
      fechaLimiteDevolucion(fechaLimite),  devuelto(devuelto), fechaDevolucion(fechaDev) {}

Prestamo::Prestamo(int usuarioId, int materialId, const QString& nombreUsuario,
                   const QString& nombreMaterial, const QDate& fechaPrestamo, const QDate& fechaLimite,
                   bool devuelto, const QDate& fechaDev)
    : usuarioId(usuarioId), materialId(materialId), fechaPrestamo(fechaPrestamo),
      nombreMaterial(nombreMaterial), nombreUsuario(nombreUsuario),
      fechaLimiteDevolucion(fechaLimite),  devuelto(devuelto), fechaDevolucion(fechaDev) {}

// Getters
int Prestamo::getId() const{
    return id;
}
int Prestamo::getUsuarioId() const{
    return usuarioId;
}
int Prestamo::getMaterialId() const{
    return materialId;
}
QString Prestamo::getNombreUsuario() const{
    return nombreUsuario;
}
QString Prestamo::getNombreMaterial() const{
    return nombreMaterial;
}
QDate Prestamo::getFechaPrestamo() const{
    return fechaPrestamo;
}
QDate Prestamo::getFechaLimiteDevolucion() const{
    return fechaLimiteDevolucion;
}
QDate Prestamo::getFechaDevolucion() const{
    return fechaDevolucion;
}
bool Prestamo::estaDevuelto() const {
    return devuelto;
}

// Setters
void Prestamo::setID(int id){
    this->id = id;
}
void Prestamo::setFechaDevolucionReal(const QDate& fecha){
    fechaDevolucion = fecha;
}
void Prestamo::setDevuelto(bool devuelto){
    this->devuelto = devuelto;
}

// Utilidades
bool Prestamo::estaVencido() const{
    return !devuelto && QDate::currentDate() > fechaLimiteDevolucion;
}
int Prestamo::diasRestantes() const{
    if (devuelto) return 0;
    return QDate::currentDate().daysTo(fechaLimiteDevolucion);
}
int Prestamo::diasRetraso() const{
    if (!devuelto && estaVencido()) {
        return fechaLimiteDevolucion.daysTo(QDate::currentDate());
    }
    return 0;
}
