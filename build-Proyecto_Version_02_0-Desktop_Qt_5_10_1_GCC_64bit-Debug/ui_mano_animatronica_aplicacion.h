/********************************************************************************
** Form generated from reading UI file 'mano_animatronica_aplicacion.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANO_ANIMATRONICA_APLICACION_H
#define UI_MANO_ANIMATRONICA_APLICACION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Mano_Animatronica_Aplicacion
{
public:
    QWidget *centralWidget;
    QPushButton *pushB_Cargar;
    QPushButton *pushB_PlayPause;
    QGroupBox *grB_Modo;
    QComboBox *cBx_Modo;
    QRadioButton *rdB_Guante_PC;
    QRadioButton *rdB_PC_Mano;
    QRadioButton *rdB_Guante_Mano;
    QGroupBox *grB_Sliders;
    QSlider *sld_Mayor;
    QSlider *sld_Anular;
    QSlider *sld_Menor;
    QSlider *sld_Pulgar;
    QSlider *sld_Indice;
    QLabel *lbl_Sliders;
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
    QLabel *lbl_Archivo;
    QPushButton *pushB_Guardar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Mano_Animatronica_Aplicacion)
    {
        if (Mano_Animatronica_Aplicacion->objectName().isEmpty())
            Mano_Animatronica_Aplicacion->setObjectName(QStringLiteral("Mano_Animatronica_Aplicacion"));
        Mano_Animatronica_Aplicacion->resize(690, 562);
        centralWidget = new QWidget(Mano_Animatronica_Aplicacion);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushB_Cargar = new QPushButton(centralWidget);
        pushB_Cargar->setObjectName(QStringLiteral("pushB_Cargar"));
        pushB_Cargar->setGeometry(QRect(10, 270, 131, 51));
        pushB_PlayPause = new QPushButton(centralWidget);
        pushB_PlayPause->setObjectName(QStringLiteral("pushB_PlayPause"));
        pushB_PlayPause->setGeometry(QRect(250, 80, 171, 91));
        grB_Modo = new QGroupBox(centralWidget);
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
        grB_Sliders = new QGroupBox(centralWidget);
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
        grB_Valores = new QGroupBox(centralWidget);
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
        grB_Mano = new QGroupBox(centralWidget);
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
        lbl_Archivo = new QLabel(centralWidget);
        lbl_Archivo->setObjectName(QStringLiteral("lbl_Archivo"));
        lbl_Archivo->setGeometry(QRect(440, 20, 191, 31));
        pushB_Guardar = new QPushButton(centralWidget);
        pushB_Guardar->setObjectName(QStringLiteral("pushB_Guardar"));
        pushB_Guardar->setGeometry(QRect(10, 360, 131, 51));
        Mano_Animatronica_Aplicacion->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Mano_Animatronica_Aplicacion);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Mano_Animatronica_Aplicacion->setStatusBar(statusBar);

        retranslateUi(Mano_Animatronica_Aplicacion);

        QMetaObject::connectSlotsByName(Mano_Animatronica_Aplicacion);
    } // setupUi

    void retranslateUi(QMainWindow *Mano_Animatronica_Aplicacion)
    {
        Mano_Animatronica_Aplicacion->setWindowTitle(QApplication::translate("Mano_Animatronica_Aplicacion", "Mano_Animatronica_Aplicacion", nullptr));
        pushB_Cargar->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "Cargar \n"
" Movimientos", nullptr));
        pushB_PlayPause->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "Play / Pause", nullptr));
        grB_Modo->setTitle(QApplication::translate("Mano_Animatronica_Aplicacion", "Modo de Operaci\303\263n", nullptr));
        cBx_Modo->setItemText(0, QApplication::translate("Mano_Animatronica_Aplicacion", "Seleccione Modo", nullptr));
        cBx_Modo->setItemText(1, QApplication::translate("Mano_Animatronica_Aplicacion", "Guante -> PC", nullptr));
        cBx_Modo->setItemText(2, QApplication::translate("Mano_Animatronica_Aplicacion", "PC -> Mano", nullptr));
        cBx_Modo->setItemText(3, QApplication::translate("Mano_Animatronica_Aplicacion", "Guante -> Mano", nullptr));

        rdB_Guante_PC->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "Guante -> PC", nullptr));
        rdB_PC_Mano->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "PC -> Mano", nullptr));
        rdB_Guante_Mano->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "Guante -> Mano", nullptr));
        grB_Sliders->setTitle(QApplication::translate("Mano_Animatronica_Aplicacion", "Sliders", nullptr));
        lbl_Sliders->setText(QApplication::translate("Mano_Animatronica_Aplicacion", " Menor     Anular     Mayor      Incide      Pulgar", nullptr));
        grB_Valores->setTitle(QApplication::translate("Mano_Animatronica_Aplicacion", "Valores actuales", nullptr));
        lbl_VMenor->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "Menor: 9999", nullptr));
        lbl_VAnular->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "Anular: 9999", nullptr));
        lbl_VMayor->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "Mayor: 9999", nullptr));
        lbl_VIndice->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "Indice: 9999", nullptr));
        lbl_VPulgar->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "Pulgar: 9999", nullptr));
        grB_Mano->setTitle(QApplication::translate("Mano_Animatronica_Aplicacion", "Mano", nullptr));
        lbl_1_Base_Img->setText(QString());
        lbl_2_Menor_Img->setText(QString());
        lbl_3_Anular_Img->setText(QString());
        lbl_4_Mayor_Img->setText(QString());
        lbl_5_Indice_Img->setText(QString());
        lbl_6_Pulgar_Img->setText(QString());
        lbl_Archivo->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "Nombre_archivo.hnd", nullptr));
        pushB_Guardar->setText(QApplication::translate("Mano_Animatronica_Aplicacion", "Guardar \n"
" Movimientos", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Mano_Animatronica_Aplicacion: public Ui_Mano_Animatronica_Aplicacion {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANO_ANIMATRONICA_APLICACION_H
