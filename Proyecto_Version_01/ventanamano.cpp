#include "ventanamano.h"
#include "ui_ventanamano.h"

VentanaMano::VentanaMano(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VentanaMano)
{
    ui->setupUi(this);

    Label_Ancho = ui->Imagen_Label_1->width();
    Label_Alto = ui->Imagen_Label_1->height();

    /*
    QPixmap I_Base(":Resource/Imagenes/Base/Base.png");
    QPixmap I_Menor(":Resource/Imagenes/Menores/Menor-Normal.png");
    QPixmap I_Anular(":Resource/Imagenes/Anulares/Anular-Normal.png");
    QPixmap I_Mayor(":Resource/Imagenes/Mayores/Mayor-Normal.png");
    QPixmap I_Indice(":Resource/Imagenes/Indices/Indice-Normal.png");
    QPixmap I_Pulgar(":Resource/Imagenes/Pulgares/Pulgar-Normal.png");

    ui->Imagen_Label_1->setPixmap(I_Base.scaled(Label_Ancho,Label_Alto,Qt::KeepAspectRatio));
    ui->Imagen_Label_2->setPixmap(I_Menor.scaled(Label_Ancho,Label_Alto,Qt::KeepAspectRatio));
    ui->Imagen_Label_3->setPixmap(I_Anular.scaled(Label_Ancho,Label_Alto,Qt::KeepAspectRatio));
    ui->Imagen_Label_4->setPixmap(I_Mayor.scaled(Label_Ancho,Label_Alto,Qt::KeepAspectRatio));
    ui->Imagen_Label_5->setPixmap(I_Indice.scaled(Label_Ancho,Label_Alto,Qt::KeepAspectRatio));
    ui->Imagen_Label_6->setPixmap(I_Pulgar.scaled(Label_Ancho,Label_Alto,Qt::KeepAspectRatio));
    */

}

VentanaMano::~VentanaMano()
{
    delete ui;
}

