#ifndef PRESTAMOS_H
#define PRESTAMOS_H

#include <QWidget>
#include "../Models/Prestamo.h"

namespace Ui {
class Prestamos;
}

class Prestamos : public QWidget
{
    Q_OBJECT

public:
    explicit Prestamos(QWidget *parent = nullptr);
    void cargarTabla(const QVector<std::shared_ptr<Prestamo>>& usuarios);
    ~Prestamos();

private:
    Ui::Prestamos *ui;

private slots:
    void on_btnNuevoPrestamo_clicked();
    void on_btnRegistrarDevolucion_clicked();
};

#endif // PRESTAMOS_H
