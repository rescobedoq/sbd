#include <QApplication>
#include <QDebug>
#include "Models/libro.h"
#include "Models/revista.h"
#include "Models/tesis.h"
#include "Models/usuario.h"
#include "Views/Materiales.h"
#include "Views/Usuarios.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Usuarios w;
    w.show();
    return a.exec();

    Libro l("El Quijote", "Cervantes", 1605, true, "Novela");
    Revista r("National Geographic", "Varios", 2023,true, 45);
    Tesis t("IA en Educación", "Jean", 2024, true, "UTP");

    Usuario u("Carlos", 1);

    qDebug() << "Tipo:" << l.obtenerTipo() << "- Título:" << l.getTitulo();
    qDebug() << "Tipo:" << r.obtenerTipo() << "- Título:" << r.getTitulo();
    qDebug() << "Tipo:" << t.obtenerTipo() << "- Título:" << t.getTitulo();
    qDebug() << "Usuario:" << u.getNombre() << "- ID:" << u.getId();

    return 0;
}




