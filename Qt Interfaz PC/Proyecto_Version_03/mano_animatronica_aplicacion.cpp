#include "mano_animatronica_aplicacion.h"
#include "ui_mano_animatronica_aplicacion.h"

#include <QLabel>
#include <QMessageBox>
#include <QByteArray>
#include <QIODevice>
#include <QFileDialog>

// SerialPort: Todo sacado de código hecho por Qt en el proyecto: Welcome->Examples->Search:terminal

static const char blankString[] = QT_TRANSLATE_NOOP("SettingsDialog", "N/A");

// Constructor
Mano_Animatronica_Aplicacion::Mano_Animatronica_Aplicacion(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Mano_Animatronica_Aplicacion){
    ui->setupUi(this);

    SerialPort_Initialize();

    f_PlayPause_Status = false;
    f_Movements_Loaded = false;

    //  Timer
    /************/
        Timer_WIFI = new QTimer(this);
        connect( Timer_WIFI, &QTimer::timeout, this, &Mano_Animatronica_Aplicacion::on_Timer_WIFI_timeout);

    //  Status Bar
    /**************/
        QString MensajeStatusBar;
        MensajeStatusBar = "MODO NO SELECCIONADO!";
        ui->statusBar->showMessage( MensajeStatusBar );
        /*ui->statusBar->showMessage( QString::number(a) );*/

    //  Tab Order
    /*************/
        ui->tabWidget->setTabOrder( ui->tab_Comunicacion, ui->tab_Controles );
        ui->tab_Comunicacion->setTabOrder( ui->pushB_Prueba_UART, ui->pushB_Actualizar );
        ui->tab_Comunicacion->setTabOrder( ui->pushB_Actualizar, ui->cBx_Puerto );
        ui->tab_Comunicacion->setTabOrder( ui->cBx_Puerto, ui->pushB_Prueba_WIFI );

        ui->tab_Controles->setTabOrder( ui->cBx_Modo, ui->rdB_Guante_PC);
        ui->tab_Controles->setTabOrder( ui->rdB_Guante_PC, ui->rdB_PC_Mano );
        ui->tab_Controles->setTabOrder( ui->rdB_PC_Mano, ui->rdB_Guante_Mano );
        ui->tab_Controles->setTabOrder( ui->rdB_Guante_Mano, ui->pushB_Cargar );
        ui->tab_Controles->setTabOrder( ui->pushB_Cargar, ui->pushB_Guardar );
        ui->tab_Controles->setTabOrder( ui->pushB_Guardar, ui->pushB_PlayPause);

    GUI_Start_Tab_Comunicacion();
    GUI_Start_Tab_Controles();

    QStringList list;
    list = ui->cBx_Puerto->itemData( ui->cBx_Puerto->currentIndex() ).toStringList();
    ui->lbl_UART_Des->setText(tr("Descripción: %1").arg(list.count() > 1 ? list.at(1) : tr(blankString)));
    ui->lbl_UART_Fab->setText(tr("Fabricante: %1").arg(list.count() > 2 ? list.at(2) : tr(blankString)));
    ui->lbl_UART_Nsr->setText(tr("Núm.Serie: %1").arg(list.count() > 3 ? list.at(3) : tr(blankString)));
    ui->lbl_UART_Ubi->setText(tr("Ubicación: %1").arg(list.count() > 4 ? list.at(4) : tr(blankString)));
}

// Destructor
Mano_Animatronica_Aplicacion::~Mano_Animatronica_Aplicacion( void ){
    if (m_serial->isOpen()){
        m_serial->close();
    }
    delete m_serial;

    delete ui;
}

// Funciones de Inicialización de la GUI
/*****************************************/

void Mano_Animatronica_Aplicacion::SerialPort_Initialize(){
    // QSerialPort
    /*************/
        m_serial = new QSerialPort(this);
        connect( m_serial, &QSerialPort::errorOccurred, this, &Mano_Animatronica_Aplicacion::handler_Error_UART);
        /*bool a = */connect( m_serial, &QSerialPort::readyRead, this, &Mano_Animatronica_Aplicacion::handler_ReadyRead);

        // SetUp SerialPortInfo
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

        // ReadBuffer ilimitado
        m_serial->setReadBufferSize(0);
}

