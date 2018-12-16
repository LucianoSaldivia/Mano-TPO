#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ventanamano.h"
#include <QSlider>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_MostrarManoBoton_clicked()
{
    QString TextoInicialDelBoton = "Mostrar Mano";

    if( TextoInicialDelBoton == ui->MostrarManoBoton->text() ){
        HandWindow = new VentanaMano(this);

        HandWindow->Actualizar( ui->Slider_Menor, ui->Slider_Anular, ui->Slider_Mayor, ui->Slider_Indice, ui->Slider_Pulgar );
        HandWindow->show();

        ui->MostrarManoBoton->setText("Ocultar Mano");
    }

    else{
        HandWindow->close();
        ui->MostrarManoBoton->setText("Mostrar Mano");
    }
}

void MainWindow::on_SalirBoton_clicked()
{
    this->close();
}

void MainWindow::on_Slider_Menor_valueChanged(int value)
{
    QString MensajeStatusBar;
    MensajeStatusBar = "Menor : ";
    MensajeStatusBar += QString::number( (value / 20 ));
    ui->statusBar->showMessage( MensajeStatusBar );
    HandWindow->Actualizar( ui->Slider_Menor, ui->Slider_Anular, ui->Slider_Mayor, ui->Slider_Indice, ui->Slider_Pulgar );
    HandWindow->show();
}

void MainWindow::on_Slider_Anular_valueChanged(int value)
{
    QString MensajeStatusBar;
    MensajeStatusBar = "Anular : ";
    MensajeStatusBar += QString::number( (value / 20 ));
    ui->statusBar->showMessage( MensajeStatusBar );
    HandWindow->Actualizar( ui->Slider_Menor, ui->Slider_Anular, ui->Slider_Mayor, ui->Slider_Indice, ui->Slider_Pulgar );
    HandWindow->show();
}

void MainWindow::on_Slider_Mayor_valueChanged(int value)
{
    QString MensajeStatusBar;
    MensajeStatusBar = "Mayor : ";
    MensajeStatusBar += QString::number( (value / 20 ));
    ui->statusBar->showMessage( MensajeStatusBar );
    HandWindow->Actualizar( ui->Slider_Menor, ui->Slider_Anular, ui->Slider_Mayor, ui->Slider_Indice, ui->Slider_Pulgar );
    HandWindow->show();
}

void MainWindow::on_Slider_Indice_valueChanged(int value)
{
    QString MensajeStatusBar;
    MensajeStatusBar = "Indice : ";
    MensajeStatusBar += QString::number( (value / 20 ));
    ui->statusBar->showMessage( MensajeStatusBar );
    HandWindow->Actualizar( ui->Slider_Menor, ui->Slider_Anular, ui->Slider_Mayor, ui->Slider_Indice, ui->Slider_Pulgar );
    HandWindow->show();
}

void MainWindow::on_Slider_Pulgar_valueChanged(int value)
{
    QString MensajeStatusBar;
    MensajeStatusBar = "Pulgar : ";
    MensajeStatusBar += QString::number( (value / 20 ));
    ui->statusBar->showMessage( MensajeStatusBar );
    HandWindow->Actualizar( ui->Slider_Menor, ui->Slider_Anular, ui->Slider_Mayor, ui->Slider_Indice, ui->Slider_Pulgar );
    HandWindow->show();
}
