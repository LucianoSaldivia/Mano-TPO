#include "mano_animatronica_aplicacion.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Mano_Animatronica_Aplicacion w;
    w.show();

    return a.exec();
}