void Mano_Animatronica_Aplicacion::GUI_Start_Tab_Comunicacion(){

    // Tab Comunicación
    /*******************/
    ui->tab_Comunicacion->setEnabled(true);
    ui->tab_Comunicacion->setToolTip("Comunicación serie");

    // Labels SerialPort
    /********************/
    ui->lbl_BaudRate->setText( "Taza de Baudios: " + m_currentSettings.stringBaudRate );
    ui->lbl_DataBits->setText( "Bits de Datos: " + m_currentSettings.stringDataBits );
    ui->lbl_Parity->setText( "Paridad: " + m_currentSettings.stringParity );
    ui->lbl_StopBits->setText( "Bits de Stop: " + m_currentSettings.stringStopBits );
    ui->lbl_FlowControl->setText( "Control de Flujo: " + m_currentSettings.stringFlowControl );

    // ComboBox Puerto
    /*****************/
    QObject::connect<void(QComboBox::*)(int)>( ui->cBx_Puerto, &QComboBox::currentIndexChanged, this,  &Mano_Animatronica_Aplicacion::on_cBx_Puerto_currentIndexChanged );
    ui->cBx_Puerto->setToolTip("Puerto UART a utilizar");

    // PushButton Actualizar
    /***********************/
    ui->pushB_Actualizar->setAutoDefault( true );
    connect( ui->pushB_Actualizar, &QPushButton::clicked, this, &Mano_Animatronica_Aplicacion::Actualizar_Puertos );
    ui->pushB_Actualizar->setToolTip("Actualizar puertos");

    // PushButton Conectar
    /*********************/
    ui->pushB_Prueba_UART->setAutoDefault( true );
    connect( ui->pushB_Prueba_UART, &QPushButton::clicked, this, &Mano_Animatronica_Aplicacion::on_pushB_Prueba_UART_clicked );
    ui->pushB_Prueba_UART->setToolTip("Prueba de conexión UART");
    // label
    ui->lbl_Estado_Con_UART->setAutoFillBackground(true);
    ui->lbl_Estado_Con_UART->setText(TEXTO_DESCONECTADO);
    ui->lbl_Estado_Con_UART->setAlignment(Qt::AlignCenter);
    ui->lbl_Estado_Con_UART->setStyleSheet(FONDO_ROJO_NEGRITA_LETRA_NEGRA);

    // PushButton WIFI
    /******************/
    ui->pushB_Prueba_WIFI->setAutoDefault( true );
    connect( ui->pushB_Prueba_WIFI, &QPushButton::clicked, this, &Mano_Animatronica_Aplicacion::on_pushB_Prueba_WIFI_clicked );
    ui->pushB_Prueba_WIFI->setToolTip("Prueba de conexión WIFI");
    // label
    ui->lbl_Estado_Con_WIFI->setAutoFillBackground(true);
    ui->lbl_Estado_Con_WIFI->setText(TEXTO_DESCONECTADO);
    ui->lbl_Estado_Con_WIFI->setAlignment(Qt::AlignCenter);
    ui->lbl_Estado_Con_WIFI->setStyleSheet(FONDO_ROJO_NEGRITA_LETRA_NEGRA);

    Actualizar_Puertos();
}

