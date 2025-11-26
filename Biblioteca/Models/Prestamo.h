#ifndef PRESTAMO_H
#define PRESTAMO_H
#include <QDate>

class Prestamo {
private:
    int id;
    int usuarioId;
    int materialId;
    QString nombreUsuario;
    QString nombreMaterial;
    QDate fechaPrestamo;
    QDate fechaLimiteDevolucion;
    QDate fechaDevolucion;  // NULL si aún no se devolvió
    bool devuelto;

public:
    // Constructor para el caché
    Prestamo(int id, int usuarioId, int materialId, const QString& nombreUsuario,
             const QString& nombreMaterial, const QDate& fechaPrestamo, const QDate& fechaLimite,
             bool devuelto = false, const QDate& fechaDev = QDate());
    // Constructor para el DAO
    Prestamo(int usuarioId, int materialId, const QString& nombreUsuario,
             const QString& nombreMaterial, const QDate& fechaPrestamo, const QDate& fechaLimite,
             bool devuelto = false, const QDate& fechaDev = QDate());

    // Getters
    int getId() const;
    int getUsuarioId() const;
    int getMaterialId() const;
    QString getNombreUsuario() const;
    QString getNombreMaterial() const;
    QDate getFechaPrestamo() const;
    QDate getFechaLimiteDevolucion() const;
    QDate getFechaDevolucion() const;
    bool estaDevuelto() const;

    // Setters (solo para devolución)
    void setID(int id);
    void setFechaDevolucionReal(const QDate& fecha);
    void setDevuelto(bool devuelto);

    // Utilidades
    bool estaVencido() const;
    int diasRestantes() const;
    int diasRetraso() const;
};

#endif // PRESTAMO_H
