/*
 * AP_PruebaUART.c
 *
 *  Created on: 25 sep. 2018
 *      Author: lsldv
 */

#include <bibliotecaInfoII.h>
#include "AP_PruebaUART.h"
#include <string.h>

#define HEADER		0
#define COMANDO		1
#define FIN			2

uint8_t Trama[100];
uint8_t Estado;

void MDE_UART ( void )
{
	int16_t dato;
	/*static char mensaje[20] = "553221";*/
		//mensaje[ strlen(mensaje) ] = '\0';
	static uint8_t /*Estado,*/ comando;
	/**/
	static char buff[7];
	static char aux[5] = {'4','4','4','4'};
	char *p;
	/**/
	char enter[10] ;

	enter[0] = '\xd';
	enter[1] = '\0';

	dato = UART0_PopRX();

	if ( dato != -1 ){
		switch ( Estado ){
			case HEADER:
				if ( dato == '#' )
					Estado = COMANDO;
				break;

			case COMANDO:
				if ( dato == 'T' || dato == 'S' || dato == 'P' || dato == 'E'  ){
					comando = dato;
					Estado = FIN;
					break;
				}
				break;

			case FIN:
				if ( dato == '$' ){
					switch( comando ){
						case 'T':
							Strcpy(Mensaje0, "T:");
							Itoa( Mensaje1 ,Temperatura( ) );
							Strformat(Mensaje1 , '0' , 4 );
							Strcat(Mensaje0,Mensaje1);
							Strcat(Mensaje0,enter);
							Transmitir( UART0 , Mensaje0 , strlen(Mensaje0));
							break;

						case 'P':
							Strcpy(Mensaje0, "P:");
							Itoa( Mensaje1 ,Potenciometro( ) );
							Strformat(Mensaje1 , '0' , 4 );
							Strcat(Mensaje0,Mensaje1);
							Strcat(Mensaje0,enter);
							Transmitir( UART0 , Mensaje0 , strlen(Mensaje0));
							break;

						case 'E':
							Strcpy(Mensaje0, "E:");
							Itoa( Mensaje1 ,ADC_Externa( ) );
							Strformat(Mensaje1 , '0' , 4 );
							Strcat(Mensaje0,Mensaje1);
							Strcat(Mensaje0,enter);
							Transmitir( UART0 , Mensaje0 , strlen(Mensaje0));
							break;

						case 'S':

							/**/
							buff[0] = '/';
							buff[1] = '\0';
							Strcat(buff, aux);
							p = strchr(buff, '\0');
							*p = '/';
							*(p+1) = '\0';
							/**/

							Transmitir( UART0, buff, strlen(buff) );
							LCD_Display( "Rx = #S$        ", DSP0, 0 );
							LCD_Display( buff , DSP1, 0 );

							break;
					}
				}
				Estado = HEADER;
				break;

			default:
				Estado = HEADER;
				break;
		}
	}
}
