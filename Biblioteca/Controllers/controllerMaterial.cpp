#include "controllerMaterial.h"
#include "../Models/libro.h"
#include "../Models/revista.h"
#include "../Models/tesis.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

controllerMaterial::controllerMaterial() {}

bool controllerMaterial::cargarMateriales(const QString& archivo) {
    QFile file(archivo);

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error al abrir el archivo:" << archivo;
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);

    if (!doc.isArray()) {
        qDebug() << "El archivo JSON no contiene un array";
        return false;
    }

    QJsonArray jsonArray = doc.array();
    materiales.clear();

    for (const QJsonValue& value : jsonArray) {
        if (!value.isObject()) continue;

        QJsonObject obj = value.toObject();

        QString tipo = obj["tipo"].toString();
        QString titulo = obj["titulo"].toString();
        QString autor = obj["autor"].toString();
        int anio = obj["anio"].toInt();
        bool disponible = obj["disponible"].toBool();

        std::shared_ptr<Material> material;

        if (tipo == "Libro") {
            QString genero = obj["genero"].toString("Desconocido");
            material = std::make_shared<Libro>(titulo, autor, anio, disponible, genero);
        }
        else if (tipo == "Revista") {
            int volumen = obj["volumen"].toInt(1);
            material = std::make_shared<Revista>(titulo, autor, anio, disponible, volumen);
        }
        else if (tipo == "Tesis") {
            QString universidad = obj["universidad"].toString("Desconocida");
            material = std::make_shared<Tesis>(titulo, autor, anio, disponible, universidad);
        }

        if (material) {
            materiales.append(material);
        }
    }

    qDebug() << "Materiales cargados:" << materiales.size();
    return true;
}

bool controllerMaterial::guardarMateriales(const QString& archivo) {
    QJsonArray jsonArray;

    for (const auto& material : materiales) {
        QJsonObject obj;
        obj["tipo"] = material->obtenerTipo();
        obj["titulo"] = material->getTitulo();
        obj["autor"] = material->getAutor();
        obj["anio"] = material->getAnio();
        obj["disponible"] = material->getDisponible();

        // Agregar campos específicos según el tipo
        if (material->obtenerTipo() == "Libro") {
            Libro* libro = dynamic_cast<Libro*>(material.get());
            if (libro) obj["genero"] = libro->getGenero();
        }
        else if (material->obtenerTipo() == "Revista") {
            Revista* revista = dynamic_cast<Revista*>(material.get());
            if (revista) obj["volumen"] = revista->getVolumen();
        }
        else if (material->obtenerTipo() == "Tesis") {
            Tesis* tesis = dynamic_cast<Tesis*>(material.get());
            if (tesis) obj["universidad"] = tesis->getUniversidad();
        }

        jsonArray.append(obj);
    }

    QJsonDocument doc(jsonArray);

    QFile file(archivo);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Error al abrir el archivo para escritura:" << archivo;
        return false;
    }

    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();

    qDebug() << "Materiales guardados:" << materiales.size();
    return true;
}

void controllerMaterial::agregarMaterial(std::shared_ptr<Material> material) {
    materiales.append(material);
}

void controllerMaterial::eliminarMaterial(int indice) {
    if (indice >= 0 && indice < materiales.size()) {
        materiales.remove(indice);
    }
}

QVector<std::shared_ptr<Material>>& controllerMaterial::obtenerMateriales() {
    return materiales;
}
