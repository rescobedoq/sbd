#ifndef TESISDAO_H
#define TESISDAO_H
#include "MaterialDAO.h"
#include <QSqlError>

class TesisDAO : public MaterialDAO {
public:
    bool insertarTesis(const std::shared_ptr<Tesis>& tesis);
    bool actualizarTesis(const std::shared_ptr<Tesis>& tesis);
    QVector<std::shared_ptr<Tesis>> obtenerTesis();
};

#endif // TESISDAO_H
