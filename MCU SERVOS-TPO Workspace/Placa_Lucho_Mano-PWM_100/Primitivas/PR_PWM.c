/*******************************************************************************************************************************//**
 *
 * @file		PR_PWM.c
 * @brief		Descripcion del modulo
 * @date		28 de oct. de 2018
 * @author		Saldivia, Luciano
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/

#include "../inc/PR_PWM.h"
//#include "../inc/PR_SysTick.h"

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

#define ESPERANDO_PROXIMO_FRENADO	0
#define FRENANDO					1

#define CUENTAS_MINIMAS_TH      	1000
#define MAXIMO_LECTURAS				1000

// Para Stop_Suave
#define TICKS_POR_PERIODO			4	// NO CAMBIAR
#define PERIODOS_POR_VALOR			4	// Se puede cambiar
#define CANT_VALORES_STOP_SUAVE		8	// Se puede cambiar, si se cambia la tabla!

/*

TIEMPO_FRENO_SUAVE ---> " TFS "
TFS = Tiempo de cada Período ( 20ms ) * Períodos por valor * Cantidad de valores

*/

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

volatile static float Tabla_Stop_Suave_Exponencial[ CANT_VALORES_STOP_SUAVE ] = {
                              1
                            , 0.606531
                            , 0.367879
                            , 0.223130
                            , 0.135335
                            , 0.082085
                            , 0.049787
                            , 0.030197 };

volatile static float Tabla_Stop_Suave_Lineal[ CANT_VALORES_STOP_SUAVE ] = {
                              1
                            , 0.875
                            , 0.75
                            , 0.625
                            , 0.5
                            , 0.375
                            , 0.25
                            , 0.125 };

volatile static float Tabla_Stop_Suave_Eliptico[ CANT_VALORES_STOP_SUAVE ] = {
                              1
                            , 0.976281
                            , 0.901387
                            , 0.760345
                            , 0.5
                            , 0.239654
                            , 0.098612
                            , 0.023718 };

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/

volatile uint8_t f_Stop_Suave = 0;

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

volatile uint8_t Nuevo_Stop_Suave = 0;

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/

/*  FUNCIONES PARA TPO_INFO_2    */

void PWM_Set_Lecturas( Lecturas_Mano_1000 *Lecturas ){

	// Protección para los motores. Por si llegan valores mayores que 1000 ( no deberían llegar )

	if( Lecturas->Menor > MAXIMO_LECTURAS ){
		Lecturas->Menor = MAXIMO_LECTURAS;
	}

	if( Lecturas->Anular > MAXIMO_LECTURAS ){
		Lecturas->Anular = MAXIMO_LECTURAS;
	}

	if( Lecturas->Mayor > MAXIMO_LECTURAS ){
		Lecturas->Mayor = MAXIMO_LECTURAS;
	}

	if( Lecturas->Indice > MAXIMO_LECTURAS ){
		Lecturas->Indice = MAXIMO_LECTURAS;
	}

	if( Lecturas->Pulgar > MAXIMO_LECTURAS ){
		Lecturas->Pulgar = MAXIMO_LECTURAS;
	}



    // Cargo los nuevos TH
    Buffer_TH[ CANAL_1 ] = Lecturas->Menor + CUENTAS_MINIMAS_TH;
    Buffer_TH[ CANAL_2 ] = Lecturas->Anular + CUENTAS_MINIMAS_TH;
    Buffer_TH[ CANAL_3 ] = MAXIMO_LECTURAS - Lecturas->Pulgar + CUENTAS_MINIMAS_TH;
    Buffer_TH[ CANAL_4 ] = MAXIMO_LECTURAS - Lecturas->Mayor + CUENTAS_MINIMAS_TH;
    Buffer_TH[ CANAL_5 ] = MAXIMO_LECTURAS - Lecturas->Indice + CUENTAS_MINIMAS_TH;

    // Aviso que hay nuevos TH
    Buffer_NEW_TH[ CANAL_1 ] = 1;
    Buffer_NEW_TH[ CANAL_2 ] = 1;
    Buffer_NEW_TH[ CANAL_3 ] = 1;
    Buffer_NEW_TH[ CANAL_4 ] = 1;
    Buffer_NEW_TH[ CANAL_5 ] = 1;
}

