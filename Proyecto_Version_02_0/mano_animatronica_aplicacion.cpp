#include "mano_animatronica_aplicacion.h"
#include "ui_mano_animatronica_aplicacion.h"

Mano_Animatronica_Aplicacion::Mano_Animatronica_Aplicacion(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Mano_Animatronica_Aplicacion)
{
    ui->setupUi(this);

    /*  MODO    */
    QString MensajeStatusBar;
    MensajeStatusBar = "MODO NO SELECCIONADO!";
    ui->statusBar->showMessage( MensajeStatusBar );
    ui->cBx_Modo->setCurrentIndex(NINGUN_MODO);

    /*  Widgets enabled & disabled*/
    ui->cBx_Modo->setEnabled(1);
    ui->rdB_Guante_PC->setChecked(0);
    ui->rdB_PC_Mano->setChecked(0);
    ui->rdB_Guante_Mano->setChecked(0);
    ui->grB_Mano->setDisabled(1);
    ui->grB_Sliders->setDisabled(1);
    ui->grB_Valores->setDisabled(1);
    ui->pushB_Cargar->setDisabled(1);
    ui->pushB_Guardar->setDisabled(1);
    ui->pushB_PlayPause->setDisabled(1);
    ui->lbl_Archivo->hide();

    /*   TOOLTIPS   */
        /*  Pestañas */
    ui->tab_Comunicacion->setToolTip("Comunicación serie");
    ui->tab_Controles->setToolTip("Controles para hardware");
        /*  Widgets  */
    ui->cBx_Modo->setToolTip("Modo a utilizar");
    ui->rdB_Guante_PC->setToolTip("IN: Guante - OUT: PC");
    ui->rdB_PC_Mano->setToolTip("IN: PC - OUT: Mano");
    ui->rdB_Guante_Mano->setToolTip("IN: Guante - OUT: Mano");
    ui->grB_Mano->setToolTip("Simulación de la Mano");
    ui->grB_Sliders->setToolTip("Simulación del Guante");
    ui->grB_Valores->setToolTip("Valores de entrada");
    ui->pushB_Cargar->setToolTip("Cargar movimientos a la mano");
    ui->pushB_Guardar->setToolTip("Guardar movimientos desde el Guante");
    ui->pushB_PlayPause->setToolTip("Leer/Reproducir");

    /*  GroupBox Mano   */
    ActualizarImagenMano( ui, ui->sld_Menor->value(), ui->sld_Anular->value(), ui->sld_Mayor->value(), ui->sld_Indice->value(), ui->sld_Pulgar->value() );

}

void Mano_Animatronica_Aplicacion::setModo( int Mode ){
    Modo = Mode;
}

Mano_Animatronica_Aplicacion::~Mano_Animatronica_Aplicacion()
{
    delete ui;
}

