#include "mano_animatronica_aplicacion.h"
#include "ui_mano_animatronica_aplicacion.h"

#include <QLabel>
#include <QMessageBox>

/*
 SerialPort
    Todo sacado de código hecho por Qt en el proyecto: Welcome->Examples->Search:terminal
*/


Mano_Animatronica_Aplicacion::Mano_Animatronica_Aplicacion(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Mano_Animatronica_Aplicacion){
    ui->setupUi(this);

    /*  QSerialPort */
        m_serial = new QSerialPort(this);

    /*  Timers   */{
        Timer_UART = new QTimer(this);
        Timer_WIFI = new QTimer(this);
    }

    /*  Connects    */{
            /*  SerialPorts */
            //connect( m_serial, SIGNAL(QSerialPort::errorOccurred(SerialPortError error) ) , this, SLOT((handleError())) );
            //connect( m_serial, SIGNAL(QSerialPort::readyRead() ) , this, SLOT(readData()) );

            /*  Timers  */
            connect( Timer_UART, SIGNAL(timeout()), this, SLOT(on_Timer_UART_timeout()) );
            connect( Timer_WIFI, SIGNAL(timeout()), this, SLOT(on_Timer_WIFI_timeout()) );

            /*  ComboBoxes    */
            connect( ui->cBx_Modo, SIGNAL(QComboBox::activated()), this, SLOT(on_cBx_Modo_activated(int)) );
            //connect( ui->cBx_Puerto, SIGNAL(QComboBox::activated()), this, SLOT(on_cBx_Puerto_activated(int)) );

            /*  RadioButtons */
            connect( ui->rdB_Guante_PC, SIGNAL(QRadioButton::clicked()), this, SLOT(on_rdB_Guante_PC_clicked()) );
            connect( ui->rdB_PC_Mano, SIGNAL(QRadioButton::clicked()), this, SLOT(on_rdB_PC_Mano_clicked()) );
            connect( ui->rdB_Guante_Mano, SIGNAL(QRadioButton::clicked()), this, SLOT(on_rdB_Guante_Mano_clicked()) );

            /*  Sliders  */
            connect( ui->sld_Menor, SIGNAL(QSlider::valueChanged()), this, SLOT(on_sld_Menor_valueChanged(int)) );
            connect( ui->sld_Anular, SIGNAL(QSlider::valueChanged()), this, SLOT(on_sld_Anular_valueChanged(int)) );
            connect( ui->sld_Mayor, SIGNAL(QSlider::valueChanged()), this, SLOT(on_sld_Mayor_valueChanged(int)) );
            connect( ui->sld_Indice, SIGNAL(QSlider::valueChanged()), this, SLOT(on_sld_Indice_valueChanged(int)) );
            connect( ui->sld_Pulgar, SIGNAL(QSlider::valueChanged()), this, SLOT(on_sld_Pulgar_valueChanged(int)) );

            /* PushButtons   */
            //connect( ui->pushB_PlayPause, SIGNAL(QPushButton::clicked()), this, SLOT(on_pushB_PlayPause_clicked()) );
            //connect( ui->pushB_Cargar, SIGNAL(QPushButton::clicked()), this, SLOT(on_pushB_Cargar_clicked()) );
            //connect( ui->pushB_Guardar, SIGNAL(QPushButton::clicked()), this, SLOT(on_pushB_Guardar_clicked()) );
            //connect( ui->pushB_Actualizar, SIGNAL(QPushButton::clicked()), this, SLOT(on_pushB_Actualizar_clicked()) );
            connect( ui->pushB_Prueba_UART, SIGNAL(QPushButton::clicked()), this, SLOT(on_pushB_Prueba_UART_clicked()) );
            connect( ui->pushB_Prueba_WIFI, SIGNAL(QPushButton::clicked()), this, SLOT(on_pushB_Prueba_WIFI_clicked()) );
    }

    /*  Status Bar  */{
        QString MensajeStatusBar;
        MensajeStatusBar = "MODO NO SELECCIONADO!";
        ui->statusBar->showMessage( MensajeStatusBar );
        ui->cBx_Modo->setCurrentIndex(NINGUN_MODO);
    }

    /*  Pestañas enables & disables */{
        ui->tab_Controles->setDisabled(true);
        ui->tab_Comunicacion->setEnabled(true);
    }

    /*  Widgets enables & disables  */{
        ui->cBx_Modo->setEnabled(true);
        ui->rdB_Guante_PC->setChecked(false);
        ui->rdB_PC_Mano->setChecked(false);
        ui->rdB_Guante_Mano->setChecked(false);
        ui->grB_Mano->setDisabled(true);
        ui->grB_Sliders->setDisabled(true);
        ui->grB_Valores->setDisabled(true);
        ui->pushB_Cargar->setDisabled(true);
        ui->pushB_Guardar->setDisabled(true);
        ui->pushB_PlayPause->setDisabled(true);
        ui->lbl_Archivo->hide();
    }

    /*  SetUp SerialPort    */{

        ui->cBx_Puerto->clear();
        const auto infos = QSerialPortInfo::availablePorts();
        for (const QSerialPortInfo &info : infos) {
            QStringList list;
            list << info.portName()
                 /*<< (!description.isEmpty() ? description : blankString)
                 << (!manufacturer.isEmpty() ? manufacturer : blankString)
                 << (!serialNumber.isEmpty() ? serialNumber : blankString)
                 << info.systemLocation()
                 << (info.vendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : blankString)
                 << (info.productIdentifier() ? QString::number(info.productIdentifier(), 16) : blankString)*/;

            ui->cBx_Puerto->addItem(list.first(), list);
        }
        ui->cBx_Puerto->setCurrentIndex(0);
        m_currentSettings.name = ui->cBx_Puerto->currentText();

        m_currentSettings.baudRate = static_cast <QSerialPort::BaudRate> (BAUD_RATE);
        m_currentSettings.stringBaudRate = QStringLiteral(STR_BAUD_RATE);

        m_currentSettings.dataBits = static_cast <QSerialPort::DataBits> (DATA_BITS);
        m_currentSettings.stringDataBits = QStringLiteral(STR_DATA_BITS);

        m_currentSettings.parity = static_cast <QSerialPort::Parity> (PARITY);
        m_currentSettings.stringParity = QStringLiteral(STR_PARITY);

        m_currentSettings.stopBits = static_cast <QSerialPort::StopBits> (STOP_BITS);
        m_currentSettings.stringStopBits = QStringLiteral(STR_STOP_BITS);

        m_currentSettings.flowControl = static_cast <QSerialPort::FlowControl> (FLOW_CONTROL);
        m_currentSettings.stringFlowControl = QStringLiteral(STR_FLOW_CONTROL);


        m_serial->setPortName(m_currentSettings.name);
        m_serial->setBaudRate(m_currentSettings.baudRate);
        m_serial->setDataBits(m_currentSettings.dataBits);
        m_serial->setParity(m_currentSettings.parity);
        m_serial->setStopBits(m_currentSettings.stopBits);
        m_serial->setFlowControl(m_currentSettings.flowControl);
    }

    /*  TOOLTIPS   */{
        /*  Pestañas */
            ui->tab_Comunicacion->setToolTip("Comunicación serie");
            ui->tab_Controles->setToolTip("Controles para hardware");

        /*  Widgets (tab_Controles) */
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

        /*  Widgets (tab_Comunicacion) */
            ui->pushB_Actualizar->setToolTip("Actualizar puertos");
            ui->pushB_Prueba_UART->setToolTip("Prueba de conexión UART");
            ui->pushB_Prueba_WIFI->setToolTip("Prueba de conexión UART");
            ui->cBx_Puerto->setToolTip("Puerto UART a utilizar");
            ui->pushB_Actualizar->setToolTip("Actualizar puertos");
    }

    /*  Labels  */{
        ui->lbl_Estado_Con_UART->setAutoFillBackground(true);
        ui->lbl_Estado_Con_UART->setText("Desconectado");
        ui->lbl_Estado_Con_UART->setAlignment(Qt::AlignCenter);
        ui->lbl_Estado_Con_UART->setStyleSheet(FONDO_ROJO_LETRA_NEGRA);

        ui->lbl_Estado_Con_WIFI->setAutoFillBackground(true);
        ui->lbl_Estado_Con_WIFI->setText("Desconectado");
        ui->lbl_Estado_Con_WIFI->setAlignment(Qt::AlignCenter);
        ui->lbl_Estado_Con_WIFI->setStyleSheet(FONDO_ROJO_LETRA_NEGRA);

        ui->lbl_BaudRate->setText( "BaudRate : " + m_currentSettings.stringBaudRate );
        ui->lbl_DataBits->setText( "DataBits : " + m_currentSettings.stringDataBits );
        ui->lbl_Parity->setText( "Parity : " + m_currentSettings.stringParity );
        ui->lbl_StopBits->setText( "StopBits : " + m_currentSettings.stringStopBits );
        ui->lbl_FlowControl->setText( "FlowControl : " + m_currentSettings.stringFlowControl );
    }

    /*  GroupBox Mano   */{
        ActualizarImagenMano( ui, ui->sld_Menor->value(), ui->sld_Anular->value(), ui->sld_Mayor->value(), ui->sld_Indice->value(), ui->sld_Pulgar->value() );
    }


}

