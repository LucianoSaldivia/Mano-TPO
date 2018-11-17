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





void MainWindow::on_pushButton_RA_clicked()
{
    QString nombre_leido = QFileDialog::getOpenFileName(this, tr("open file"), "", "Text File (*.txt)");
    Archivo_para_leer.setFileName(nombre_leido);
    Archivo_para_leer.open(QIODevice::ReadOnly | QIODevice::Text);


   linea_archivo.setDevice(&Archivo_para_leer);

    QString linea = lee_linea_archivo();
    qDebug() << linea;

    linea = lee_linea_archivo();
    qDebug() << linea;

    linea = lee_linea_archivo();
    bool i=linea.isNull();  //para chequiar que lo ultimo que devuelve es NULL

    qDebug() << linea;
     qDebug() << i;

    Archivo_para_leer.close();
}

QString MainWindow::lee_linea_archivo(void)
{
    /*QTextStream linea_archivo(&Archivo_para_leer);*/
    QString text = linea_archivo.readLine();
    return text;
}
