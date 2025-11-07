#include <QCoreApplication>
#include <QDebug>
#include "Models/libro.h"
#include "Models/revista.h"
#include "Models/tesis.h"
#include "Models/usuario.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    libro l("El Quijote", "Cervantes", 1605, "Novela");
    revista r("National Geographic", "Varios", 2023, 45);
    tesis t("IA en Educación", "Jean", 2024, "UTP");

    usuario u("Carlos", 1);

    qDebug() << "Tipo:" << l.obtenerTipo() << "- Título:" << l.getTitulo();
    qDebug() << "Tipo:" << r.obtenerTipo() << "- Título:" << r.getTitulo();
    qDebug() << "Tipo:" << t.obtenerTipo() << "- Título:" << t.getTitulo();
    qDebug() << "Usuario:" << u.getNombre() << "- ID:" << u.getId();

    return 0;
}




