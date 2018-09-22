#ifndef MANO_ANIMATRONICA_APLICACION_H
#define MANO_ANIMATRONICA_APLICACION_H

#include <QMainWindow>
#include <QSlider>

/*  Modos   */
#define NINGUN_MODO 0
#define GUANTE_PC 1
#define PC_MANO 2
#define GUANTE_MANO 3

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

    void setModo( int Mode );

private slots:
    void on_cBx_Modo_activated(int index);

    void on_rdB_Guante_PC_clicked();

    void on_rdB_PC_Mano_clicked();

    void on_rdB_Guante_Mano_clicked();

    void on_sld_Menor_valueChanged(int value);

    void on_sld_Anular_valueChanged(int value);

    void on_sld_Mayor_valueChanged(int value);

    void on_sld_Indice_valueChanged(int value);

    void on_sld_Pulgar_valueChanged(int value);

    void on_pushB_Prueba_Guante_clicked();

private:
    Ui::Mano_Animatronica_Aplicacion *ui;
    int Modo;
};

void ActualizarImagenMano( Ui::Mano_Animatronica_Aplicacion * ui, int Menor, int Anular, int Mayor, int Indice, int Pulgar );
void ActualizarImagenMano( Ui::Mano_Animatronica_Aplicacion * ui, QSlider *Menor, QSlider *Anular, QSlider *Mayor, QSlider *Indice, QSlider *Pulgar );

#endif // MANO_ANIMATRONICA_APLICACION_H