//uint16_t Convertir( uint16_t Lectura_4096 ){
//    uint16_t Lectura_1000, Lectura_1024 = Lectura_4096 / 4;
//
//    if( Lectura_1024 > 1024 ){
//        Lectura_1024 = 1024;
//    }
//
//    if( Lectura_1024 < 501 ){
//        if( Lectura_1024 < 250 ){
//            if( Lectura_1024 < 125 ){
//                if( Lectura_1024 < 84 ){
//                    if( Lectura_1024 < 42 ){
//                        Lectura_1000 = Lectura_1024;         // 0 <= Lectura_1024 < 42
//                    }
//                    else{
//                        Lectura_1000 = Lectura_1024 - 1;     // 42 <= Lectura_1024 < 84
//                    }
//                }
//                else{
//                    Lectura_1000 = Lectura_1024 - 2;         // 84 <= Lectura_1024 < 125
//                }
//            }
//            else{
//                if( Lectura_1024 < 209 ){
//                    if( Lectura_1024 < 167 ){
//                        Lectura_1000 = Lectura_1024 - 3;     // 125 <= Lectura_1024 < 167
//                    }
//                    else{
//                        Lectura_1000 = Lectura_1024 - 4;     // 167 <= Lectura_1024 < 209
//                    }
//                }
//                else{
//                    Lectura_1000 = Lectura_1024 - 5;         // 209 <= Lectura_1024 < 250
//                }
//            }
//        }
//        else{
//            if( Lectura_1024 < 375 ){
//                if( Lectura_1024 < 333 ){
//                    if( Lectura_1024 < 292 ){
//                        Lectura_1000 = Lectura_1024 - 6;     // 250 <= Lectura_1024 < 292
//                    }
//                    else{
//                        Lectura_1000 = Lectura_1024 - 7;     // 292 <= Lectura_1024 < 333
//                    }
//                }
//                else{
//                    Lectura_1000 = Lectura_1024 - 8;         // 333 <= Lectura_1024 < 375
//                }
//            }
//
//            else{
//                if( Lectura_1024 < 459 ){
//                    if( Lectura_1024 < 417 ){
//                        Lectura_1000 = Lectura_1024 - 9;     // 375 <= Lectura_1024 < 417
//                    }
//                    else{
//                        Lectura_1000 = Lectura_1024 - 10;    // 417 <= Lectura_1024 < 459
//                    }
//                }
//                else{
//                    Lectura_1000 = Lectura_1024 - 11;        // 459 <= Lectura_1024 < 501
//                }
//            }
//        }
//    }
//    else{
//        if( Lectura_1024 < 751 ){
//            if( Lectura_1024 < 626 ){
//                if( Lectura_1024 < 548 ){
//                    if( Lectura_1024 < 542 ){
//                        Lectura_1000 = Lectura_1024 - 12;    // 501 <= Lectura_1024 < 542
//                    }
//                    else{
//                        Lectura_1000 = Lectura_1024 - 13;    // 542 <= Lectura_1024 < 548
//                    }
//                }
//                else{
//                    Lectura_1000 = Lectura_1024 - 14;        // 548 <= Lectura_1024 < 626
//                }
//            }
//            else{
//                if( Lectura_1024 < 709 ){
//                    if( Lectura_1024 < 667 ){
//                        Lectura_1000 = Lectura_1024 - 15;    // 626 <= Lectura_1024 < 667
//                    }
//                    else{
//                        Lectura_1000 = Lectura_1024 - 16;    // 667 <= Lectura_1024 < 709
//                    }
//                }
//                else{
//                    Lectura_1000 = Lectura_1024 - 17;        // 709 <= Lectura_1024 < 751
//                }
//            }
//        }
//        else{
//            if( Lectura_1024 < 917 ){
//                if( Lectura_1024 < 834 ){
//                    if( Lectura_1024 < 792 ){
//                        Lectura_1000 = Lectura_1024 - 18;    // 751 <= Lectura_1024 < 792
//                    }
//                    else{
//                        Lectura_1000 = Lectura_1024 - 19;    // 792 <= Lectura_1024 < 834
//                    }
//                }
//                else{
//                    if( Lectura_1024 < 876 ){
//                        Lectura_1000 = Lectura_1024 - 20;    // 834 <= Lectura_1024 < 876
//                    }
//                    else{
//                        Lectura_1000 = Lectura_1024 - 21;    // 876 <= Lectura_1024 < 917
//                    }
//                }
//            }
//            else{
//                if( Lectura_1024 < 1000 ){
//                    if( Lectura_1024 < 959 ){
//                        Lectura_1000 = Lectura_1024 - 22;    // 917 <= Lectura_1024 < 959
//                    }
//                    else{
//                        Lectura_1000 = Lectura_1024 - 23;    // 959 <= Lectura_1024 < 1000
//                    }
//                }
//                else{
//                    Lectura_1000 = Lectura_1024 - 24;        // 1000 <= Lectura_1024 < 1024
//                }
//            }
//        }
//    }
//
//    return Lectura_1000;
//}