void Mano_Animatronica_Aplicacion::on_cBx_Modo_activated(int index)
{

    if( index == NINGUN_MODO ){

        /*  Status Bar    */
        QString MensajeStatusBar;
        MensajeStatusBar = "MODO NO SELECCIONADO!";
        ui->statusBar->showMessage( MensajeStatusBar );

        /*  ComboBox Modo */
        ui->cBx_Modo->setCurrentIndex(NINGUN_MODO);
        ui->rdB_Guante_PC->setChecked(0);
        ui->rdB_PC_Mano->setChecked(0);
        ui->rdB_Guante_Mano->setChecked(0);
        setModo(NINGUN_MODO);

        /*  Widgets enabled & disabled*/
        ui->grB_Mano->setDisabled(1);
        ui->grB_Sliders->setDisabled(1);
        ui->grB_Valores->setDisabled(1);
        ui->pushB_Cargar->setDisabled(1);
        ui->pushB_Guardar->setDisabled(1);
        ui->pushB_PlayPause->setDisabled(1);
        ui->lbl_Archivo->hide();

        /*   TOOLTIPS   */
        ui->cBx_Modo->setToolTip("Modo a utilizar");
        ui->rdB_Guante_PC->setToolTip("IN: Guante - OUT: PC");
        ui->rdB_PC_Mano->setToolTip("IN: PC - OUT: Mano");
        ui->rdB_Guante_Mano->setToolTip("IN: Guante - OUT: Mano");
        ui->grB_Mano->setToolTip("Simulación de la Mano");
        ui->grB_Sliders->setToolTip("Simulación del Guante");
        ui->grB_Valores->setToolTip("Valores de entrada");
        ui->pushB_Cargar->setToolTip("Cargar movimientos a la mano");
        ui->pushB_Guardar->setToolTip("Guardar movimientos desde el Guante");
        ui->pushB_PlayPause->setToolTip("Leer/Reproducir");

    }

    if( index == GUANTE_PC ){

        /*  Status Bar    */
        QString MensajeStatusBar;
        MensajeStatusBar = "MODO GUANTE_PC";
        ui->statusBar->showMessage( MensajeStatusBar );

        /*  ComboBox Modo */
        ui->rdB_Guante_PC->setChecked(1);
        ui->rdB_PC_Mano->setChecked(0);
        ui->rdB_Guante_Mano->setChecked(0);
        setModo(GUANTE_PC);

        /*  Widgets enabled & disabled*/
        ui->grB_Mano->setEnabled(1);
        ui->grB_Sliders->setDisabled(1);
        ui->grB_Valores->setEnabled(1);
        ui->pushB_Cargar->setDisabled(1);
        ui->pushB_Guardar->setEnabled(1);
        ui->pushB_PlayPause->setDisabled(1);
        ui->lbl_Archivo->hide();

        /*   TOOLTIPS   */
        ui->cBx_Modo->setToolTip("Modo actual: Guante -> PC");
        ui->rdB_Guante_PC->setToolTip("IN: Guante - OUT: PC");
        ui->rdB_PC_Mano->setToolTip("IN: PC - OUT: Mano");
        ui->rdB_Guante_Mano->setToolTip("IN: Guante - OUT: Mano");
        ui->grB_Mano->setToolTip("Simulación de la Mano");
        ui->grB_Sliders->setToolTip("Simulación del Guante");
        ui->grB_Valores->setToolTip("Valores del Guante");
        ui->pushB_Cargar->setToolTip("Sólo para PC -> Mano");
        ui->pushB_Guardar->setToolTip("Guardar movimientos desde el Guante");
        ui->pushB_PlayPause->setToolTip("Comenzar lectura (10 seg.)");
    }

    if( index == PC_MANO ){

        /*  Status Bar    */
        QString MensajeStatusBar;
        MensajeStatusBar = "MODO PC_MANO";
        ui->statusBar->showMessage( MensajeStatusBar );

        /*  ComboBox Modo */
        ui->rdB_Guante_PC->setChecked(0);
        ui->rdB_PC_Mano->setChecked(1);
        ui->rdB_Guante_Mano->setChecked(0);
        setModo(PC_MANO);

        /*  Widgets enabled & disabled*/
        ui->grB_Mano->setEnabled(1);
        ui->grB_Sliders->setEnabled(1);
        ui->grB_Valores->setEnabled(1);
        ui->pushB_Cargar->setEnabled(1);
        ui->pushB_Guardar->setDisabled(1);
        ui->pushB_PlayPause->setEnabled(1);
        ui->lbl_Archivo->show();

        /*   TOOLTIPS   */
        ui->cBx_Modo->setToolTip("Modo actual: PC -> Mano");
        ui->rdB_Guante_PC->setToolTip("IN: Guante - OUT: PC");
        ui->rdB_PC_Mano->setToolTip("IN: PC - OUT: Mano");
        ui->rdB_Guante_Mano->setToolTip("IN: Guante - OUT: Mano");
        ui->grB_Mano->setToolTip("Simulación de la Mano");
        ui->grB_Sliders->setToolTip("Simulación del Guante");
        ui->grB_Valores->setToolTip("Valores de los sliders");
        ui->pushB_Cargar->setToolTip("Cargar movimientos a la Mano");
        ui->pushB_Guardar->setToolTip("Sólo para Guante -> PC");
        ui->pushB_PlayPause->setToolTip("Reproducir (10 seg.)");
        ui->lbl_Archivo->setToolTip("Archivo a reproducir");
    }

    if( index == GUANTE_MANO ){

        /*  MODO    */
        QString MensajeStatusBar;
        MensajeStatusBar = "MODO GUANTE_MANO";
        ui->statusBar->showMessage( MensajeStatusBar );

        /*  ComboBox Modo */
        ui->rdB_Guante_PC->setChecked(0);
        ui->rdB_PC_Mano->setChecked(0);
        ui->rdB_Guante_Mano->setChecked(1);
        setModo(GUANTE_MANO);

        /*  Widgets enabled & disabled*/
        ui->grB_Mano->setEnabled(1);
        ui->grB_Sliders->setDisabled(1);
        ui->grB_Valores->setEnabled(1);
        ui->pushB_Cargar->setDisabled(1);
        ui->pushB_Guardar->setDisabled(1);
        ui->pushB_PlayPause->setDisabled(1);
        ui->lbl_Archivo->hide();

        /*   TOOLTIPS   */
        ui->cBx_Modo->setToolTip("Modo actual: Guante -> Mano");
        ui->rdB_Guante_PC->setToolTip("IN: Guante - OUT: PC");
        ui->rdB_PC_Mano->setToolTip("IN: PC - OUT: Mano");
        ui->rdB_Guante_Mano->setToolTip("IN: Guante - OUT: Mano");
        ui->grB_Mano->setToolTip("Simulación de la Mano");
        ui->grB_Sliders->setToolTip("Simulación del Guante");
        ui->grB_Valores->setToolTip("Valores del Guante");
        ui->pushB_Cargar->setToolTip("Sólo para PC -> Mano");
        ui->pushB_Guardar->setToolTip("Sólo para Guante -> PC");
        ui->pushB_PlayPause->setToolTip("Comenzar lectura (10 seg.)");
    }

}