void Mano_Animatronica_Aplicacion::GUI_Start_Tab_Controles(){

    // Tab Controles
    /*******************/
    ui->tab_Controles->setDisabled(true);
    ui->tab_Controles->setToolTip("Controles para hardware");

    // ComboBox Modo
    /*****************/
    QObject::connect<void(QComboBox::*)(int)>( ui->cBx_Modo, &QComboBox::activated, this,  &Mano_Animatronica_Aplicacion::on_cBx_Modo_activated );
    /*  Porque la señal "currentIndexChanged" y la señal "activated" está sobrecargada, forzamos a que sea la que entregue un int    */
    ui->cBx_Modo->setCurrentIndex( NINGUN_MODO );
    ui->cBx_Modo->setEnabled(true);
    ui->cBx_Modo->setToolTip("Modo a utilizar");

        // RadioButton Guante-PC
        /*************************/
        connect( ui->rdB_Guante_PC, &QRadioButton::clicked, this, &Mano_Animatronica_Aplicacion::on_rdB_Guante_PC_clicked );
        ui->rdB_Guante_PC->setChecked(false);
        ui->rdB_Guante_PC->setToolTip("IN: Guante - OUT: PC");

        // RadioButton PC-MANO
        /***********************/
        connect( ui->rdB_PC_Mano, &QRadioButton::clicked, this, &Mano_Animatronica_Aplicacion::on_rdB_PC_Mano_clicked );
        ui->rdB_PC_Mano->setChecked(false);
        ui->rdB_PC_Mano->setToolTip("IN: PC - OUT: Mano");

        // RadioButton Guante-MANO
        /**************************/
        connect( ui->rdB_Guante_Mano, &QRadioButton::clicked, this, &Mano_Animatronica_Aplicacion::on_rdB_Guante_Mano_clicked );
        ui->rdB_Guante_Mano->setChecked(false);
        ui->rdB_Guante_Mano->setToolTip("IN: Guante - OUT: Mano");

    // PushButton Play/Pause
    /************************/
    connect( ui->pushB_PlayPause, &QPushButton::clicked, this, &Mano_Animatronica_Aplicacion::on_pushB_PlayPause_clicked );
    ui->pushB_PlayPause->setDisabled(true);
    ui->pushB_PlayPause->setToolTip("Leer/Reproducir");

    // PushButton Cargar
    /********************/
    connect( ui->pushB_Cargar, &QPushButton::clicked, this, &Mano_Animatronica_Aplicacion::on_pushB_Cargar_clicked );
    ui->pushB_Cargar->setDisabled(true);
    ui->pushB_Cargar->setToolTip("Cargar movimientos a la mano");

    // PushButton Guardar
    /*********************/
    connect( ui->pushB_Guardar, &QPushButton::clicked, this, &Mano_Animatronica_Aplicacion::on_pushB_Guardar_clicked );
    ui->pushB_Guardar->setDisabled(true);
    ui->pushB_Guardar->setToolTip("Guardar movimientos desde el Guante");

    // GroupBox Sliders
    /*******************/
    ui->grB_Sliders->setDisabled(true);
    ui->grB_Sliders->setToolTip("Simulación del Guante");

        // Sliders
        /**********/
        connect( ui->sld_Menor, &QSlider::valueChanged, this, &Mano_Animatronica_Aplicacion::on_sld_Menor_valueChanged );
        connect( ui->sld_Anular, &QSlider::valueChanged, this, &Mano_Animatronica_Aplicacion::on_sld_Anular_valueChanged );
        connect( ui->sld_Mayor, &QSlider::valueChanged, this, &Mano_Animatronica_Aplicacion::on_sld_Mayor_valueChanged );
        connect( ui->sld_Indice, &QSlider::valueChanged, this, &Mano_Animatronica_Aplicacion::on_sld_Indice_valueChanged );
        connect( ui->sld_Pulgar, &QSlider::valueChanged, this, &Mano_Animatronica_Aplicacion::on_sld_Pulgar_valueChanged );

    // GroupBox Mano
    /*****************/
    ui->grB_Mano->setDisabled(true);
    ui->grB_Mano->setToolTip("Simulación de la Mano");
    ActualizarImagenMano( ui, ui->sld_Menor->value(), ui->sld_Anular->value(), ui->sld_Mayor->value(), ui->sld_Indice->value(), ui->sld_Pulgar->value() );

    // GroupBox Valores
    /******************/
    ui->grB_Valores->setDisabled(true);
    ui->grB_Valores->setToolTip("Valores de entrada");

    ui->lbl_Archivo->hide();
}

