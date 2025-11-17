#ifndef TESISDAO_H
#define TESISDAO_H

#include "MaterialDAO.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QDebug>

class TesisDAO : public MaterialDAO {
public:
    bool insertar(const std::shared_ptr<Tesis>& tesis);
    bool actualizar(const std::shared_ptr<Tesis>& tesis);
    bool eliminar(int id);
    QVector<std::shared_ptr<Tesis>> obtenerTesis();
};

#endif // TESISDAO_H