void Mano_Animatronica_Aplicacion::on_rdB_Guante_PC_clicked()
{
    /*  Status Bar    */
    QString MensajeStatusBar;
    MensajeStatusBar = "MODO GUANTE_PC";
    ui->statusBar->showMessage( MensajeStatusBar );

    /*  ComboBox Modo */
    ui->rdB_Guante_PC->setChecked(1);
    ui->rdB_PC_Mano->setChecked(0);
    ui->rdB_Guante_Mano->setChecked(0);
    setModo(GUANTE_PC);

    /*  Widgets enabled & disabled*/
    ui->grB_Mano->setEnabled(1);
    ui->grB_Sliders->setDisabled(1);
    ui->grB_Valores->setEnabled(1);
    ui->pushB_Cargar->setDisabled(1);
    ui->pushB_Guardar->setEnabled(1);
    ui->pushB_PlayPause->setDisabled(1);
    ui->lbl_Archivo->hide();

    /*   TOOLTIPS   */
    ui->cBx_Modo->setToolTip("Modo actual: Guante -> PC");
    ui->rdB_Guante_PC->setToolTip("IN: Guante - OUT: PC");
    ui->rdB_PC_Mano->setToolTip("IN: PC - OUT: Mano");
    ui->rdB_Guante_Mano->setToolTip("IN: Guante - OUT: Mano");
    ui->grB_Mano->setToolTip("Simulación de la Mano");
    ui->grB_Sliders->setToolTip("Simulación del Guante");
    ui->grB_Valores->setToolTip("Valores del Guante");
    ui->pushB_Cargar->setToolTip("Sólo para PC -> Mano");
    ui->pushB_Guardar->setToolTip("Guardar movimientos desde el Guante");
    ui->pushB_PlayPause->setToolTip("Comenzar lectura (10 seg.)");
}

