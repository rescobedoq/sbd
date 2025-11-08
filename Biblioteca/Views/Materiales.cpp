#include "Materiales.h"
#include "ui_Materiales.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QVector>
#include "../Models/libro.h"
#include "../Models/revista.h"
#include "../Models/tesis.h"
#include "../Models/material.h"

QVector<Material*> cargarMaterialesDesdeJSON(const QString& rutaArchivo) {
    QVector<Material*> materiales;

    QFile archivo(rutaArchivo);
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("No se pudo abrir el archivo JSON.");
        return materiales;
    }

    QByteArray data = archivo.readAll();
    archivo.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray array = doc.array();

    for (const QJsonValue& value : array) {
        QJsonObject obj = value.toObject();

        QString tipo = obj["tipo"].toString();
        QString titulo = obj["titulo"].toString();
        QString autor = obj["autor"].toString();
        int anio = obj["anio"].toInt();
        bool disponible = obj["disponible"].toBool();

        if (tipo == "Libro") {
            QString genero = obj["genero"].toString();
            materiales.append(new Libro(titulo, autor, anio, disponible, genero));
        } else if (tipo == "Revista") {
            int volumen = obj["volumen"].toInt();
            materiales.append(new Revista(titulo, autor, anio, disponible, volumen));
        } else if (tipo == "Tesis") {
            QString universidad = obj["universidad"].toString();
            materiales.append(new Tesis(titulo, autor, anio, disponible, universidad));
        }
    }

    return materiales;
}



Materiales::Materiales(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Materiales)
{
    ui->setupUi(this);
    QString ruta = QCoreApplication::applicationDirPath() + "/../../materiales.json";
    qDebug() << "Intentando abrir JSON en:" << ruta;
    QVector<Material*> lista = cargarMaterialesDesdeJSON(ruta);

    // Configura la tabla
    ui->tablaMateriales->setColumnCount(5);
    ui->tablaMateriales->setHorizontalHeaderLabels(
        {"Tipo", "Título", "Autor", "Año", "Disponible"}
        );
    ui->tablaMateriales->setRowCount(lista.size());

    // Llenar tabla
    for (int i = 0; i < lista.size(); ++i) {
        Material* m = lista[i];
        ui->tablaMateriales->setItem(i, 0, new QTableWidgetItem(m->obtenerTipo()));
        ui->tablaMateriales->setItem(i, 1, new QTableWidgetItem(m->getTitulo()));
        ui->tablaMateriales->setItem(i, 2, new QTableWidgetItem(m->getAutor()));
        ui->tablaMateriales->setItem(i, 3, new QTableWidgetItem(QString::number(m->getAnio())));
        ui->tablaMateriales->setItem(i, 4, new QTableWidgetItem(m->getDisponible()? "Sí" : "No"));
    }
    ui->tablaMateriales->resizeColumnsToContents();
    ui->tablaMateriales->resizeRowsToContents();
    ui->tablaMateriales->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    ui->tablaMateriales->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tablaMateriales->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    layout()->activate();   // recalcula el layout
    adjustSize();
    resize(width() + 20, height());
}

Materiales::~Materiales()
{
    delete ui;
}
