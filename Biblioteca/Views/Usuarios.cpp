#include "Usuarios.h"
#include "ui_Usuarios.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QVector>
#include "../Models/usuario.h"

QVector<Usuario*> cargarUsuariosDesdeJSON(const QString& rutaArchivo) {
    QVector<Usuario*> usuarios;

    QFile archivo(rutaArchivo);
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("No se pudo abrir el archivo JSON.");
        return usuarios;
    }

    QByteArray data = archivo.readAll();
    archivo.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray array = doc.array();

    for (const QJsonValue& value : array) {
        QJsonObject obj = value.toObject();
        int id = obj["id"].toInt();
        QString nombre = obj["nombre"].toString();
        usuarios.append(new Usuario(nombre, id));
    }

    return usuarios;
}
Usuarios::Usuarios(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Usuarios)
{
    ui->setupUi(this);
    QString ruta = QCoreApplication::applicationDirPath() + "/../../usuarios.json";
    qDebug() << "Intentando abrir JSON en:" << ruta;
    QVector<Usuario*> lista = cargarUsuariosDesdeJSON(ruta);

    // Configura la tabla
    ui->tablaUsuarios->setColumnCount(2);
    ui->tablaUsuarios->setHorizontalHeaderLabels(
        {"ID", "Nombre"}
        );
    ui->tablaUsuarios->setRowCount(lista.size());

    // Llenar tabla
    for (int i = 0; i < lista.size(); ++i) {
        Usuario* u = lista[i];
        ui->tablaUsuarios->setItem(i, 0, new QTableWidgetItem(QString::number(u->getId())));
        ui->tablaUsuarios->setItem(i, 1, new QTableWidgetItem(u->getNombre()));
    }
    ui->tablaUsuarios->resizeColumnsToContents();
    ui->tablaUsuarios->resizeRowsToContents();
    ui->tablaUsuarios->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    ui->tablaUsuarios->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tablaUsuarios->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    layout()->activate();   // recalcula el layout
    adjustSize();
    resize(width() + 20, height());
}

Usuarios::~Usuarios()
{
    delete ui;
}