void VentanaMano::Actualizar( QSlider *S_Menor, QSlider *S_Anular, QSlider *S_Mayor, QSlider *S_Indice, QSlider *S_Pulgar ){
    QPixmap I_Base, I_Menor, I_Anular, I_Mayor, I_Indice, I_Pulgar;

    I_Base.load(":Resource/Imagenes/Base/Base.png");

    if( S_Menor->value() < 20 ) I_Menor.load(":Resource/Imagenes/Menores/Menor-Normal.png");
    else if( S_Menor->value() >= 20 && S_Menor->value() < 40 )  I_Menor.load(":Resource/Imagenes/Menores/Menor-1.png");
    else if( S_Menor->value() >= 40 && S_Menor->value() < 60 )  I_Menor.load(":Resource/Imagenes/Menores/Menor-2.png");
    else if( S_Menor->value() >= 60 && S_Menor->value() < 80 )  I_Menor.load(":Resource/Imagenes/Menores/Menor-3.png");
    else if( S_Menor->value() >= 80 && S_Menor->value() < 100 )  I_Menor.load(":Resource/Imagenes/Menores/Menor-4.png");
    else if( S_Menor->value() >= 100 && S_Menor->value() <= 120 )  I_Menor.load(":Resource/Imagenes/Menores/Menor-5.png");

    if( S_Anular->value() < 20 ) I_Anular.load(":Resource/Imagenes/Anulares/Anular-Normal.png");
    else if( S_Anular->value() >= 20 && S_Anular->value() < 40 )  I_Anular.load(":Resource/Imagenes/Anulares/Anular-1.png");
    else if( S_Anular->value() >= 40 && S_Anular->value() < 60 )  I_Anular.load(":Resource/Imagenes/Anulares/Anular-2.png");
    else if( S_Anular->value() >= 60 && S_Anular->value() < 80 )  I_Anular.load(":Resource/Imagenes/Anulares/Anular-3.png");
    else if( S_Anular->value() >= 80 && S_Anular->value() < 100 )  I_Anular.load(":Resource/Imagenes/Anulares/Anular-4.png");
    else if( S_Anular->value() >= 100 && S_Anular->value() < 120 )  I_Anular.load(":Resource/Imagenes/Anulares/Anular-5.png");
    else if( S_Anular->value() >= 120 && S_Anular->value() <= 140 )  I_Anular.load(":Resource/Imagenes/Anulares/Anular-6.png");

    if( S_Mayor->value() < 20 ) I_Mayor.load(":Resource/Imagenes/Mayores/Mayor-Normal.png");
    else if( S_Mayor->value() >= 20 && S_Mayor->value() < 40 )  I_Mayor.load(":Resource/Imagenes/Mayores/Mayor-1.png");
    else if( S_Mayor->value() >= 40 && S_Mayor->value() < 60 )  I_Mayor.load(":Resource/Imagenes/Mayores/Mayor-2.png");
    else if( S_Mayor->value() >= 60 && S_Mayor->value() < 80 )  I_Mayor.load(":Resource/Imagenes/Mayores/Mayor-3.png");
    else if( S_Mayor->value() >= 80 && S_Mayor->value() < 100 )  I_Mayor.load(":Resource/Imagenes/Mayores/Mayor-4.png");
    else if( S_Mayor->value() >= 100 && S_Mayor->value() < 120 )  I_Mayor.load(":Resource/Imagenes/Mayores/Mayor-5.png");
    else if( S_Mayor->value() >= 120 && S_Mayor->value() <= 140 )  I_Mayor.load(":Resource/Imagenes/Mayores/Mayor-6.png");

    if( S_Indice->value() < 20 ) I_Indice.load(":Resource/Imagenes/Indices/Indice-Normal.png");
    else if( S_Indice->value() >= 20 && S_Indice->value() < 40 )  I_Indice.load(":Resource/Imagenes/Indices/Indice-1.png");
    else if( S_Indice->value() >= 40 && S_Indice->value() < 60 )  I_Indice.load(":Resource/Imagenes/Indices/Indice-2.png");
    else if( S_Indice->value() >= 60 && S_Indice->value() < 80 )  I_Indice.load(":Resource/Imagenes/Indices/Indice-3.png");
    else if( S_Indice->value() >= 80 && S_Indice->value() < 100 )  I_Indice.load(":Resource/Imagenes/Indices/Indice-4.png");
    else if( S_Indice->value() >= 100 && S_Indice->value() < 120 )  I_Indice.load(":Resource/Imagenes/Indices/Indice-5.png");
    else if( S_Indice->value() >= 120 && S_Indice->value() <= 140 )  I_Indice.load(":Resource/Imagenes/Indices/Indice-6.png");

    if( S_Pulgar->value() < 20 ) I_Pulgar.load(":Resource/Imagenes/Pulgares/Pulgar-Normal.png");
    else if( S_Pulgar->value() >= 20 && S_Pulgar->value() < 40 )  I_Pulgar.load(":Resource/Imagenes/Pulgares/Pulgar-1.png");
    else if( S_Pulgar->value() >= 40 && S_Pulgar->value() < 60 )  I_Pulgar.load(":Resource/Imagenes/Pulgares/Pulgar-2.png");
    else if( S_Pulgar->value() >= 60 && S_Pulgar->value() < 80 )  I_Pulgar.load(":Resource/Imagenes/Pulgares/Pulgar-3.png");
    else if( S_Pulgar->value() >= 80 && S_Pulgar->value() < 100 )  I_Pulgar.load(":Resource/Imagenes/Pulgares/Pulgar-4.png");
    else if( S_Pulgar->value() >= 100 && S_Pulgar->value() <= 120 )  I_Pulgar.load(":Resource/Imagenes/Pulgares/Pulgar-5.png");

    /*switch( S_Mayor->value() ){
        case 0:
            I_Mayor.load(":Resource/Imagenes/Mayores/Mayor-Normal.png");
            break;
        case 1:
            I_Mayor.load(":Resource/Imagenes/Mayores/Mayor-1.png");
            break;
        case 2:
            I_Mayor.load(":Resource/Imagenes/Mayores/Mayor-2.png");
            break;
        case 3:
            I_Mayor.load(":Resource/Imagenes/Mayores/Mayor-3.png");
            break;
        case 4:
            I_Mayor.load(":Resource/Imagenes/Mayores/Mayor-4.png");
            break;
        case 5:
            I_Mayor.load(":Resource/Imagenes/Mayores/Mayor-5.png");
            break;
        case 6:
            I_Mayor.load(":Resource/Imagenes/Mayores/Mayor-6.png");
            break;
    }

    switch( S_Indice->value() ){
        case 0:
            I_Indice.load(":Resource/Imagenes/Indices/Indice-Normal.png");
            break;
        case 1:
            I_Indice.load(":Resource/Imagenes/Indices/Indice-1.png");
            break;
        case 2:
            I_Indice.load(":Resource/Imagenes/Indices/Indice-2.png");
            break;
        case 3:
            I_Indice.load(":Resource/Imagenes/Indices/Indice-3.png");
            break;
        case 4:
            I_Indice.load(":Resource/Imagenes/Indices/Indice-4.png");
            break;
        case 5:
            I_Indice.load(":Resource/Imagenes/Indices/Indice-5.png");
            break;
        case 6:
            I_Indice.load(":Resource/Imagenes/Indices/Indice-6.png");
            break;
    }

    switch( S_Pulgar->value() ){
        case 0:
            I_Pulgar.load(":Resource/Imagenes/Pulgares/Pulgar-Normal.png");
            break;
        case 1:
            I_Pulgar.load(":Resource/Imagenes/Pulgares/Pulgar-1.png");
            break;
        case 2:
            I_Pulgar.load(":Resource/Imagenes/Pulgares/Pulgar-2.png");
            break;
        case 3:
            I_Pulgar.load(":Resource/Imagenes/Pulgares/Pulgar-3.png");
            break;
        case 4:
            I_Pulgar.load(":Resource/Imagenes/Pulgares/Pulgar-4.png");
            break;
        case 5:
            I_Pulgar.load(":Resource/Imagenes/Pulgares/Pulgar-5.png");
            break;
    }*/

    /*QPixmap I_Base;
    I_Base.load(":Resource/Imagenes/Pulgares/Pulgar-Normal.png");

    S_Pulgar->value()  );*/
    ui->Imagen_Label_1->setPixmap(I_Base.scaled(Label_Ancho,Label_Alto,Qt::KeepAspectRatio));
    ui->Imagen_Label_2->setPixmap(I_Menor.scaled(Label_Ancho,Label_Alto,Qt::KeepAspectRatio));
    ui->Imagen_Label_3->setPixmap(I_Anular.scaled(Label_Ancho,Label_Alto,Qt::KeepAspectRatio));
    ui->Imagen_Label_4->setPixmap(I_Mayor.scaled(Label_Ancho,Label_Alto,Qt::KeepAspectRatio));
    ui->Imagen_Label_5->setPixmap(I_Indice.scaled(Label_Ancho,Label_Alto,Qt::KeepAspectRatio));
    ui->Imagen_Label_6->setPixmap(I_Pulgar.scaled(Label_Ancho,Label_Alto,Qt::KeepAspectRatio));

}

