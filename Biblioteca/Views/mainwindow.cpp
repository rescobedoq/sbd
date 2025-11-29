#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->btnGestUsuarios->setIcon(QIcon(":/Iconos/person.svg"));
    ui->btnGestUsuarios->setIconSize(QSize(32, 32));

    ui->btnGestMateriales->setIcon(QIcon(":/Iconos/book.svg"));
    ui->btnGestMateriales->setIconSize(QSize(32, 32));

    ui->btnGestPrestamos->setIcon(QIcon(":/Iconos/pencil-square.svg"));
    ui->btnGestPrestamos->setIconSize(QSize(32, 32));

    // Conectar señales (si no las conectaste desde Qt Designer)
    connect(ui->btnGestUsuarios, &QPushButton::clicked,
            this, &MainWindow::on_btnUsuarios_clicked);
    connect(ui->btnGestMateriales, &QPushButton::clicked,
            this, &MainWindow::on_btnMateriales_clicked);
    connect(ui->btnGestPrestamos, &QPushButton::clicked,
            this, &MainWindow::on_btnPrestamos_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnUsuarios_clicked()
{
    if (!usuariosView)
        usuariosView = new UsuariosView();
    usuariosView->show();
    usuariosView->raise();
    usuariosView->activateWindow();
}

void MainWindow::on_btnMateriales_clicked()
{
    if (!materialesView)
        materialesView = new MaterialesView();
    materialesView->show();
    materialesView->raise();
    materialesView->activateWindow();
}

void MainWindow::on_btnPrestamos_clicked()
{
    if (!prestamosView)
        prestamosView = new PrestamosView();
    prestamosView->show();
    prestamosView->raise();
    prestamosView->activateWindow();
}
