#ifndef BASEDATOS_H
#define BASEDATOS_H
#include <QtSql>
#include <QSqlDatabase>

class BaseDatos
{
public:
    static bool conectar(const QString& rutaBD);
    static QSqlDatabase& getBD();
private:
    static QSqlDatabase bd;
};


#endif // BASEDATOS_H
