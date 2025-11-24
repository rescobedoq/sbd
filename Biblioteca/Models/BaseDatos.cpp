#include "BaseDatos.h"

QSqlDatabase BaseDatos::bd = QSqlDatabase();  // definición del miembro estático

bool BaseDatos::conectar(const QString& rutaBD) {
    if (bd.isOpen())
        return true;

    bd = QSqlDatabase::addDatabase("QSQLITE");
    bd.setDatabaseName(rutaBD);

    if (!bd.open()) {
        qDebug() << "Error al abrir la base de datos:" << bd.lastError().text();
        return false;
    }

    QSqlQuery q(bd);
    q.exec("PRAGMA foreign_keys = ON;");

    qDebug() << "Conexión a SQLite exitosa.";
    return true;
}

QSqlDatabase& BaseDatos::getBD() {
    return bd;
}