void PWM_Get_Lecturas( Lecturas_Mano_1000 *Lecturas ){
	Lecturas->Menor  = ( Buffer_TH[ CANAL_1 ] - CUENTAS_MINIMAS_TH );
	Lecturas->Anular = ( Buffer_TH[ CANAL_2 ] - CUENTAS_MINIMAS_TH );
	Lecturas->Pulgar = MAXIMO_LECTURAS - ( Buffer_TH[ CANAL_3 ] - CUENTAS_MINIMAS_TH );
	Lecturas->Mayor  = MAXIMO_LECTURAS - ( Buffer_TH[ CANAL_4 ] - CUENTAS_MINIMAS_TH );
	Lecturas->Indice = MAXIMO_LECTURAS - ( Buffer_TH[ CANAL_5 ] - CUENTAS_MINIMAS_TH );
}

void PWM_Enable_5_Channels( void ){

    // Start   ==> OUTPUT ENABLE = 1

    Buffer_NEW_ENABLE[ CANAL_1 ] = 1;
    Buffer_NEW_ENABLE[ CANAL_2 ] = 1;
    Buffer_NEW_ENABLE[ CANAL_3 ] = 1;
    Buffer_NEW_ENABLE[ CANAL_4 ] = 1;
    Buffer_NEW_ENABLE[ CANAL_5 ] = 1;
}

void PWM_Disable_5_Channels( void ){

    // Stop    ==> OUTPUT DISABLE = 1

    Buffer_NEW_DISABLE[ CANAL_1 ] = 1;
    Buffer_NEW_DISABLE[ CANAL_2 ] = 1;
    Buffer_NEW_DISABLE[ CANAL_3 ] = 1;
    Buffer_NEW_DISABLE[ CANAL_4 ] = 1;
    Buffer_NEW_DISABLE[ CANAL_5 ] = 1;

}