// Métodos para la tab Comunicación
/***********************************/

void Mano_Animatronica_Aplicacion::setEstado_UART( int Nuevo_Estado ){
    Estado_Conexion_UART = Nuevo_Estado;
}
int Mano_Animatronica_Aplicacion::getEstado_UART( void ){
    return Estado_Conexion_UART;
}

void Mano_Animatronica_Aplicacion::setEstado_WIFI( int Nuevo_Estado ){
    Estado_Conexion_WIFI = Nuevo_Estado;
}
int Mano_Animatronica_Aplicacion::getEstado_WIFI( void ){
    return Estado_Conexion_WIFI;
}

// Handlers de GUI
void Mano_Animatronica_Aplicacion::on_cBx_Puerto_currentIndexChanged( int index ){

    /*  Labels  */
    QStringList list;
    list = ui->cBx_Puerto->itemData(index).toStringList();
    ui->lbl_UART_Des->setText(tr("Descripción: %1").arg(list.count() > 1 ? list.at(1) : tr(blankString)));
    ui->lbl_UART_Fab->setText(tr("Fabricante: %1").arg(list.count() > 2 ? list.at(2) : tr(blankString)));
    ui->lbl_UART_Nsr->setText(tr("Núm.Serie: %1").arg(list.count() > 3 ? list.at(3) : tr(blankString)));
    ui->lbl_UART_Ubi->setText(tr("Ubicación: %1").arg(list.count() > 4 ? list.at(4) : tr(blankString)));

    if( getEstado_UART() != DESCONECTADO ){

        setEstado_UART( DESCONECTADO );

        /*  SerialPort  */
        if (m_serial->isOpen()){
            m_serial->close();
        }

        /*  Labels   */
        ui->lbl_Estado_Con_UART->setText(TEXTO_DESCONECTADO);
        ui->lbl_Estado_Con_UART->setAlignment(Qt::AlignCenter);
        ui->lbl_Estado_Con_UART->setStyleSheet(FONDO_ROJO_NEGRITA_LETRA_NEGRA);

        /*  PushButton  */
        ui->pushB_Prueba_UART->setEnabled(true);
    }
}
void Mano_Animatronica_Aplicacion::on_pushB_Prueba_UART_clicked( void ){

    /*  Timer   */
    //Timer_UART->start( TIEMPO_DE_ESPERA_UART );

    setEstado_UART( ESPERANDO );

    /*  Label   */
    ui->lbl_Estado_Con_UART->setText(TEXTO_ESPERANDO);
    ui->lbl_Estado_Con_UART->setAlignment(Qt::AlignCenter);
    ui->lbl_Estado_Con_UART->setStyleSheet(FONDO_AMARILLO_NEGRITA_LETRA_NEGRA);

    /*  PushButton  */
    ui->pushB_Prueba_UART->setDisabled(true);

    /*  Prueba UART */
    m_currentSettings.name = ui->cBx_Puerto->currentText();

    m_serial->setPortName(ui->cBx_Puerto->currentText());
    m_serial->setBaudRate(m_currentSettings.baudRate);
    m_serial->setDataBits(m_currentSettings.dataBits);
    m_serial->setParity(m_currentSettings.parity);
    m_serial->setStopBits(m_currentSettings.stopBits);
    m_serial->setFlowControl(m_currentSettings.flowControl);

    if ( m_serial->open(QIODevice::ReadWrite)  ||  m_serial->isOpen() ) {
        setEstado_UART( CONECTADO );

        /*  Label   */
        ui->lbl_Estado_Con_UART->setText(TEXTO_CONECTADO);
        ui->lbl_Estado_Con_UART->setAlignment(Qt::AlignCenter);
        ui->lbl_Estado_Con_UART->setStyleSheet(FONDO_VERDE_NEGRITA_LETRA_NEGRA);

        /*  Tab Controles */
            ui->tab_Controles->setEnabled(true);
    }
    else {
        QMessageBox::critical(this, tr("Error"), m_serial->errorString());
        setEstado_UART(DESCONECTADO);

        /*  Label   */
        ui->lbl_Estado_Con_UART->setText(TEXTO_DESCONECTADO);
        ui->lbl_Estado_Con_UART->setAlignment(Qt::AlignCenter);
        ui->lbl_Estado_Con_UART->setStyleSheet(FONDO_ROJO_NEGRITA_LETRA_NEGRA);

        /*  PushButton  */
        ui->pushB_Prueba_UART->setEnabled(true);
    }
}
void Mano_Animatronica_Aplicacion::on_pushB_Prueba_WIFI_clicked( void ){

    setEstado_WIFI( ESPERANDO );

    /*  Timer   */
    Timer_WIFI->start( TIEMPO_DE_ESPERA_WIFI );

    /*  Label   */
    ui->lbl_Estado_Con_WIFI->setText(TEXTO_ESPERANDO);
    ui->lbl_Estado_Con_WIFI->setAlignment(Qt::AlignCenter);
    ui->lbl_Estado_Con_WIFI->setStyleSheet(FONDO_AMARILLO_NEGRITA_LETRA_NEGRA);

    /*  PushButton  */
    ui->pushB_Prueba_WIFI->setDisabled(true);
}
void Mano_Animatronica_Aplicacion::on_Timer_WIFI_timeout( void ){
    setEstado_WIFI( CONECTADO );

    /*  Label   */
    ui->lbl_Estado_Con_WIFI->setText(TEXTO_CONECTADO);
    ui->lbl_Estado_Con_WIFI->setAlignment(Qt::AlignCenter);
    ui->lbl_Estado_Con_WIFI->setStyleSheet(FONDO_VERDE_NEGRITA_LETRA_NEGRA);

    /*  Pestañas enables & disables */
        ui->tab_Controles->setEnabled(true);
}

