#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFile>
#include<QTextStream>
#include <QDebug>

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

void MainWindow::on_pushButton_clicked()
{

    QString Nombre_Archivo = ui->TextoNombre->text();
    QString Trama_Nueva_A_Guardar = ui->TextoArchivo->toPlainText();
    Crear_Archivo(Nombre_Archivo);
    Guardar_En_Archivo(Trama_Nueva_A_Guardar);
    Cerrar_Archivo();

}

void MainWindow::Crear_Archivo(QString Nombre_Archivo)
{

    if(!Nombre_Archivo.isNull())
    {
        Archivo.setFileName(Nombre_Archivo);

        Archivo.open(QIODevice::ReadWrite | QIODevice::Text); //Archivo de lectrura y escritura, y de texto
        if(!Archivo.isOpen())
        {
            qDebug() << "error, archivo no abierto";
        }
    }
    else
    {
        qDebug() << "error, se le debe agegar un nombre al archivo";
    }


}

void MainWindow::Guardar_En_Archivo(QString Trama_Nueva_A_Guardar)
{

    int posicion_$ = Trama_Nueva_A_Guardar.indexOf('$'); //identifico donde se ubica $

    Trama_Nueva_A_Guardar.remove(0, 1); //saco el primer caracter, el #
    Trama_Nueva_A_Guardar.remove(posicion_$-1, 1); //saco el caracter $

    QTextStream datosArchivo(&Archivo);
    datosArchivo << Trama_Nueva_A_Guardar << '\n' << endl;

}

void MainWindow::Cerrar_Archivo()
{
    Archivo.close();
}

