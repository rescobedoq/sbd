#ifndef REVISTADAO_H
#define REVISTADAO_H

#include "MaterialDAO.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QDebug>

class RevistaDAO : public MaterialDAO {
public:
    bool insertar(const std::shared_ptr<Revista>& revista);
    bool actualizar(const std::shared_ptr<Revista>& revista);
    bool eliminar(int id);
    QVector<std::shared_ptr<Revista>> obtenerRevistas();
};

#endif // REVISTADAO_H

