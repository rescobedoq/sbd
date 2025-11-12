#ifndef REVISTADAO_H
#define REVISTADAO_H
#include "MaterialDAO.h"
#include <QSqlError>

class RevistaDAO : public MaterialDAO {
public:
    bool insertarRevista(const std::shared_ptr<Revista>& revista);
    bool actualizarRevista(const std::shared_ptr<Revista>& revista);
    QVector<std::shared_ptr<Revista>> obtenerRevistas();
};

#endif // REVISTADAO_H
