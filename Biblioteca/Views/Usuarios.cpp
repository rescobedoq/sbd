#include "Usuarios.h"
#include "ui_Usuarios.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QVector>
#include "../Models/usuario.h"
#include "../Controllers/UsuarioController.h"

Usuarios::Usuarios(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Usuarios)
{
    ui->setupUi(this);
    UsuarioController controller;
    QString ruta = QCoreApplication::applicationDirPath() + "/../../usuarios.json";
    controller.cargarUsuarios(ruta);

    QVector<std::shared_ptr<Usuario>>& usuariosRef = controller.obtenerUsuarios();

    // Configura la tabla
    ui->tablaUsuarios->setColumnCount(2);
    ui->tablaUsuarios->setHorizontalHeaderLabels(
        {"ID", "Nombre"}
        );
    ui->tablaUsuarios->setRowCount(usuariosRef.size());

    // Llenar tabla
    for (int i = 0; i < usuariosRef.size(); ++i) {
        std::shared_ptr<Usuario> u = usuariosRef[i];
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
