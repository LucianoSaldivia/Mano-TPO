/*
 * mensaje.c
 *
 *  Created on: 29 may. 2018
 *      Author: gabriel
 */


#include <bibliotecaInfoII.h>
#include "AP_Prueba1.h"

void MaquinaEstadosPrueba(void){
	static uint8_t Switch = 0;
	static uint8_t estado = 0;
	static char Numero[16] = "", Aux[16] = "", Fin = '\0';

	switch(estado){
		case ESPERANDO:
			Switch = GetKey();
			if( Switch != NO_KEY ){
				estado = NUEVA_TECLA;
			}
			break;

		case NUEVA_TECLA:
			switch( Switch ){
				case SW10:
					LCD_Display( "a               ", DSP1, 0);
					Strcpy( Numero, "Tecla: " );
					Itoa( Aux, 1 );
					Strcat( Numero, Aux );
					Strcat( Numero, &Fin );
					Strcat( Numero, "       " );
					LCD_Display( Numero, DSP0, 0 );
					break;
				case SW7:
					LCD_Display( "b               ", DSP1, 0);
					Strcpy( Numero, "Tecla: " );
					Itoa( Aux, 2 );
					Strcat( Numero, Aux );
					Strcat( Numero, &Fin );
					Strcat( Numero, "       " );
					LCD_Display( Numero, DSP0, 0 );
					break;
				case SW4:
					LCD_Display( "c               ", DSP1, 0);
					Strcpy( Numero, "Tecla: " );
					Itoa( Aux, 3 );
					Strcat( Numero, Aux );
					Strcat( Numero, &Fin );
					Strcat( Numero, "       " );
					LCD_Display( Numero, DSP0, 0 );
					break;
				case SW1:
					LCD_Display( "d               ", DSP1, 0);
					Strcpy( Numero, "Tecla: " );
					Itoa( Aux, 4 );
					Strcat( Numero, Aux );
					Strcat( Numero, &Fin );
					Strcat( Numero, "       " );
					LCD_Display( Numero, DSP0, 0 );
					break;
				default:
					break;
			}
			estado = ESPERANDO;
			break;

		default:
			estado = ESPERANDO;
	}
}
