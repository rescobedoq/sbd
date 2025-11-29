#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../Views/UsuariosView.h"
#include "../Views/MaterialesView.h"
#include "../Views/PrestamosView.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnUsuarios_clicked();
    void on_btnMateriales_clicked();
    void on_btnPrestamos_clicked();

private:
    Ui::MainWindow *ui;

    UsuariosView *usuariosView = nullptr;
    MaterialesView *materialesView = nullptr;
    PrestamosView *prestamosView = nullptr;
};
#endif // MAINWINDOW_H