void Mano_Animatronica_Aplicacion::on_rdB_PC_Mano_clicked()
{
    /*  Status Bar    */
    QString MensajeStatusBar;
    MensajeStatusBar = "MODO PC_MANO";
    ui->statusBar->showMessage( MensajeStatusBar );

    /*  ComboBox Modo */
    ui->rdB_Guante_PC->setChecked(0);
    ui->rdB_PC_Mano->setChecked(1);
    ui->rdB_Guante_Mano->setChecked(0);
    setModo(PC_MANO);

    /*  Widgets enabled & disabled*/
    ui->grB_Mano->setEnabled(1);
    ui->grB_Sliders->setEnabled(1);
    ui->grB_Valores->setEnabled(1);
    ui->pushB_Cargar->setEnabled(1);
    ui->pushB_Guardar->setDisabled(1);
    ui->pushB_PlayPause->setEnabled(1);
    ui->lbl_Archivo->show();

    /*   TOOLTIPS   */
    ui->cBx_Modo->setToolTip("Modo actual: PC -> Mano");
    ui->rdB_Guante_PC->setToolTip("IN: Guante - OUT: PC");
    ui->rdB_PC_Mano->setToolTip("IN: PC - OUT: Mano");
    ui->rdB_Guante_Mano->setToolTip("IN: Guante - OUT: Mano");
    ui->grB_Mano->setToolTip("Simulación de la Mano");
    ui->grB_Sliders->setToolTip("Simulación del Guante");
    ui->grB_Valores->setToolTip("Valores de los sliders");
    ui->pushB_Cargar->setToolTip("Cargar movimientos a la Mano");
    ui->pushB_Guardar->setToolTip("Sólo para Guante -> PC");
    ui->pushB_PlayPause->setToolTip("Reproducir (10 seg.)");
    ui->lbl_Archivo->setToolTip("Archivo a reproducir");
}

void Mano_Animatronica_Aplicacion::on_rdB_Guante_Mano_clicked()
{
    /*  MODO    */
    QString MensajeStatusBar;
    MensajeStatusBar = "MODO GUANTE_MANO";
    ui->statusBar->showMessage( MensajeStatusBar );

    /*  ComboBox Modo */
    ui->rdB_Guante_PC->setChecked(0);
    ui->rdB_PC_Mano->setChecked(0);
    ui->rdB_Guante_Mano->setChecked(1);
    setModo(GUANTE_MANO);

    /*  Widgets enabled & disabled*/
    ui->grB_Mano->setEnabled(1);
    ui->grB_Sliders->setDisabled(1);
    ui->grB_Valores->setEnabled(1);
    ui->pushB_Cargar->setDisabled(1);
    ui->pushB_Guardar->setDisabled(1);
    ui->pushB_PlayPause->setDisabled(1);
    ui->lbl_Archivo->hide();

    /*   TOOLTIPS   */
    ui->cBx_Modo->setToolTip("Modo actual: Guante -> Mano");
    ui->rdB_Guante_PC->setToolTip("IN: Guante - OUT: PC");
    ui->rdB_PC_Mano->setToolTip("IN: PC - OUT: Mano");
    ui->rdB_Guante_Mano->setToolTip("IN: Guante - OUT: Mano");
    ui->grB_Mano->setToolTip("Simulación de la Mano");
    ui->grB_Sliders->setToolTip("Simulación del Guante");
    ui->grB_Valores->setToolTip("Valores del Guante");
    ui->pushB_Cargar->setToolTip("Sólo para PC -> Mano");
    ui->pushB_Guardar->setToolTip("Sólo para Guante -> PC");
    ui->pushB_PlayPause->setToolTip("Comenzar lectura (10 seg.)");
}

void Mano_Animatronica_Aplicacion::on_sld_Menor_valueChanged(int value)
{
    if( Modo == PC_MANO ){
        ActualizarImagenMano( ui, value, ui->sld_Anular->value(), ui->sld_Mayor->value(), ui->sld_Indice->value(), ui->sld_Pulgar->value() );
    }
}

void Mano_Animatronica_Aplicacion::on_sld_Anular_valueChanged(int value)
{
    if( Modo == PC_MANO ){
        ActualizarImagenMano( ui, ui->sld_Menor->value(), value, ui->sld_Mayor->value(), ui->sld_Indice->value(), ui->sld_Pulgar->value() );
    }
}

void Mano_Animatronica_Aplicacion::on_sld_Mayor_valueChanged(int value)
{
    if( Modo == PC_MANO ){
        ActualizarImagenMano( ui, ui->sld_Menor->value(), ui->sld_Anular->value(), value, ui->sld_Indice->value(), ui->sld_Pulgar->value() );
    }
}

void Mano_Animatronica_Aplicacion::on_sld_Indice_valueChanged(int value)
{
    if( Modo == PC_MANO ){
        ActualizarImagenMano( ui, ui->sld_Menor->value(), ui->sld_Anular->value(), ui->sld_Mayor->value(), value, ui->sld_Pulgar->value() );
    }
}