// Handlers UART
void Mano_Animatronica_Aplicacion::handler_Error_UART( QSerialPort::SerialPortError error ){
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), m_serial->errorString() + "\nCompruebe si el dispositivo sigue conectado...");
        if (m_serial->isOpen()){
            m_serial->close();
        }

        setEstado_UART(DESCONECTADO);

        /*  Tab Controles   */
        ui->tab_Controles->setDisabled(true);

        /*  Label   */
        ui->lbl_Estado_Con_UART->setText(TEXTO_DESCONECTADO);
        ui->lbl_Estado_Con_UART->setAlignment(Qt::AlignCenter);
        ui->lbl_Estado_Con_UART->setStyleSheet(FONDO_ROJO_NEGRITA_LETRA_NEGRA);

        /*  PushButton  */
        ui->pushB_Prueba_UART->setEnabled(true);

    }
}

void Mano_Animatronica_Aplicacion::handler_ReadyRead( void ){
    static uint32_t qty_ManosRead = 0;
    long bytesAvailable;
    uint8_t aux[TRAMA_DATOS_MANO_SIZE] = {0};
    int pos;

    // protección: a veces al abrir el puerto
    // se reciben 2 bytes 0x0.
    // esto arruina la lectura de las manos
    bytesAvailable = m_serial->bytesAvailable();
    if( (bytesAvailable == 2) && (get_PlayPause_Status() == false) ){
        qty_ManosRead=0;
        return;
    }

    // caso: no se recibió siquiera una trama completa
    if(bytesAvailable >= TRAMA_DATOS_MANO_SIZE){

        // caso: hay al menos una trama completa
        m_serial->read((char *)aux, TRAMA_DATOS_MANO_SIZE);
        pos = (int) *(data_rx.end());
        // escribir la data al buffer interno de datos
        int j=0;
        while(j <= TRAMA_DATOS_MANO_SIZE-1 ){
            data_rx.insert(pos+j, (char)aux[j]);
            j++;
        }
        qty_ManosRead++;
        if(qty_ManosRead == 500){
            qty_ManosRead=0;
        }
    }

    // ??????????????
    // Solo chequeamos el dato recibido cuando llegaron las dos '/' indicando toda una transmision
//    if(data_rx.count('/') == 2){
//        // Borramos la '/' del final y del principio
//        QString dato(data_rx);

//        dato.chop(1); // Sacamos '/' del final
//        dato.remove(0,1); // Sacamos '/' del principio

//        // En esta instancia, en dato solo tendremos XXXX
//        ui->statusBar->showMessage("Ultimo dato: " + dato + " Nuevos bytes para leer: " + QString::number(bytes)); // Mostramos el ultimo dato recibido
//    }

    // por las dudas me dejo esto
    //    data_rx.append(m_serial->readAll());

}

