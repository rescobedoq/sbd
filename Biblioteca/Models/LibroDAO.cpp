#include "LibroDAO.h"

bool LibroDAO::insertarLibro(const std::shared_ptr<Libro>& libro) {
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.transaction()) {
        qDebug() << "No se pudo iniciar transacción en LibroDAO::insertarLibro()";
        return false;
    }

    // Insertar en tabla Material (usa método protegido de la clase base)
    int idGenerado;
    if (!insertarEnMaterial(libro, idGenerado)) {
        db.rollback();
        return false;
    }

    // Insertar en tabla Libro
    QSqlQuery query;
    query.prepare("INSERT INTO Libro (id_material, genero) VALUES (:id, :genero)");
    query.bindValue(":id", idGenerado);
    query.bindValue(":genero", libro->getGenero());

    if (!query.exec()) {
        qDebug() << "Error SQL en LibroDAO::insertarLibro():" << query.lastError().text();
        db.rollback();
        return false;
    }

    if (!db.commit()) {
        qDebug() << "Error al confirmar transacción en LibroDAO::insertarLibro()";
        db.rollback();
        return false;
    }

    return true;
}

bool LibroDAO::actualizarLibro(const std::shared_ptr<Libro>& libro) {
    // Reutiliza el método de la clase base que ya maneja transacciones
    return MaterialDAO::actualizar(libro);
}

QVector<std::shared_ptr<Libro>> LibroDAO::obtenerLibros() {
    QVector<std::shared_ptr<Libro>> lista;

    QSqlQuery query;
    query.prepare(
        "SELECT m.*, l.genero "
        "FROM Material m "
        "INNER JOIN Libro l ON m.id_material = l.id_material"
        );

    if (!query.exec()) {
        qDebug() << "Error SQL en LibroDAO::obtenerLibros():" << query.lastError().text();
        return lista;
    }

    while (query.next()) {
        lista.append(std::make_shared<Libro>(
            query.value("id_material").toInt(),
            query.value("titulo").toString(),
            query.value("autor").toString(),
            query.value("anio_publicacion").toInt(),
            query.value("disponible").toBool(),
            query.value("genero").toString()
            ));
    }

    return lista;
}
