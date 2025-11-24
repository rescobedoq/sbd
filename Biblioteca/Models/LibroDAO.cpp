#include "LibroDAO.h"
#include "BaseDatos.h"
// Inserta libro (inserta en Material y en tabla Libro)
bool LibroDAO::insertar(const std::shared_ptr<Libro>& libro){
    QSqlDatabase db = BaseDatos::getBD();

    if (!db.transaction()) {
        qDebug() << "No se pudo iniciar transacción en LibroDAO::insertar()";
        return false;
    }

    // Insertar en tabla Material (usa método protegido de la clase base)
    int idGenerado;
    if (!insertarEnMaterial(libro, idGenerado)) {
        db.rollback();
        return false;
    }

    // Insertar en tabla Libro
    QSqlQuery query(BaseDatos::getBD());
    query.prepare("INSERT INTO Libro (id_material, genero) VALUES (:id, :genero)");
    query.bindValue(":id", idGenerado);
    query.bindValue(":genero", libro->getGenero());

    if (!query.exec()) {
        qDebug() << "Error SQL en LibroDAO::insertar():" << query.lastError().text();
        db.rollback();
        return false;
    }

    if (!db.commit()) {
        qDebug() << "Error al confirmar transacción en LibroDAO::insertar()";
        db.rollback();
        return false;
    }

    return true;
}

bool LibroDAO::actualizar(const std::shared_ptr<Libro>& libro) {
    // Reutiliza el método de la clase base que ya maneja transacciones y actualiza la tabla Material
    // Si MaterialDAO::actualizar también actualiza las tablas específicas, perfecto;
    // si no, deberías implementar aquí la actualización específica de la tabla Libro.
    bool ok = MaterialDAO::actualizar(libro);
    if (!ok) return false;

    // Actualizar campos específicos de Libro (tabla Libro)
    QSqlQuery query(BaseDatos::getBD());
    query.prepare("UPDATE Libro SET genero = :genero WHERE id_material = :id");
    query.bindValue(":genero", libro->getGenero());
    query.bindValue(":id", libro->getID());

    if (!query.exec()) {
        qDebug() << "Error SQL en LibroDAO::actualizar():" << query.lastError().text();
        return false;
    }
    return true;
}

bool LibroDAO::eliminar(int id) {
    // Primero eliminar de tabla Libro y luego de Material (o usar método de la base)
    QSqlDatabase db = BaseDatos::getBD();
    if (!db.transaction()) {
        qDebug() << "No se pudo iniciar transacción en LibroDAO::eliminar()";
        return false;
    }

    QSqlQuery q1(BaseDatos::getBD());
    q1.prepare("DELETE FROM Libro WHERE id_material = :id");
    q1.bindValue(":id", id);
    if (!q1.exec()) {
        qDebug() << "Error SQL en LibroDAO::eliminar() (tabla Libro):" << q1.lastError().text();
        db.rollback();
        return false;
    }

    // Usar el método de la clase base para eliminar de Material
    if (!MaterialDAO::eliminar(id)) {
        db.rollback();
        return false;
    }

    if (!db.commit()) {
        qDebug() << "Error al confirmar transacción en LibroDAO::eliminar()";
        db.rollback();
        return false;
    }

    return true;
}

QVector<std::shared_ptr<Libro>> LibroDAO::obtenerLibros() {
    QVector<std::shared_ptr<Libro>> lista;

    QSqlQuery query(BaseDatos::getBD());
    query.prepare(
        "SELECT m.id_material, m.titulo, m.autor, m.anio_publicacion, m.disponible, l.genero "
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