void Mano_Animatronica_Aplicacion::Actualizar_Puertos( void ){
    ui->cBx_Puerto->clear();

    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        QStringList list;
        description = info.description();
        manufacturer = info.manufacturer();
        serialNumber = info.serialNumber();
        list << info.portName()
             << (!description.isEmpty() ? description : blankString)
             << (!manufacturer.isEmpty() ? manufacturer : blankString)
             << (!serialNumber.isEmpty() ? serialNumber : blankString)
             << info.systemLocation()
             /*<< (info.vendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : blankString)
             << (info.productIdentifier() ? QString::number(info.productIdentifier(), 16) : blankString)*/;

        ui->cBx_Puerto->addItem(list.first(), list);
    }
    ui->cBx_Puerto->setCurrentIndex(0);
    m_currentSettings.name = ui->cBx_Puerto->currentText();
}


// Métodos para la tab Controles
/********************************/

void Mano_Animatronica_Aplicacion::setModo( int Nuevo_Modo ){
    Modo = Nuevo_Modo;
}
int Mano_Animatronica_Aplicacion::getModo( void ){
    return Modo;
}

void Mano_Animatronica_Aplicacion::set_PlayPause_Status(bool NewStatus){
    f_PlayPause_Status = NewStatus;
}
bool Mano_Animatronica_Aplicacion::get_PlayPause_Status(void){
    return f_PlayPause_Status;
}

void Mano_Animatronica_Aplicacion::set_Movements_Loaded_Status(bool NewStatus){
    f_Movements_Loaded = NewStatus;
}
bool Mano_Animatronica_Aplicacion::get_Movements_Loaded_Status(){
    return f_Movements_Loaded;
}

