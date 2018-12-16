#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ventanamano.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_MostrarManoBoton_clicked();

    void on_SalirBoton_clicked();

    void on_Slider_Menor_valueChanged(int value);


    void on_Slider_Anular_valueChanged(int value);

    void on_Slider_Mayor_valueChanged(int value);

    void on_Slider_Indice_valueChanged(int value);

    void on_Slider_Pulgar_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    VentanaMano *HandWindow;
};

#endif // MAINWINDOW_H