Mano_Animatronica_Aplicacion::~Mano_Animatronica_Aplicacion()
{
    if (m_serial->isOpen())  m_serial->close();
    delete m_serial;

    delete Timer_UART;
    delete Timer_WIFI;
    delete ui;
}

void Mano_Animatronica_Aplicacion::setModo( int Nuevo_Modo ){
    Modo = Nuevo_Modo;
}

int Mano_Animatronica_Aplicacion::getModo(){
    return Modo;
}

void Mano_Animatronica_Aplicacion::setEstado_UART( int Nuevo_Estado ){
    Estado_Conexion_UART = Nuevo_Estado;
}

int Mano_Animatronica_Aplicacion::getEstado_UART(){
    return Estado_Conexion_UART;
}

void Mano_Animatronica_Aplicacion::setEstado_WIFI( int Nuevo_Estado ){
    Estado_Conexion_WIFI = Nuevo_Estado;
}

int Mano_Animatronica_Aplicacion::getEstado_WIFI(){
    return Estado_Conexion_WIFI;
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
        ui->rdB_Guante_PC->setChecked(false);
        ui->rdB_PC_Mano->setChecked(false);
        ui->rdB_Guante_Mano->setChecked(false);
        setModo(NINGUN_MODO);

        /*  Widgets enables & disables  */
        ui->grB_Mano->setDisabled(true);
        ui->grB_Sliders->setDisabled(true);
        ui->grB_Valores->setDisabled(true);
        ui->pushB_Cargar->setDisabled(true);
        ui->pushB_Guardar->setDisabled(true);
        ui->pushB_PlayPause->setDisabled(true);
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
        ui->rdB_Guante_PC->setChecked(true);
        ui->rdB_PC_Mano->setChecked(false);
        ui->rdB_Guante_Mano->setChecked(false);
        setModo(GUANTE_PC);

        /*  Widgets enables & disables  */
        ui->grB_Mano->setEnabled(true);
        ui->grB_Sliders->setDisabled(true);
        ui->grB_Valores->setEnabled(true);
        ui->pushB_Cargar->setDisabled(true);
        ui->pushB_Guardar->setEnabled(true);
        ui->pushB_PlayPause->setDisabled(true);
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
        ui->rdB_Guante_PC->setChecked(false);
        ui->rdB_PC_Mano->setChecked(true);
        ui->rdB_Guante_Mano->setChecked(false);
        setModo(PC_MANO);

        /*  Widgets enables & disables  */
        ui->grB_Mano->setEnabled(true);
        ui->grB_Sliders->setEnabled(true);
        ui->grB_Valores->setEnabled(true);
        ui->pushB_Cargar->setEnabled(true);
        ui->pushB_Guardar->setDisabled(true);
        ui->pushB_PlayPause->setEnabled(true);
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
        ui->rdB_Guante_PC->setChecked(false);
        ui->rdB_PC_Mano->setChecked(false);
        ui->rdB_Guante_Mano->setChecked(true);
        setModo(GUANTE_MANO);

        /*  Widgets enables & disables  */
        ui->grB_Mano->setEnabled(true);
        ui->grB_Sliders->setDisabled(true);
        ui->grB_Valores->setEnabled(true);
        ui->pushB_Cargar->setDisabled(true);
        ui->pushB_Guardar->setDisabled(true);
        ui->pushB_PlayPause->setDisabled(true);
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
    ui->rdB_Guante_PC->setChecked(true);
    ui->rdB_PC_Mano->setChecked(false);
    ui->rdB_Guante_Mano->setChecked(false);
    setModo(GUANTE_PC);

    /*  Widgets enables & disables  */
    ui->grB_Mano->setEnabled(true);
    ui->grB_Sliders->setDisabled(true);
    ui->grB_Valores->setEnabled(true);
    ui->pushB_Cargar->setDisabled(true);
    ui->pushB_Guardar->setEnabled(true);
    ui->pushB_PlayPause->setDisabled(true);
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
    ui->rdB_Guante_PC->setChecked(false);
    ui->rdB_PC_Mano->setChecked(true);
    ui->rdB_Guante_Mano->setChecked(false);
    setModo(PC_MANO);

    /*  Widgets enables & disables  */
    ui->grB_Mano->setEnabled(true);
    ui->grB_Sliders->setEnabled(true);
    ui->grB_Valores->setEnabled(true);
    ui->pushB_Cargar->setEnabled(true);
    ui->pushB_Guardar->setDisabled(true);
    ui->pushB_PlayPause->setEnabled(true);
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
    ui->rdB_Guante_PC->setChecked(false);
    ui->rdB_PC_Mano->setChecked(false);
    ui->rdB_Guante_Mano->setChecked(true);
    setModo(GUANTE_MANO);

    /*  Widgets enables & disables  */
    ui->grB_Mano->setEnabled(true);
    ui->grB_Sliders->setDisabled(true);
    ui->grB_Valores->setEnabled(true);
    ui->pushB_Cargar->setDisabled(true);
    ui->pushB_Guardar->setDisabled(true);
    ui->pushB_PlayPause->setDisabled(true);
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
    if( getModo() == PC_MANO ){
        value = (value * MAX_VAL) / ui->sld_Menor->maximum();

        /*  GroupBox Mano   */
        ActualizarImagenMano( ui, ui->sld_Menor->value(), ui->sld_Anular->value(), ui->sld_Mayor->value(), ui->sld_Indice->value(), ui->sld_Pulgar->value() );

        /*  Label   */
        ui->lbl_VMenor->setText( "Menor : " + QString::number(value));
    }
}