void Mano_Animatronica_Aplicacion::on_sld_Pulgar_valueChanged(int value)
{
    if( Modo == PC_MANO ){
        ActualizarImagenMano( ui, ui->sld_Menor->value(), ui->sld_Anular->value(), ui->sld_Mayor->value(), ui->sld_Indice->value(), value );
    }
}





void ActualizarImagenMano( Ui::Mano_Animatronica_Aplicacion *ui, int Menor, int Anular, int Mayor, int Indice, int Pulgar ){
    QPixmap I_Base, I_Menor, I_Anular, I_Mayor, I_Indice, I_Pulgar;

    I_Base.load(":Resource/Imagenes/Base/Base.png");

    if( Menor < 20 ) I_Menor.load(":Resource/Imagenes/Menores/Menor-Normal.png");
    else if( Menor >= 20 && Menor < 40 )  I_Menor.load(":Resource/Imagenes/Menores/Menor-1.png");
    else if( Menor >= 40 && Menor < 60 )  I_Menor.load(":Resource/Imagenes/Menores/Menor-2.png");
    else if( Menor >= 60 && Menor < 80 )  I_Menor.load(":Resource/Imagenes/Menores/Menor-3.png");
    else if( Menor >= 80 && Menor < 100 )  I_Menor.load(":Resource/Imagenes/Menores/Menor-4.png");
    else if( Menor >= 100 && Menor <= 120 )  I_Menor.load(":Resource/Imagenes/Menores/Menor-5.png");

    if( Anular < 20 ) I_Anular.load(":Resource/Imagenes/Anulares/Anular-Normal.png");
    else if( Anular >= 20 && Anular < 40 )  I_Anular.load(":Resource/Imagenes/Anulares/Anular-1.png");
    else if( Anular >= 40 && Anular < 60 )  I_Anular.load(":Resource/Imagenes/Anulares/Anular-2.png");
    else if( Anular >= 60 && Anular < 80 )  I_Anular.load(":Resource/Imagenes/Anulares/Anular-3.png");
    else if( Anular >= 80 && Anular < 100 )  I_Anular.load(":Resource/Imagenes/Anulares/Anular-4.png");
    else if( Anular >= 100 && Anular < 120 )  I_Anular.load(":Resource/Imagenes/Anulares/Anular-5.png");
    else if( Anular >= 120 && Anular <= 140 )  I_Anular.load(":Resource/Imagenes/Anulares/Anular-6.png");

    if( Mayor < 20 ) I_Mayor.load(":Resource/Imagenes/Mayores/Mayor-Normal.png");
    else if( Mayor >= 20 && Mayor < 40 )  I_Mayor.load(":Resource/Imagenes/Mayores/Mayor-1.png");
    else if( Mayor >= 40 && Mayor < 60 )  I_Mayor.load(":Resource/Imagenes/Mayores/Mayor-2.png");
    else if( Mayor >= 60 && Mayor < 80 )  I_Mayor.load(":Resource/Imagenes/Mayores/Mayor-3.png");
    else if( Mayor >= 80 && Mayor < 100 )  I_Mayor.load(":Resource/Imagenes/Mayores/Mayor-4.png");
    else if( Mayor >= 100 && Mayor < 120 )  I_Mayor.load(":Resource/Imagenes/Mayores/Mayor-5.png");
    else if( Mayor >= 120 && Mayor <= 140 )  I_Mayor.load(":Resource/Imagenes/Mayores/Mayor-6.png");

    if( Indice < 20 ) I_Indice.load(":Resource/Imagenes/Indices/Indice-Normal.png");
    else if( Indice >= 20 && Indice < 40 )  I_Indice.load(":Resource/Imagenes/Indices/Indice-1.png");
    else if( Indice >= 40 && Indice < 60 )  I_Indice.load(":Resource/Imagenes/Indices/Indice-2.png");
    else if( Indice >= 60 && Indice < 80 )  I_Indice.load(":Resource/Imagenes/Indices/Indice-3.png");
    else if( Indice >= 80 && Indice < 100 )  I_Indice.load(":Resource/Imagenes/Indices/Indice-4.png");
    else if( Indice >= 100 && Indice < 120 )  I_Indice.load(":Resource/Imagenes/Indices/Indice-5.png");
    else if( Indice >= 120 && Indice <= 140 )  I_Indice.load(":Resource/Imagenes/Indices/Indice-6.png");

    if( Pulgar < 20 ) I_Pulgar.load(":Resource/Imagenes/Pulgares/Pulgar-Normal.png");
    else if( Pulgar >= 20 && Pulgar < 40 )  I_Pulgar.load(":Resource/Imagenes/Pulgares/Pulgar-1.png");
    else if( Pulgar >= 40 && Pulgar < 60 )  I_Pulgar.load(":Resource/Imagenes/Pulgares/Pulgar-2.png");
    else if( Pulgar >= 60 && Pulgar < 80 )  I_Pulgar.load(":Resource/Imagenes/Pulgares/Pulgar-3.png");
    else if( Pulgar >= 80 && Pulgar < 100 )  I_Pulgar.load(":Resource/Imagenes/Pulgares/Pulgar-4.png");
    else if( Pulgar >= 100 && Pulgar <= 120 )  I_Pulgar.load(":Resource/Imagenes/Pulgares/Pulgar-5.png");

    ui->lbl_1_Base_Img->setPixmap(I_Base.scaled( ui->lbl_1_Base_Img->width() , ui->lbl_1_Base_Img->height() ,Qt::KeepAspectRatio));
    ui->lbl_2_Menor_Img->setPixmap(I_Menor.scaled( ui->lbl_2_Menor_Img->width() , ui->lbl_2_Menor_Img->height() ,Qt::KeepAspectRatio));
    ui->lbl_3_Anular_Img->setPixmap(I_Anular.scaled( ui->lbl_3_Anular_Img->width() , ui->lbl_3_Anular_Img->height() ,Qt::KeepAspectRatio));
    ui->lbl_4_Mayor_Img->setPixmap(I_Mayor.scaled( ui->lbl_4_Mayor_Img->width() , ui->lbl_4_Mayor_Img->height() ,Qt::KeepAspectRatio));
    ui->lbl_5_Indice_Img->setPixmap(I_Indice.scaled( ui->lbl_5_Indice_Img->width() , ui->lbl_5_Indice_Img->height() ,Qt::KeepAspectRatio));
    ui->lbl_6_Pulgar_Img->setPixmap(I_Pulgar.scaled( ui->lbl_6_Pulgar_Img->width() , ui->lbl_6_Pulgar_Img->height() ,Qt::KeepAspectRatio));

}

