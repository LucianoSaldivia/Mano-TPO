/********************************************************************************
** Form generated from reading UI file 'mano_animatronica_aplicacion.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANO_ANIMATRONICA_APLICACION_H
#define UI_MANO_ANIMATRONICA_APLICACION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Mano_Animatronica_Aplicacion
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab_Comunicacion;
    QGroupBox *grB_Con_WIFI;
    QPushButton *pushB_Prueba_WIFI;
    QLabel *lbl_Estado_Con_WIFI;
    QGroupBox *grB_Com_UART;
    QLabel *lbl_Titulo_Puerto;
    QPushButton *pushB_Actualizar;
    QComboBox *cBx_Puerto;
    QPushButton *pushB_Prueba_UART;
    QLabel *lbl_Estado_Con_UART;
    QLabel *lbl_Titulo_Estado_UART;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *VLyt_Config;
    QLabel *lbl_BaudRate;
    QLabel *lbl_DataBits;
    QLabel *lbl_FlowControl;
    QLabel *lbl_StopBits;
    QLabel *lbl_Parity;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *VLyt_Info;
    QLabel *lbl_UART_Des;
    QLabel *lbl_UART_Fab;
    QLabel *lbl_UART_Nsr;
    QLabel *lbl_UART_Ubi;
    QLabel *lbl_Titulo_Config;
    QLabel *lbl_Titulo_Info;
    QWidget *tab_Controles;
    QPushButton *pushB_PlayPause;
    QLabel *lbl_Archivo;
    QPushButton *pushB_Cargar;
    QGroupBox *grB_Sliders;
    QSlider *sld_Mayor;
    QSlider *sld_Anular;
    QSlider *sld_Menor;
    QSlider *sld_Pulgar;
    QSlider *sld_Indice;
    QLabel *lbl_Sliders;
    QGroupBox *grB_Modo;
    QComboBox *cBx_Modo;
    QRadioButton *rdB_Guante_PC;
    QRadioButton *rdB_PC_Mano;
    QRadioButton *rdB_Guante_Mano;
    QGroupBox *grB_Valores;
    QLabel *lbl_VMenor;
    QLabel *lbl_VAnular;
    QLabel *lbl_VMayor;
    QLabel *lbl_VIndice;
    QLabel *lbl_VPulgar;
    QGroupBox *grB_Mano;
    QLabel *lbl_1_Base_Img;
    QLabel *lbl_2_Menor_Img;
    QLabel *lbl_3_Anular_Img;
    QLabel *lbl_4_Mayor_Img;
    QLabel *lbl_5_Indice_Img;
    QLabel *lbl_6_Pulgar_Img;
    QPushButton *pushB_Guardar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Mano_Animatronica_Aplicacion)
    {
        if (Mano_Animatronica_Aplicacion->objectName().isEmpty())
            Mano_Animatronica_Aplicacion->setObjectName(QStringLiteral("Mano_Animatronica_Aplicacion"));
        Mano_Animatronica_Aplicacion->resize(695, 572);
        centralWidget = new QWidget(Mano_Animatronica_Aplicacion);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 691, 551));
        tab_Comunicacion = new QWidget();
        tab_Comunicacion->setObjectName(QStringLiteral("tab_Comunicacion"));
        grB_Con_WIFI = new QGroupBox(tab_Comunicacion);
        grB_Con_WIFI->setObjectName(QStringLiteral("grB_Con_WIFI"));
        grB_Con_WIFI->setGeometry(QRect(10, 280, 660, 231));
        pushB_Prueba_WIFI = new QPushButton(grB_Con_WIFI);
        pushB_Prueba_WIFI->setObjectName(QStringLiteral("pushB_Prueba_WIFI"));
        pushB_Prueba_WIFI->setGeometry(QRect(60, 90, 201, 61));
        lbl_Estado_Con_WIFI = new QLabel(grB_Con_WIFI);
        lbl_Estado_Con_WIFI->setObjectName(QStringLiteral("lbl_Estado_Con_WIFI"));
        lbl_Estado_Con_WIFI->setGeometry(QRect(370, 90, 201, 61));
        lbl_Estado_Con_WIFI->setAlignment(Qt::AlignCenter);
        grB_Com_UART = new QGroupBox(tab_Comunicacion);
        grB_Com_UART->setObjectName(QStringLiteral("grB_Com_UART"));
        grB_Com_UART->setGeometry(QRect(10, 10, 661, 261));
        lbl_Titulo_Puerto = new QLabel(grB_Com_UART);
        lbl_Titulo_Puerto->setObjectName(QStringLiteral("lbl_Titulo_Puerto"));
        lbl_Titulo_Puerto->setGeometry(QRect(10, 30, 61, 16));
        pushB_Actualizar = new QPushButton(grB_Com_UART);
        pushB_Actualizar->setObjectName(QStringLiteral("pushB_Actualizar"));
        pushB_Actualizar->setGeometry(QRect(170, 70, 121, 31));
        cBx_Puerto = new QComboBox(grB_Com_UART);
        cBx_Puerto->setObjectName(QStringLiteral("cBx_Puerto"));
        cBx_Puerto->setGeometry(QRect(10, 70, 151, 31));
        pushB_Prueba_UART = new QPushButton(grB_Com_UART);
        pushB_Prueba_UART->setObjectName(QStringLiteral("pushB_Prueba_UART"));
        pushB_Prueba_UART->setGeometry(QRect(170, 160, 121, 71));
        lbl_Estado_Con_UART = new QLabel(grB_Com_UART);
        lbl_Estado_Con_UART->setObjectName(QStringLiteral("lbl_Estado_Con_UART"));
        lbl_Estado_Con_UART->setGeometry(QRect(10, 160, 151, 71));
        lbl_Estado_Con_UART->setFocusPolicy(Qt::NoFocus);
        lbl_Estado_Con_UART->setLayoutDirection(Qt::LeftToRight);
        lbl_Estado_Con_UART->setAlignment(Qt::AlignCenter);
        lbl_Titulo_Estado_UART = new QLabel(grB_Com_UART);
        lbl_Titulo_Estado_UART->setObjectName(QStringLiteral("lbl_Titulo_Estado_UART"));
        lbl_Titulo_Estado_UART->setGeometry(QRect(10, 120, 151, 16));
        verticalLayoutWidget_4 = new QWidget(grB_Com_UART);
        verticalLayoutWidget_4->setObjectName(QStringLiteral("verticalLayoutWidget_4"));
        verticalLayoutWidget_4->setGeometry(QRect(350, 160, 301, 96));
        VLyt_Config = new QVBoxLayout(verticalLayoutWidget_4);
        VLyt_Config->setSpacing(6);
        VLyt_Config->setContentsMargins(11, 11, 11, 11);
        VLyt_Config->setObjectName(QStringLiteral("VLyt_Config"));
        VLyt_Config->setContentsMargins(0, 0, 0, 0);
        lbl_BaudRate = new QLabel(verticalLayoutWidget_4);
        lbl_BaudRate->setObjectName(QStringLiteral("lbl_BaudRate"));

        VLyt_Config->addWidget(lbl_BaudRate);

        lbl_DataBits = new QLabel(verticalLayoutWidget_4);
        lbl_DataBits->setObjectName(QStringLiteral("lbl_DataBits"));

        VLyt_Config->addWidget(lbl_DataBits);

        lbl_FlowControl = new QLabel(verticalLayoutWidget_4);
        lbl_FlowControl->setObjectName(QStringLiteral("lbl_FlowControl"));

        VLyt_Config->addWidget(lbl_FlowControl);

        lbl_StopBits = new QLabel(verticalLayoutWidget_4);
        lbl_StopBits->setObjectName(QStringLiteral("lbl_StopBits"));

        VLyt_Config->addWidget(lbl_StopBits);

        lbl_Parity = new QLabel(verticalLayoutWidget_4);
        lbl_Parity->setObjectName(QStringLiteral("lbl_Parity"));

        VLyt_Config->addWidget(lbl_Parity);

        verticalLayoutWidget_3 = new QWidget(grB_Com_UART);
        verticalLayoutWidget_3->setObjectName(QStringLiteral("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(350, 40, 301, 81));
        VLyt_Info = new QVBoxLayout(verticalLayoutWidget_3);
        VLyt_Info->setSpacing(6);
        VLyt_Info->setContentsMargins(11, 11, 11, 11);
        VLyt_Info->setObjectName(QStringLiteral("VLyt_Info"));
        VLyt_Info->setContentsMargins(0, 0, 0, 0);
        lbl_UART_Des = new QLabel(verticalLayoutWidget_3);
        lbl_UART_Des->setObjectName(QStringLiteral("lbl_UART_Des"));

        VLyt_Info->addWidget(lbl_UART_Des);

        lbl_UART_Fab = new QLabel(verticalLayoutWidget_3);
        lbl_UART_Fab->setObjectName(QStringLiteral("lbl_UART_Fab"));

        VLyt_Info->addWidget(lbl_UART_Fab);

        lbl_UART_Nsr = new QLabel(verticalLayoutWidget_3);
        lbl_UART_Nsr->setObjectName(QStringLiteral("lbl_UART_Nsr"));

        VLyt_Info->addWidget(lbl_UART_Nsr);

        lbl_UART_Ubi = new QLabel(verticalLayoutWidget_3);
        lbl_UART_Ubi->setObjectName(QStringLiteral("lbl_UART_Ubi"));

        VLyt_Info->addWidget(lbl_UART_Ubi);

        lbl_Titulo_Config = new QLabel(grB_Com_UART);
        lbl_Titulo_Config->setObjectName(QStringLiteral("lbl_Titulo_Config"));
        lbl_Titulo_Config->setGeometry(QRect(320, 140, 91, 16));
        lbl_Titulo_Info = new QLabel(grB_Com_UART);
        lbl_Titulo_Info->setObjectName(QStringLiteral("lbl_Titulo_Info"));
        lbl_Titulo_Info->setGeometry(QRect(320, 20, 151, 16));
        tabWidget->addTab(tab_Comunicacion, QString());
        tab_Controles = new QWidget();
        tab_Controles->setObjectName(QStringLiteral("tab_Controles"));
        pushB_PlayPause = new QPushButton(tab_Controles);
        pushB_PlayPause->setObjectName(QStringLiteral("pushB_PlayPause"));
        pushB_PlayPause->setGeometry(QRect(250, 80, 171, 91));
        lbl_Archivo = new QLabel(tab_Controles);
        lbl_Archivo->setObjectName(QStringLiteral("lbl_Archivo"));
        lbl_Archivo->setGeometry(QRect(440, 20, 191, 31));
        pushB_Cargar = new QPushButton(tab_Controles);
        pushB_Cargar->setObjectName(QStringLiteral("pushB_Cargar"));
        pushB_Cargar->setGeometry(QRect(10, 270, 131, 51));
        grB_Sliders = new QGroupBox(tab_Controles);
        grB_Sliders->setObjectName(QStringLiteral("grB_Sliders"));
        grB_Sliders->setGeometry(QRect(150, 220, 281, 241));
        sld_Mayor = new QSlider(grB_Sliders);
        sld_Mayor->setObjectName(QStringLiteral("sld_Mayor"));
        sld_Mayor->setGeometry(QRect(130, 59, 20, 171));
        sld_Mayor->setMaximum(140);
        sld_Mayor->setOrientation(Qt::Vertical);
        sld_Mayor->setInvertedAppearance(true);
        sld_Anular = new QSlider(grB_Sliders);
        sld_Anular->setObjectName(QStringLiteral("sld_Anular"));
        sld_Anular->setGeometry(QRect(70, 59, 20, 171));
        sld_Anular->setMaximum(140);
        sld_Anular->setOrientation(Qt::Vertical);
        sld_Anular->setInvertedAppearance(true);
        sld_Menor = new QSlider(grB_Sliders);
        sld_Menor->setObjectName(QStringLiteral("sld_Menor"));
        sld_Menor->setGeometry(QRect(10, 59, 20, 171));
        sld_Menor->setMaximum(120);
        sld_Menor->setOrientation(Qt::Vertical);
        sld_Menor->setInvertedAppearance(true);
        sld_Pulgar = new QSlider(grB_Sliders);
        sld_Pulgar->setObjectName(QStringLiteral("sld_Pulgar"));
        sld_Pulgar->setGeometry(QRect(250, 59, 16, 171));
        sld_Pulgar->setMaximum(120);
        sld_Pulgar->setOrientation(Qt::Vertical);
        sld_Pulgar->setInvertedAppearance(true);
        sld_Indice = new QSlider(grB_Sliders);
        sld_Indice->setObjectName(QStringLiteral("sld_Indice"));
        sld_Indice->setGeometry(QRect(190, 59, 16, 171));
        sld_Indice->setMaximum(140);
        sld_Indice->setOrientation(Qt::Vertical);
        sld_Indice->setInvertedAppearance(true);
        lbl_Sliders = new QLabel(grB_Sliders);
        lbl_Sliders->setObjectName(QStringLiteral("lbl_Sliders"));
        lbl_Sliders->setGeometry(QRect(0, 30, 281, 20));
        grB_Modo = new QGroupBox(tab_Controles);
        grB_Modo->setObjectName(QStringLiteral("grB_Modo"));
        grB_Modo->setGeometry(QRect(10, 10, 221, 201));
        cBx_Modo = new QComboBox(grB_Modo);
        cBx_Modo->addItem(QString());
        cBx_Modo->addItem(QString());
        cBx_Modo->addItem(QString());
        cBx_Modo->addItem(QString());
        cBx_Modo->setObjectName(QStringLiteral("cBx_Modo"));
        cBx_Modo->setGeometry(QRect(10, 30, 191, 31));
        rdB_Guante_PC = new QRadioButton(grB_Modo);
        rdB_Guante_PC->setObjectName(QStringLiteral("rdB_Guante_PC"));
        rdB_Guante_PC->setGeometry(QRect(20, 70, 111, 31));
        rdB_PC_Mano = new QRadioButton(grB_Modo);
        rdB_PC_Mano->setObjectName(QStringLiteral("rdB_PC_Mano"));
        rdB_PC_Mano->setGeometry(QRect(20, 110, 111, 31));
        rdB_Guante_Mano = new QRadioButton(grB_Modo);
        rdB_Guante_Mano->setObjectName(QStringLiteral("rdB_Guante_Mano"));
        rdB_Guante_Mano->setGeometry(QRect(20, 150, 181, 31));
        grB_Valores = new QGroupBox(tab_Controles);
        grB_Valores->setObjectName(QStringLiteral("grB_Valores"));
        grB_Valores->setGeometry(QRect(10, 460, 671, 51));
        lbl_VMenor = new QLabel(grB_Valores);
        lbl_VMenor->setObjectName(QStringLiteral("lbl_VMenor"));
        lbl_VMenor->setGeometry(QRect(10, 20, 91, 31));
        lbl_VAnular = new QLabel(grB_Valores);
        lbl_VAnular->setObjectName(QStringLiteral("lbl_VAnular"));
        lbl_VAnular->setGeometry(QRect(110, 20, 91, 31));
        lbl_VMayor = new QLabel(grB_Valores);
        lbl_VMayor->setObjectName(QStringLiteral("lbl_VMayor"));
        lbl_VMayor->setGeometry(QRect(210, 20, 91, 31));
        lbl_VIndice = new QLabel(grB_Valores);
        lbl_VIndice->setObjectName(QStringLiteral("lbl_VIndice"));
        lbl_VIndice->setGeometry(QRect(310, 20, 91, 31));
        lbl_VPulgar = new QLabel(grB_Valores);
        lbl_VPulgar->setObjectName(QStringLiteral("lbl_VPulgar"));
        lbl_VPulgar->setGeometry(QRect(410, 20, 91, 31));
        grB_Mano = new QGroupBox(tab_Controles);
        grB_Mano->setObjectName(QStringLiteral("grB_Mano"));
        grB_Mano->setGeometry(QRect(440, 50, 241, 411));
        lbl_1_Base_Img = new QLabel(grB_Mano);
        lbl_1_Base_Img->setObjectName(QStringLiteral("lbl_1_Base_Img"));
        lbl_1_Base_Img->setGeometry(QRect(10, 20, 216, 384));
        lbl_2_Menor_Img = new QLabel(grB_Mano);
        lbl_2_Menor_Img->setObjectName(QStringLiteral("lbl_2_Menor_Img"));
        lbl_2_Menor_Img->setGeometry(QRect(10, 20, 216, 384));
        lbl_3_Anular_Img = new QLabel(grB_Mano);
        lbl_3_Anular_Img->setObjectName(QStringLiteral("lbl_3_Anular_Img"));
        lbl_3_Anular_Img->setGeometry(QRect(10, 20, 216, 384));
        lbl_4_Mayor_Img = new QLabel(grB_Mano);
        lbl_4_Mayor_Img->setObjectName(QStringLiteral("lbl_4_Mayor_Img"));
        lbl_4_Mayor_Img->setGeometry(QRect(10, 20, 216, 384));
        lbl_5_Indice_Img = new QLabel(grB_Mano);
        lbl_5_Indice_Img->setObjectName(QStringLiteral("lbl_5_Indice_Img"));
        lbl_5_Indice_Img->setGeometry(QRect(10, 20, 216, 384));
        lbl_6_Pulgar_Img = new QLabel(grB_Mano);
        lbl_6_Pulgar_Img->setObjectName(QStringLiteral("lbl_6_Pulgar_Img"));
        lbl_6_Pulgar_Img->setGeometry(QRect(10, 20, 216, 384));
        pushB_Guardar = new QPushButton(tab_Controles);
        pushB_Guardar->setObjectName(QStringLiteral("pushB_Guardar"));
        pushB_Guardar->setGeometry(QRect(10, 360, 131, 51));
        tabWidget->addTab(tab_Controles, QString());
        Mano_Animatronica_Aplicacion->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Mano_Animatronica_Aplicacion);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Mano_Animatronica_Aplicacion->setStatusBar(statusBar);

        retranslateUi(Mano_Animatronica_Aplicacion);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Mano_Animatronica_Aplicacion);
    } // setupUi

    void retranslateUi(QMainWindow *Mano_Animatronica_Aplicacion)
    {
        Mano_Animatronica_Aplicacion->setWindowTitle(QApplication::translate("Mano_Animatronica_Aplicacion", "Mano_Animatronica_Aplicacion", nullptr));
        grB_Con_WIFI->setTitle(QApplication::translate("Mano_Animatronica_Aplicacion", "Conexi\303\263n Wi-Fi", nullptr));
        pushB_Prueba_WIFI->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "Comprobar conexi\303\263n \n"
" del Puerto Wi-Fi configurado", nullptr));
        lbl_Estado_Con_WIFI->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "Desconectado", nullptr));
        grB_Com_UART->setTitle(QApplication::translate("Mano_Animatronica_Aplicacion", "Conexi\303\263n UART", nullptr));
        lbl_Titulo_Puerto->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "Puerto", nullptr));
        pushB_Actualizar->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "Actualizar", nullptr));
        pushB_Prueba_UART->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "Conectar", nullptr));
        lbl_Estado_Con_UART->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "Desconectado", nullptr));
        lbl_Titulo_Estado_UART->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "Estado de la conexi\303\263n", nullptr));
        lbl_BaudRate->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "Taza de Baudios: ", nullptr));
        lbl_DataBits->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "Bits de Datos: ", nullptr));
        lbl_FlowControl->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "Control de Flujo: ", nullptr));
        lbl_StopBits->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "Bits de Stop: ", nullptr));
        lbl_Parity->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "Paridad: ", nullptr));
        lbl_UART_Des->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "Descripci\303\263n:", nullptr));
        lbl_UART_Fab->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "Fabricante:", nullptr));
        lbl_UART_Nsr->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "N\303\272m.Serie:", nullptr));
        lbl_UART_Ubi->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "Ubicaci\303\263n:", nullptr));
        lbl_Titulo_Config->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "Configuracion", nullptr));
        lbl_Titulo_Info->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "Informacion del puerto", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_Comunicacion), QApplication::translate("Mano_Animatronica_Aplicacion", "Comunicaci\303\263n", nullptr));
        pushB_PlayPause->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "Play / Pause", nullptr));
        lbl_Archivo->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "Nombre_archivo.hnd", nullptr));
        pushB_Cargar->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "Cargar \n"
" Movimientos", nullptr));
        grB_Sliders->setTitle(QApplication::translate("Mano_Animatronica_Aplicacion", "Sliders", nullptr));
        lbl_Sliders->setText(QApplication::translate("Mano_Animatronica_Aplicacion", " Menor     Anular     Mayor      Incide      Pulgar", nullptr));
        grB_Modo->setTitle(QApplication::translate("Mano_Animatronica_Aplicacion", "Modo de Operaci\303\263n", nullptr));
        cBx_Modo->setItemText(0, QApplication::translate("Mano_Animatronica_Aplicacion", "Seleccione Modo", nullptr));
        cBx_Modo->setItemText(1, QApplication::translate("Mano_Animatronica_Aplicacion", "Guante -> PC", nullptr));
        cBx_Modo->setItemText(2, QApplication::translate("Mano_Animatronica_Aplicacion", "PC -> Mano", nullptr));
        cBx_Modo->setItemText(3, QApplication::translate("Mano_Animatronica_Aplicacion", "Guante -> Mano", nullptr));

        rdB_Guante_PC->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "Guante -> PC", nullptr));
        rdB_PC_Mano->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "PC -> Mano", nullptr));
        rdB_Guante_Mano->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "Guante -> Mano", nullptr));
        grB_Valores->setTitle(QApplication::translate("Mano_Animatronica_Aplicacion", "Valores actuales", nullptr));
        lbl_VMenor->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "Menor : 0", nullptr));
        lbl_VAnular->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "Anular : 0", nullptr));
        lbl_VMayor->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "Mayor : 0", nullptr));
        lbl_VIndice->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "Indice : 0", nullptr));
        lbl_VPulgar->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "Pulgar : 0", nullptr));
        grB_Mano->setTitle(QApplication::translate("Mano_Animatronica_Aplicacion", "Mano", nullptr));
        lbl_1_Base_Img->setText(QString());
        lbl_2_Menor_Img->setText(QString());
        lbl_3_Anular_Img->setText(QString());
        lbl_4_Mayor_Img->setText(QString());
        lbl_5_Indice_Img->setText(QString());
        lbl_6_Pulgar_Img->setText(QString());
        pushB_Guardar->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "Guardar \n"
" Movimientos", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_Controles), QApplication::translate("Mano_Animatronica_Aplicacion", "Controles", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Mano_Animatronica_Aplicacion: public Ui_Mano_Animatronica_Aplicacion {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANO_ANIMATRONICA_APLICACION_H