void Mano_Animatronica_Aplicacion::on_sld_Anular_valueChanged(int value)
{
    if( getModo() == PC_MANO ){
        value = (value * MAX_VAL) / ui->sld_Anular->maximum();

        /*  GroupBox Mano   */
        ActualizarImagenMano( ui, ui->sld_Menor->value(), ui->sld_Anular->value(), ui->sld_Mayor->value(), ui->sld_Indice->value(), ui->sld_Pulgar->value() );

        /*  Label   */
        ui->lbl_VAnular->setText( "Anular : " + QString::number(value));
    }
}

void Mano_Animatronica_Aplicacion::on_sld_Mayor_valueChanged(int value)
{
    if( getModo() == PC_MANO ){
        value = (value * MAX_VAL) / ui->sld_Mayor->maximum();

        /*  GroupBox Mano   */
        ActualizarImagenMano( ui, ui->sld_Menor->value(), ui->sld_Anular->value(), ui->sld_Mayor->value(), ui->sld_Indice->value(), ui->sld_Pulgar->value() );

        /*  Label   */
        ui->lbl_VMayor->setText( "Mayor : " + QString::number(value));
    }
}

void Mano_Animatronica_Aplicacion::on_sld_Indice_valueChanged(int value)
{
    if( getModo() == PC_MANO ){
        value = (value * MAX_VAL) / ui->sld_Indice->maximum();

        /*  GroupBox Mano   */
        ActualizarImagenMano( ui, ui->sld_Menor->value(), ui->sld_Anular->value(), ui->sld_Mayor->value(), ui->sld_Indice->value(), ui->sld_Pulgar->value() );

        /*  Label   */
        ui->lbl_VIndice->setText( "Indice : " + QString::number(value));
    }
}