void Mano_Animatronica_Aplicacion::on_cBx_Modo_activated( int index ){

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

void Mano_Animatronica_Aplicacion::on_rdB_Guante_PC_clicked( void ){

    /*  Status Bar    */
    QString MensajeStatusBar;
    MensajeStatusBar = "MODO GUANTE_PC";
    ui->statusBar->showMessage( MensajeStatusBar );

    /*  ComboBox Modo */
    ui->cBx_Modo->setCurrentIndex( GUANTE_PC );
    setModo(GUANTE_PC);

    /*  Widgets enables & disables  */
    ui->grB_Mano->setEnabled(true);
    ui->grB_Sliders->setDisabled(true);
    ui->grB_Valores->setEnabled(true);
    ui->pushB_Cargar->setDisabled(true);
    ui->pushB_Guardar->setEnabled(true);        // chiama: cambié de disabled a enabled
    ui->pushB_PlayPause->setEnabled(true);
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
void Mano_Animatronica_Aplicacion::on_rdB_PC_Mano_clicked( void ){

    /*  Status Bar    */
    QString MensajeStatusBar;
    MensajeStatusBar = "MODO PC_MANO";
    ui->statusBar->showMessage( MensajeStatusBar );

    /*  ComboBox Modo */
    ui->cBx_Modo->setCurrentIndex( PC_MANO );
    setModo( PC_MANO );

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
void Mano_Animatronica_Aplicacion::on_rdB_Guante_Mano_clicked( void ){

    /*  MODO    */
    QString MensajeStatusBar;
    MensajeStatusBar = "MODO GUANTE_MANO";
    ui->statusBar->showMessage( MensajeStatusBar );

    /*  ComboBox Modo */
    ui->cBx_Modo->setCurrentIndex( GUANTE_MANO );
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

void Mano_Animatronica_Aplicacion::on_sld_Menor_valueChanged( int value ){
    if( getModo() == PC_MANO ){
        value = (value * MAX_VAL) / ui->sld_Menor->maximum();

        /*  GroupBox Mano   */
        ActualizarImagenMano( ui, ui->sld_Menor->value(), ui->sld_Anular->value(), ui->sld_Mayor->value(), ui->sld_Indice->value(), ui->sld_Pulgar->value() );

        /*  Label   */
        ui->lbl_VMenor->setText( "Menor : " + QString::number(value));
    }
}
void Mano_Animatronica_Aplicacion::on_sld_Anular_valueChanged( int value ){
    if( getModo() == PC_MANO ){
        value = (value * MAX_VAL) / ui->sld_Anular->maximum();

        /*  GroupBox Mano   */
        ActualizarImagenMano( ui, ui->sld_Menor->value(), ui->sld_Anular->value(), ui->sld_Mayor->value(), ui->sld_Indice->value(), ui->sld_Pulgar->value() );

        /*  Label   */
        ui->lbl_VAnular->setText( "Anular : " + QString::number(value));
    }
}
void Mano_Animatronica_Aplicacion::on_sld_Mayor_valueChanged( int value ){
    if( getModo() == PC_MANO ){
        value = (value * MAX_VAL) / ui->sld_Mayor->maximum();

        /*  GroupBox Mano   */
        ActualizarImagenMano( ui, ui->sld_Menor->value(), ui->sld_Anular->value(), ui->sld_Mayor->value(), ui->sld_Indice->value(), ui->sld_Pulgar->value() );

        /*  Label   */
        ui->lbl_VMayor->setText( "Mayor : " + QString::number(value));
    }
}
void Mano_Animatronica_Aplicacion::on_sld_Indice_valueChanged( int value ){
    if( getModo() == PC_MANO ){
        value = (value * MAX_VAL) / ui->sld_Indice->maximum();

        /*  GroupBox Mano   */
        ActualizarImagenMano( ui, ui->sld_Menor->value(), ui->sld_Anular->value(), ui->sld_Mayor->value(), ui->sld_Indice->value(), ui->sld_Pulgar->value() );

        /*  Label   */
        ui->lbl_VIndice->setText( "Indice : " + QString::number(value));
    }
}
void Mano_Animatronica_Aplicacion::on_sld_Pulgar_valueChanged( int value ){
    if( getModo() == PC_MANO ){
        value = (value * MAX_VAL) / ui->sld_Pulgar->maximum();

        /*  GroupBox Mano   */
        ActualizarImagenMano( ui, ui->sld_Menor->value(), ui->sld_Anular->value(), ui->sld_Mayor->value(), ui->sld_Indice->value(), ui->sld_Pulgar->value() );

        /*  Label   */
        ui->lbl_VPulgar->setText( "Pulgar : " + QString::number(value));
    }
}

void Mano_Animatronica_Aplicacion::on_pushB_PlayPause_clicked(){
    int SelectedMode;
    bool status;

    // Protección: doble click de mi mouse
    static int entered=0;
    entered++;
    if( entered == 2 ){
        entered = 0;
        return;
    }

    // Lectura del estado actual: estado activo/inactivo y modo
    status = get_PlayPause_Status();
    SelectedMode = getModo();

    // protección: no hay movimientos cargados para enviar y se está en modo PC_MANO
    if( (status == false) && (SelectedMode == PC_MANO) && (get_Movements_Loaded_Status() == false) ){
        QMessageBox::critical(this, tr("Error"), "Can't send movements if none have been loaded.");
        return;
    }

    // caso: inactivo
    if( status == false ){
        set_PlayPause_Status(true);
        // deshabilito el cambio de modo
        ui->grB_Modo->setDisabled(true);

        // limpio el buffer interno de data recibida
        data_rx.clear();

        // enviar comando para comenzar el modo, según cual sea
        if( SelectedMode == GUANTE_MANO){
            // no implementado
        }
        if( SelectedMode == GUANTE_PC){
            // Enviar $M1#
            m_serial->write( COMANDO_COMIENZO_GUANTE_PC, sizeof(COMANDO_COMIENZO_GUANTE_PC) );
//            m_serial->flush();
        }
        if( SelectedMode == PC_MANO){
           // Enviar $MPM1#
            m_serial->write( COMANDO_COMIENZO_PC_MANO, sizeof(COMANDO_COMIENZO_PC_MANO) );
//            m_serial->flush();

            // Enviar movimientos
            SendLoadedMovements();
        }
    }
    // caso: activo
    else if( status == true ){
        set_PlayPause_Status(false);
        // re-habilito el cambio de modo
        ui->grB_Modo->setEnabled(true);

        // enviar comando para detener el modo, según cual sea
        if( SelectedMode == GUANTE_MANO){
            // no implementado
        }
        if( SelectedMode == GUANTE_PC){
            // Enviar $M0#
            m_serial->write( COMANDO_DETENER_GUANTE_PC, sizeof(COMANDO_DETENER_GUANTE_PC) );
//            m_serial->flush();
        }
        if( SelectedMode == PC_MANO){
           // Enviar $MPM0#
            m_serial->write( COMANDO_DETENER_PC_MANO, sizeof(COMANDO_DETENER_PC_MANO) );
//            m_serial->flush();
        }
    }

}

void Mano_Animatronica_Aplicacion::on_pushB_Guardar_clicked(){

    // protección: click doble de mi mouse
    static uint8_t entered = 0;
    entered++;
    if( entered == 2 ){
        entered=0;
        return;
    }

    // protección: guardar mientras se está activo algún modo
    if( get_PlayPause_Status() == true ){
        QMessageBox::critical(this, tr("Error"), "Can't save movements, internal data buffer is busy. Stop current mode first.");
        return;
    }

    // protección: guardar pero que data_rx esté vacío
    if( data_rx.isEmpty() ){
        QMessageBox::critical(this, tr("Error"), "Can't save movements if no data has been adquired.");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               "/home/cha/mov_untitled.mno",
                               tr(".mno"));
    QFile savefile(fileName);

    savefile.open(QIODevice::WriteOnly);
    savefile.write(data_rx, data_rx.size());
    savefile.close();
}

void Mano_Animatronica_Aplicacion::on_pushB_Cargar_clicked(){

    // protección: click doble de mi mouse
    static uint8_t entered = 0;
    entered++;
    if( entered == 2 ){
        entered=0;
        return;
    }

    // protección: cargar mientras está activo algún modo
    if( get_PlayPause_Status() == true ){
        if( getModo() == PC_MANO ){
            QMessageBox::critical(this, tr("Error"), "Can't load movements, internal data buffer is busy. Stop current mode first.");
        }
        return;
    }

    // Obtengo el nombre del archivo a abrir
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                 "/home/cha");

    // Protección: se cargó un archivo que no termina en .mno
    if( fileName.endsWith(".mno", Qt::CaseSensitive) == false ){
        QMessageBox::critical(this, tr("Error"), "Can't load files which are not of the '.mno' type.");
        return;
    }

    // Abro el archivo
    QFile Movements(fileName);
    Movements.open(QIODevice::ReadOnly);

    // Lo cargo en el buffer interno de datos
    data_rx.clear();
    data_rx = Movements.readAll();

    Movements.close();

    f_Movements_Loaded = true;
}

void Mano_Animatronica_Aplicacion::SendLoadedMovements(){
    m_serial->write((char *)&data_rx, sizeof(data_rx));
//    m_serial->flush();
}





// Otras Funciones
/*******************/

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