// CHIAMA: Como no uso este systick, para ponerlo tengo que levantar un flag y desde el systick llamar a estas funciones.
// // // // // // // // // // // //
//void PWM_Stop_Suave_5_Channels( uint8_t Modo ){
//	static uint8_t Already_Set_Exponencial = 0;
//	static uint8_t Already_Set_Lineal = 0;
//	static uint8_t Already_Set_Eliptico = 0;
//
//	switch( Modo ){
//	case SUAVIZAR_MODO_EXPONENCIAL:
//		Nuevo_Stop_Suave = SUAVIZAR_MODO_EXPONENCIAL;
//		if( Already_Set_Exponencial == 0 ){
//			setTickCallback( Tick_Call_Back_Stop_Suave_Exponencial );
//			Already_Set_Exponencial = 1;
//		}
//		break;
//
//	case SUAVIZAR_MODO_LINEAL:
//		Nuevo_Stop_Suave = SUAVIZAR_MODO_LINEAL;
//		if( Already_Set_Lineal == 0 ){
//			setTickCallback( Tick_Call_Back_Stop_Suave_Lineal );
//			Already_Set_Lineal = 1;
//		}
//		break;
//
//	case SUAVIZAR_MODO_ELIPTICO:
//		Nuevo_Stop_Suave = SUAVIZAR_MODO_ELIPTICO;
//		if( Already_Set_Eliptico == 0 ){
//			setTickCallback( Tick_Call_Back_Stop_Suave_Eliptico );
//			Already_Set_Eliptico = 1;
//		}
//		break;
//		break;
//	}
//}
//
//void Tick_Call_Back_Stop_Suave_Exponencial( void ){	// Cada 2,5ms
//	static uint8_t Contador, Indice_Tabla;
//	static Lecturas_Mano_4096 Lecturas_Iniciales, Lecturas_Siguientes;
//	static uint8_t Estado_Call_Back = ESPERANDO_PROXIMO_FRENADO;
//
//	switch( Estado_Call_Back ){
//		case ESPERANDO_PROXIMO_FRENADO:
//			if( Nuevo_Stop_Suave == SUAVIZAR_MODO_EXPONENCIAL ){
//				Nuevo_Stop_Suave = 0;		// Ya no es nuevo
//
//				Contador = 0;				// Inicializo el contador y el Indice
//				Indice_Tabla = 0;
//				PWM_Get_Lecturas( &Lecturas_Iniciales );	// Cargo las lecturas
//											// desde las cuales empiezo a frenar
//				Estado_Call_Back = FRENANDO;
//			}
//			break;
//
//		case FRENANDO:
//			if( Contador % ( TICKS_POR_PERIODO * PERIODOS_POR_VALOR ) == 0 ){	// Cada PERIODOS_POR_VALOR entro acá
//				if( Indice_Tabla < CANT_VALORES_STOP_SUAVE ){
//					Lecturas_Siguientes.Pulgar = Lecturas_Iniciales.Pulgar * Tabla_Stop_Suave_Exponencial[ Indice_Tabla ];
//					Lecturas_Siguientes.Indice = Lecturas_Iniciales.Indice * Tabla_Stop_Suave_Exponencial[ Indice_Tabla ];
//					Lecturas_Siguientes.Mayor  = Lecturas_Iniciales.Mayor  * Tabla_Stop_Suave_Exponencial[ Indice_Tabla ];
//					Lecturas_Siguientes.Anular = Lecturas_Iniciales.Anular * Tabla_Stop_Suave_Exponencial[ Indice_Tabla ];
//					Lecturas_Siguientes.Menor  = Lecturas_Iniciales.Menor  * Tabla_Stop_Suave_Exponencial[ Indice_Tabla ];
//
//					PWM_Set_Lecturas( &Lecturas_Siguientes );
//					Indice_Tabla ++;
//				}
//				else if( Indice_Tabla == CANT_VALORES_STOP_SUAVE ){
//					Lecturas_Siguientes.Pulgar = 0;
//					Lecturas_Siguientes.Indice = 0;
//					Lecturas_Siguientes.Mayor  = 0;
//					Lecturas_Siguientes.Anular = 0;
//					Lecturas_Siguientes.Menor  = 0;
//
//					PWM_Set_Lecturas( &Lecturas_Siguientes );
//					Indice_Tabla ++;
//				}
//				else if( Indice_Tabla > CANT_VALORES_STOP_SUAVE ){
//					PWM_Disable_5_Channels();
//					Estado_Call_Back = ESPERANDO_PROXIMO_FRENADO;
//				}
//			}
//			Contador ++;
//			break;
//	}
//}
//
//void Tick_Call_Back_Stop_Suave_Lineal( void ){		// Cada 2,5ms
//	static uint8_t Contador, Indice_Tabla;
//	static Lecturas_Mano_4096 Lecturas_Iniciales, Lecturas_Siguientes;
//	static uint8_t Estado_Call_Back = ESPERANDO_PROXIMO_FRENADO;
//
//	switch( Estado_Call_Back ){
//		case ESPERANDO_PROXIMO_FRENADO:
//			if( Nuevo_Stop_Suave == SUAVIZAR_MODO_LINEAL ){
//				Nuevo_Stop_Suave = 0;		// Ya no es nuevo
//
//				Contador = 0;				// Inicializo el contador y el Indice
//				Indice_Tabla = 0;
//				PWM_Get_Lecturas( &Lecturas_Iniciales );	// Cargo las lecturas
//											// desde las cuales empiezo a frenar
//				Estado_Call_Back = FRENANDO;
//			}
//			break;
//
//		case FRENANDO:
//			if( Contador % ( TICKS_POR_PERIODO * PERIODOS_POR_VALOR ) == 0 ){	// Cada PERIODOS_POR_VALOR entro acá
//				if( Indice_Tabla < CANT_VALORES_STOP_SUAVE ){
//					Lecturas_Siguientes.Pulgar = Lecturas_Iniciales.Pulgar * Tabla_Stop_Suave_Lineal[ Indice_Tabla ];
//					Lecturas_Siguientes.Indice = Lecturas_Iniciales.Indice * Tabla_Stop_Suave_Lineal[ Indice_Tabla ];
//					Lecturas_Siguientes.Mayor  = Lecturas_Iniciales.Mayor  * Tabla_Stop_Suave_Lineal[ Indice_Tabla ];
//					Lecturas_Siguientes.Anular = Lecturas_Iniciales.Anular * Tabla_Stop_Suave_Lineal[ Indice_Tabla ];
//					Lecturas_Siguientes.Menor  = Lecturas_Iniciales.Menor  * Tabla_Stop_Suave_Lineal[ Indice_Tabla ];
//
//					PWM_Set_Lecturas( &Lecturas_Siguientes );
//					Indice_Tabla ++;
//				}
//				else if( Indice_Tabla == CANT_VALORES_STOP_SUAVE ){
//					Lecturas_Siguientes.Pulgar = 0;
//					Lecturas_Siguientes.Indice = 0;
//					Lecturas_Siguientes.Mayor  = 0;
//					Lecturas_Siguientes.Anular = 0;
//					Lecturas_Siguientes.Menor  = 0;
//
//					PWM_Set_Lecturas( &Lecturas_Siguientes );
//					Indice_Tabla ++;
//				}
//				else if( Indice_Tabla > CANT_VALORES_STOP_SUAVE ){
//					PWM_Disable_5_Channels();
//					Estado_Call_Back = ESPERANDO_PROXIMO_FRENADO;
//				}
//			}
//			Contador ++;
//			break;
//	}
//}
//
//void Tick_Call_Back_Stop_Suave_Eliptico( void ){	// Cada 2,5ms
//	static uint8_t Contador, Indice_Tabla;
//	static Lecturas_Mano_4096 Lecturas_Iniciales, Lecturas_Siguientes;
//	static uint8_t Estado_Call_Back = ESPERANDO_PROXIMO_FRENADO;
//
//	switch( Estado_Call_Back ){
//		case ESPERANDO_PROXIMO_FRENADO:
//			if( Nuevo_Stop_Suave == SUAVIZAR_MODO_ELIPTICO ){
//				Nuevo_Stop_Suave = 0;		// Ya no es nuevo
//
//				Contador = 0;				// Inicializo el contador y el Indice
//				Indice_Tabla = 0;
//				PWM_Get_Lecturas( &Lecturas_Iniciales );	// Cargo las lecturas
//											// desde las cuales empiezo a frenar
//				Estado_Call_Back = FRENANDO;
//			}
//			break;
//
//		case FRENANDO:
//			if( Contador % ( TICKS_POR_PERIODO * PERIODOS_POR_VALOR ) == 0 ){	// Cada PERIODOS_POR_VALOR entro acá
//				if( Indice_Tabla < CANT_VALORES_STOP_SUAVE ){
//					Lecturas_Siguientes.Pulgar = Lecturas_Iniciales.Pulgar * Tabla_Stop_Suave_Eliptico[ Indice_Tabla ];
//					Lecturas_Siguientes.Indice = Lecturas_Iniciales.Indice * Tabla_Stop_Suave_Eliptico[ Indice_Tabla ];
//					Lecturas_Siguientes.Mayor  = Lecturas_Iniciales.Mayor  * Tabla_Stop_Suave_Eliptico[ Indice_Tabla ];
//					Lecturas_Siguientes.Anular = Lecturas_Iniciales.Anular * Tabla_Stop_Suave_Eliptico[ Indice_Tabla ];
//					Lecturas_Siguientes.Menor  = Lecturas_Iniciales.Menor  * Tabla_Stop_Suave_Eliptico[ Indice_Tabla ];
//
//					PWM_Set_Lecturas( &Lecturas_Siguientes );
//					Indice_Tabla ++;
//				}
//				else if( Indice_Tabla == CANT_VALORES_STOP_SUAVE ){
//					Lecturas_Siguientes.Pulgar = 0;
//					Lecturas_Siguientes.Indice = 0;
//					Lecturas_Siguientes.Mayor  = 0;
//					Lecturas_Siguientes.Anular = 0;
//					Lecturas_Siguientes.Menor  = 0;
//
//					PWM_Set_Lecturas( &Lecturas_Siguientes );
//					Indice_Tabla ++;
//				}
//				else if( Indice_Tabla > CANT_VALORES_STOP_SUAVE ){
//					PWM_Disable_5_Channels();
//					Estado_Call_Back = ESPERANDO_PROXIMO_FRENADO;
//				}
//			}
//			Contador ++;
//			break;
//	}
//}