void Mano_Animatronica_Aplicacion::on_sld_Pulgar_valueChanged(int value)
{
    if( getModo() == PC_MANO ){
        value = (value * MAX_VAL) / ui->sld_Pulgar->maximum();

        /*  GroupBox Mano   */
        ActualizarImagenMano( ui, ui->sld_Menor->value(), ui->sld_Anular->value(), ui->sld_Mayor->value(), ui->sld_Indice->value(), ui->sld_Pulgar->value() );

        /*  Label   */
        ui->lbl_VPulgar->setText( "Pulgar : " + QString::number(value));
    }
}

void Mano_Animatronica_Aplicacion::on_pushB_Prueba_UART_clicked(){

    /*  Timer   */
    Timer_UART->start( TIEMPO_DE_ESPERA_UART );

    setEstado_UART( ESPERANDO );

    m_currentSettings.name = ui->cBx_Puerto->currentText();
    /*ui->statusBar->showMessage( "\"" + ui->cBx_Puerto->currentText() + "\"" );*/

    /*  Label   */
    ui->lbl_Estado_Con_UART->setText("Esperando...");
    ui->lbl_Estado_Con_UART->setAlignment(Qt::AlignCenter);
    ui->lbl_Estado_Con_UART->setStyleSheet(FONDO_AMARILLO_LETRA_NEGRA);

    /*  PushButton  */
    ui->pushB_Prueba_UART->setDisabled(true);

    /*  Prueba UART */
    if (m_serial->open(QIODevice::ReadWrite)) {
        setEstado_UART(CONECTADO);

        /*  Label   */
        ui->lbl_Estado_Con_UART->setText("Conectado!");
        ui->lbl_Estado_Con_UART->setAlignment(Qt::AlignCenter);
        ui->lbl_Estado_Con_UART->setStyleSheet(FONDO_VERDE_LETRA_NEGRA);

        /*  Pestañas enables & disables */{
            ui->tab_Controles->setEnabled(true);
        }
    }
    else {
        /*QMessageBox::critical(this, tr("Error"), m_serial->errorString());*/
        setEstado_UART(DESCONECTADO);

        /*  Label   */
        ui->lbl_Estado_Con_UART->setText("Desconectado");
        ui->lbl_Estado_Con_UART->setAlignment(Qt::AlignCenter);
        ui->lbl_Estado_Con_UART->setStyleSheet(FONDO_ROJO_LETRA_NEGRA);

        /*  PushButton  */
        ui->pushB_Prueba_UART->setEnabled(true);
    }
}

