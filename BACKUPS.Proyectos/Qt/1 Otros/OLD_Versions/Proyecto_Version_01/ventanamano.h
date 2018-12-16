#ifndef VENTANAMANO_H
#define VENTANAMANO_H

#include <QMainWindow>
#include <QSlider>

enum MisDedos{ MENOR, ANULAR, MAYOR, INDICE, PULGAR };

namespace Ui {
class VentanaMano;
}

class VentanaMano : public QMainWindow
{
    Q_OBJECT

public:
    explicit VentanaMano(QWidget *parent = 0);
    ~VentanaMano();
    void Actualizar( QSlider *Menor, QSlider *Anular, QSlider *Mayor, QSlider *Indice, QSlider *Pulgar );


private:
    int Label_Ancho;
    int Label_Alto;
    Ui::VentanaMano *ui;
    QSlider  *Menor, *Anular, *Mayor, *Indice, *Pulgar;
};

#endif // VENTANAMANO_H