////  Funciones para el CANAL PWM1_1
//
//void PWM_1_Set( uint32_t Valor_Lectura_4096 ){
//
//    // Set     ==>  Cargo el nuevo TH en Buffer_TH
//    //              Aviso que hay nuevo TH por Buffer_NEW_TH
//
//    Buffer_TH[ CANAL_1 ] = Convertir( Valor_Lectura_4096 ) + CUENTAS_MINIMAS_TH;   // Cargo el nuevo TH
//    Buffer_NEW_TH[ CANAL_1 ] = 1;           // Aviso que hay un nuevo TH
//}
//
//uint32_t PWM_1_Get( void ){
//    return ( ( Buffer_TH[ CANAL_1 ] - CUENTAS_MINIMAS_TH ) * 4 );
//}
//
//void PWM_1_Start( void ){
//
//    // Start   ==> OUTPUT ENABLE = 1
//
//    Buffer_NEW_ENABLE[ CANAL_1 ] = 1;       // Enable PWM1_1 Output
//}
//
//void PWM_1_Stop( void ){
//
//    // Stop    ==> ENABLE = 0
//
//    Buffer_NEW_DISABLE[ CANAL_1 ] = 1;      // Disable PWM1_1 Output
//}
//
//
//
////  Funciones para el CANAL PWM1_2
//
//void PWM_2_Set( uint32_t Valor_Lectura_4096 ){
//
//    // Set     ==>  Cargo el nuevo TH en Buffer_TH
//    //              Aviso que hay nuevo TH por Buffer_NEW_TH
//
//    Buffer_TH[ CANAL_2 ] = Convertir( Valor_Lectura_4096 ) + CUENTAS_MINIMAS_TH; // Cargo el nuevo TH
//    Buffer_NEW_TH[ CANAL_2 ] = 1;           // Aviso que hay un nuevo TH
//}
//
//uint32_t PWM_2_Get( void ){
//    return ( ( Buffer_TH[ CANAL_2 ] - CUENTAS_MINIMAS_TH ) * 4 );
//}
//
//void PWM_2_Start( void ){
//
//    // Start   ==> OUTPUT ENABLE = 1
//
//    Buffer_NEW_ENABLE[ CANAL_2 ] = 1;       // Enable PWM1_2 Output
//}
//
//void PWM_2_Stop( void ){
//
//    // Stop    ==> ENABLE = 0
//
//    Buffer_NEW_DISABLE[ CANAL_2 ] = 1;      // Disable PWM1_2 Output
//}
//
//
//
////  Funciones para el CANAL PWM1_3
//
//void PWM_3_Set( uint32_t Valor_Lectura_4096 ){
//
//    // Set     ==>  Cargo el nuevo TH en Buffer_TH
//    //              Aviso que hay nuevo TH por Buffer_NEW_TH
//
//    Buffer_TH[ CANAL_3 ] = Convertir( Valor_Lectura_4096 ) + CUENTAS_MINIMAS_TH;   // Cargo el nuevo TH
//    Buffer_NEW_TH[ CANAL_3 ] = 1;           // Aviso que hay un nuevo TH
//}
//
//uint32_t PWM_3_Get( void ){
//    return ( ( Buffer_TH[ CANAL_3 ] - CUENTAS_MINIMAS_TH ) * 4 );
//}
//
//void PWM_3_Start( void ){
//
//    // Start   ==> OUTPUT ENABLE = 1
//
//    Buffer_NEW_ENABLE[ CANAL_3 ] = 1;       // Enable PWM1_3 Output
//}
//
//void PWM_3_Stop( void ){
//
//    // Stop    ==> ENABLE = 0
//
//    Buffer_NEW_DISABLE[ CANAL_3 ] = 1;      // Disable PWM1_3 Output
//}
//
//
//
////  Funciones para el CANAL PWM1_4
//
//void PWM_4_Set( uint32_t Valor_Lectura_4096 ){
//
//    // Set     ==>  Cargo el nuevo TH en Buffer_TH
//    //              Aviso que hay nuevo TH por Buffer_NEW_TH
//
//    Buffer_TH[ CANAL_4 ] = Convertir( Valor_Lectura_4096 ) + CUENTAS_MINIMAS_TH;   // Cargo el nuevo TH
//    Buffer_NEW_TH[ CANAL_4 ] = 1;           // Aviso que hay un nuevo TH
//}
//
//uint32_t PWM_4_Get( void ){
//    return ( ( Buffer_TH[ CANAL_4 ] - CUENTAS_MINIMAS_TH ) * 4 );
//}
//
//void PWM_4_Start( void ){
//
//    // Start   ==> OUTPUT ENABLE = 1
//
//    Buffer_NEW_ENABLE[ CANAL_4 ] = 1;       // Enable PWM1_4 Output
//}
//
//void PWM_4_Stop( void ){
//
//    // Stop    ==> ENABLE = 0
//
//    Buffer_NEW_DISABLE[ CANAL_4 ] = 1;      // Disable PWM1_4 Output
//}
//
//
//
////  Funciones para el CANAL PWM1_5
//
//void PWM_5_Set( uint32_t Valor_Lectura_4096 ){
//
//    // Set     ==>  Cargo el nuevo TH en Buffer_TH
//    //              Aviso que hay nuevo TH por Buffer_NEW_TH
//
//    Buffer_TH[ CANAL_5 ] = Convertir( Valor_Lectura_4096 ) + CUENTAS_MINIMAS_TH;   // Cargo el nuevo TH
//    Buffer_NEW_TH[ CANAL_5 ] = 1;           // Aviso que hay un nuevo TH
//}
//
//uint32_t PWM_5_Get( void ){
//    return ( ( Buffer_TH[ CANAL_5 ] - CUENTAS_MINIMAS_TH ) * 4 );
//}
//
//void PWM_5_Start( void ){
//
//    // Start   ==> OUTPUT ENABLE = 1
//
//    Buffer_NEW_ENABLE[ CANAL_5 ] = 1;       // Enable PWM1_5 Output
//}
//
//void PWM_5_Stop( void ){
//
//    // Stop    ==> ENABLE = 0
//
//    Buffer_NEW_DISABLE[ CANAL_5 ] = 1;      // Disable PWM1_5 Output
//}
//
//
//
///*  ABAJO, TODAS LAS NO USADAS PARA EL TPO_INFO_2   */
//
//void PWM_Start_All_Channels( void ){
//
//    // Start   ==> OUTPUT ENABLE = 1
//
//    Buffer_NEW_ENABLE[ CANAL_1 ] = 1;
//    Buffer_NEW_ENABLE[ CANAL_2 ] = 1;
//    Buffer_NEW_ENABLE[ CANAL_3 ] = 1;
//    Buffer_NEW_ENABLE[ CANAL_4 ] = 1;
//    Buffer_NEW_ENABLE[ CANAL_5 ] = 1;
//    Buffer_NEW_ENABLE[ CANAL_6 ] = 1;
//}
//
//void PWM_Stop_All_Channels( void ){
//
//    // Stop    ==> ENABLE = 0
//
//    Buffer_NEW_ENABLE[ CANAL_1 ] = 0;
//    Buffer_NEW_ENABLE[ CANAL_2 ] = 0;
//    Buffer_NEW_ENABLE[ CANAL_3 ] = 0;
//    Buffer_NEW_ENABLE[ CANAL_4 ] = 0;
//    Buffer_NEW_ENABLE[ CANAL_5 ] = 0;
//    Buffer_NEW_ENABLE[ CANAL_6 ] = 0;
//
//}
//
////  Funciones para el CANAL PWM1_6
//
//void PWM_6_Set( uint32_t Valor_Lectura_4096 ){
//
//    // Set     ==>  Cargo el nuevo TH en Buffer_TH
//    //              Aviso que hay nuevo TH por Buffer_NEW_TH
//
//    Buffer_TH[ CANAL_6 ] = Convertir( Valor_Lectura_4096 ) + CUENTAS_MINIMAS_TH;   // Cargo el nuevo TH
//    Buffer_NEW_TH[ CANAL_6 ] = 1;           // Aviso que hay un nuevo TH
//}
//
//uint32_t PWM_6_Get( void ){
//    return ( ( Buffer_TH[ CANAL_6 ] - CUENTAS_MINIMAS_TH ) * 4 );
//}
//
//void PWM_6_Start( void ){
//
//    // Start   ==> OUTPUT ENABLE = 1
//
//    Buffer_NEW_ENABLE[ CANAL_6 ] = 1;       // Enable PWM1_6 Output
//}
//
//void PWM_6_Stop( void ){
//
//    // Stop    ==> ENABLE = 0
//
//    Buffer_NEW_DISABLE[ CANAL_6 ] = 1;      // Disable PWM1_6 Output
//}
