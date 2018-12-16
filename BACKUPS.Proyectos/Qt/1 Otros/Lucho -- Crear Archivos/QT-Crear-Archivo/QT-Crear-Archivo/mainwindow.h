#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    QFile Archivo;

    explicit MainWindow(QWidget *parent = 0);
    void Crear_Archivo(QString Nombre_Archivo);
    void Cerrar_Archivo();
    void Guardar_En_Archivo(QString Trama_Nueva_A_Guardar);

    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
