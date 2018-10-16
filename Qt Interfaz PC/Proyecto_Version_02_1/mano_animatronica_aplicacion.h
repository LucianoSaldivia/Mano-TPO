#ifndef MANO_ANIMATRONICA_APLICACION_H
#define MANO_ANIMATRONICA_APLICACION_H

#include <QMainWindow>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QTimer>
#include <QTime>
#include <QSlider>

/*  Parametros Puerto Serie */
#define BAUD_RATE           QSerialPort::Baud9600
#define STR_BAUD_RATE       "9600"
#define DATA_BITS           QSerialPort::Data8
#define STR_DATA_BITS       "8"
#define PARITY              QSerialPort::NoParity
#define STR_PARITY          "None"
#define STOP_BITS           QSerialPort::OneStop
#define STR_STOP_BITS       "1"
#define FLOW_CONTROL        QSerialPort::NoFlowControl
#define STR_FLOW_CONTROL    "None"

/*  Modos   */
#define NINGUN_MODO 0
#define GUANTE_PC   1
#define PC_MANO     2
#define GUANTE_MANO 3

/*  Estados */
#define DESCONECTADO 0
#define ESPERANDO   1
#define CONECTADO   2

/*  QByteArray de prueba    */
#define TEXTO_A_ENVIAR    "#S$"
//#define TEXTO_A_RECIBIR   "Rx = #S$"

/*  Tiempos */
#define TIEMPO_DE_ESPERA_UART 1500
#define TIEMPO_DE_ESPERA_WIFI 1000

/*  Textos Conexión */
#define TEXTO_DESCONECTADO "DESCONECTADO"
#define TEXTO_ESPERANDO "ESPERANDO..."
#define TEXTO_CONECTADO "CONECTADO !"

/*  Colores */
//  Para conseguir otros colores, https://htmlcolorcodes.com/
#define FONDO_ROJO_NEGRITA_LETRA_NEGRA        "QLabel { background-color: #D71B17 ; font-weight: bold; color : #000000; }"
#define FONDO_AMARILLO_NEGRITA_LETRA_NEGRA    "QLabel { background-color: #D2CF00 ; font-weight: bold; color : #000000; }"
#define FONDO_VERDE_NEGRITA_LETRA_NEGRA       "QLabel { background-color: #38CC25 ; font-weight: bold; color : #000000; }"

/*  Maximo Valor de lectura analógica */
#define MAX_VAL 1024

namespace Ui {
class Mano_Animatronica_Aplicacion;
}

class Mano_Animatronica_Aplicacion : public QMainWindow
{
    Q_OBJECT

public:

    explicit Mano_Animatronica_Aplicacion(QWidget *parent = nullptr);

    ~Mano_Animatronica_Aplicacion();

    struct Settings {
        QString name;
        qint32 baudRate;
        QString stringBaudRate;
        QSerialPort::DataBits dataBits;
        QString stringDataBits;
        QSerialPort::Parity parity;
        QString stringParity;
        QSerialPort::StopBits stopBits;
        QString stringStopBits;
        QSerialPort::FlowControl flowControl;
        QString stringFlowControl;
        bool localEchoEnabled;
    };

    Settings settings() const;

    void setModo( int Mode );
    int getModo();

    void setEstado_UART( int Estado );
    int getEstado_UART();

    void setEstado_WIFI( int Estado );
    int getEstado_WIFI();

private slots:
    //void readData();
    void handler_Error_UART(QSerialPort::SerialPortError error);
    void Actualizar_Puertos();

    void on_cBx_Modo_activated(int index);
    void on_cBx_Puerto_currentIndexChanged(int index);

    void on_rdB_Guante_PC_clicked();
    void on_rdB_PC_Mano_clicked();
    void on_rdB_Guante_Mano_clicked();

    void on_sld_Menor_valueChanged(int value);
    void on_sld_Anular_valueChanged(int value);
    void on_sld_Mayor_valueChanged(int value);
    void on_sld_Indice_valueChanged(int value);
    void on_sld_Pulgar_valueChanged(int value);

    void on_pushB_Prueba_UART_clicked();
    void handler_ReadyRead();

    void on_pushB_Prueba_WIFI_clicked();
    void on_Timer_WIFI_timeout();

private:
    Ui::Mano_Animatronica_Aplicacion *ui;

    Settings m_currentSettings;

    QSerialPort *m_serial;

    QTimer *Timer_WIFI;

    QString description, manufacturer, serialNumber;

    int Modo, Estado_Conexion_UART, Estado_Conexion_WIFI;

};

void ActualizarImagenMano( Ui::Mano_Animatronica_Aplicacion * ui, int Menor, int Anular, int Mayor, int Indice, int Pulgar );
void ActualizarImagenMano( Ui::Mano_Animatronica_Aplicacion * ui, QSlider *Menor, QSlider *Anular, QSlider *Mayor, QSlider *Indice, QSlider *Pulgar );

#endif // MANO_ANIMATRONICA_APLICACION_H