void Mano_Animatronica_Aplicacion::on_pushB_Prueba_WIFI_clicked(){

    setEstado_WIFI( ESPERANDO );

    /*  Timer   */
    Timer_WIFI->start( TIEMPO_DE_ESPERA_WIFI );

    /*  Label   */
    ui->lbl_Estado_Con_WIFI->setText("Esperando...");
    ui->lbl_Estado_Con_WIFI->setAlignment(Qt::AlignCenter);
    ui->lbl_Estado_Con_WIFI->setStyleSheet(FONDO_AMARILLO_LETRA_NEGRA);

    /*  PushButton  */
    ui->pushB_Prueba_WIFI->setDisabled(true);
}

void Mano_Animatronica_Aplicacion::on_Timer_UART_timeout(){

    if( getEstado_UART() == ESPERANDO ){
        setEstado_UART( DESCONECTADO );

        /*  Label   */
        ui->lbl_Estado_Con_UART->setText("Desconectado");
        ui->lbl_Estado_Con_UART->setAlignment(Qt::AlignCenter);
        ui->lbl_Estado_Con_UART->setStyleSheet(FONDO_ROJO_LETRA_NEGRA);

        /*  PushButton  */
        ui->pushB_Prueba_UART->setEnabled(true);
    }
}

void Mano_Animatronica_Aplicacion::on_Timer_WIFI_timeout(){

    setEstado_WIFI( ESPERANDO );

    /*  Label   */
    ui->lbl_Estado_Con_WIFI->setText("Desconectado");
    ui->lbl_Estado_Con_WIFI->setAlignment(Qt::AlignCenter);
    ui->lbl_Estado_Con_WIFI->setStyleSheet(FONDO_ROJO_LETRA_NEGRA);

    /*  PushButton  */
    ui->pushB_Prueba_WIFI->setEnabled(true);
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