void ActualizarImagenMano( Ui::Mano_Animatronica_Aplicacion *ui, QSlider *S_Menor, QSlider *S_Anular, QSlider *S_Mayor, QSlider *S_Indice, QSlider *S_Pulgar ){
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

    ui->lbl_1_Base_Img->setPixmap(I_Base.scaled( ui->lbl_1_Base_Img->width() , ui->lbl_1_Base_Img->height() ,Qt::KeepAspectRatio));
    ui->lbl_2_Menor_Img->setPixmap(I_Menor.scaled( ui->lbl_2_Menor_Img->width() , ui->lbl_2_Menor_Img->height() ,Qt::KeepAspectRatio));
    ui->lbl_3_Anular_Img->setPixmap(I_Anular.scaled( ui->lbl_3_Anular_Img->width() , ui->lbl_3_Anular_Img->height() ,Qt::KeepAspectRatio));
    ui->lbl_4_Mayor_Img->setPixmap(I_Mayor.scaled( ui->lbl_4_Mayor_Img->width() , ui->lbl_4_Mayor_Img->height() ,Qt::KeepAspectRatio));
    ui->lbl_5_Indice_Img->setPixmap(I_Indice.scaled( ui->lbl_5_Indice_Img->width() , ui->lbl_5_Indice_Img->height() ,Qt::KeepAspectRatio));
    ui->lbl_6_Pulgar_Img->setPixmap(I_Pulgar.scaled( ui->lbl_6_Pulgar_Img->width() , ui->lbl_6_Pulgar_Img->height() ,Qt::KeepAspectRatio));

}

void Mano_Animatronica_Aplicacion::on_pushButton_clicked()
{
    /* algo */
}
