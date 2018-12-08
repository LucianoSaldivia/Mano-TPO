/*******************************************************************************************************************************//**
 *
 * @file		DR_PWM.c
 * @brief		Descripcion del modulo
 * @date		28 de oct. de 2018
 * @author		Saldivia, Luciano
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/

#include "DR_PWM.h"

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

#define CUENTAS_POR_CICLO           20000
#define VALOR_PR                    24

#define VALOR_INICIAL_1             1500
#define VALOR_INICIAL_2             1500
#define VALOR_INICIAL_3             1500
#define VALOR_INICIAL_4             1500
#define VALOR_INICIAL_5             1500
#define VALOR_INICIAL_6             1500

#define BORRAR_PWM_MR0_IIR_FLAG     PWM1IR |= ( PWM_MR0_IIR_FLAG )
#define BORRAR_PWM_MR1_IIR_FLAG     PWM1IR |= ( PWM_MR1_IIR_FLAG )
#define BORRAR_PWM_MR2_IIR_FLAG     PWM1IR |= ( PWM_MR2_IIR_FLAG )
#define BORRAR_PWM_MR3_IIR_FLAG     PWM1IR |= ( PWM_MR3_IIR_FLAG )
#define BORRAR_PWM_MR4_IIR_FLAG     PWM1IR |= ( PWM_MR4_IIR_FLAG )
#define BORRAR_PWM_MR5_IIR_FLAG     PWM1IR |= ( PWM_MR5_IIR_FLAG )
#define BORRAR_PWM_MR6_IIR_FLAG     PWM1IR |= ( PWM_MR6_IIR_FLAG )

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE datoS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/

volatile uint32_t Buffer_TH[ CANT_CANALES ];
volatile uint8_t Buffer_NEW_TH[ CANT_CANALES ];
volatile uint8_t Buffer_NEW_ENABLE[ CANT_CANALES ];
volatile uint8_t Buffer_NEW_DISABLE[ CANT_CANALES ];

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

volatile static uint8_t _FLAGS_INTERRUPCIONES = 0;
volatile static uint8_t _PWM_1_ENABLED = 0;
volatile static uint8_t _PWM_2_ENABLED = 0;
volatile static uint8_t _PWM_3_ENABLED = 0;
volatile static uint8_t _PWM_4_ENABLED = 0;
volatile static uint8_t _PWM_5_ENABLED = 0;
volatile static uint8_t _PWM_6_ENABLED = 0;

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/

void PWM1_IRQHandler (void){
    uint32_t iir;

    do{
        iir = PWM1IR;

        if( iir & PWM_MR0_IIR_FLAG ){   // Interrupcion por MR0
            _FLAGS_INTERRUPCIONES = 0;
            BORRAR_PWM_MR0_IIR_FLAG;
        }
        if( iir & PWM_MR1_IIR_FLAG ){   // Interrupcion por MR1
            _FLAGS_INTERRUPCIONES ++;
            BORRAR_PWM_MR1_IIR_FLAG;

            if( Buffer_NEW_TH[ CANAL_1 ] == 1 ){
                PWM1MR1 = CUENTAS_POR_CICLO - Buffer_TH[ CANAL_1 ];     // Cargo el nuevo MR
                PWM1LER |= ( 0x01 << 1 );           // Aviso para que lo haga efectivo
            }
            if( Buffer_NEW_ENABLE[ CANAL_1 ] == 1 ){
                PWM1PCR |= ( 0x01 << 9 );           // Enable PWM1_1 Output
                Buffer_NEW_ENABLE[ CANAL_1 ] = 0;
            }
            if( Buffer_NEW_DISABLE[ CANAL_1 ] == 1 ){
                PWM1PCR &= ~( 0x01 << 9 );          // Disable PWM1_1 Output
                Buffer_NEW_DISABLE[ CANAL_1 ] = 0;
            }

        }
        if( iir & PWM_MR2_IIR_FLAG ){   // Interrupcion por MR2
            _FLAGS_INTERRUPCIONES ++;
            BORRAR_PWM_MR2_IIR_FLAG;

            if( Buffer_NEW_TH[ CANAL_2 ] == 1 ){
                PWM1MR2 = CUENTAS_POR_CICLO - Buffer_TH[ CANAL_2 ];     // Cargo el nuevo MR
                PWM1LER |= ( 0x01 << 2 );           // Aviso para que lo haga efectivo
            }
            if( Buffer_NEW_ENABLE[ CANAL_2 ] == 1 ){
                PWM1PCR |= ( 0x01 << 10 );          // Enable PWM1_2 Output
                Buffer_NEW_ENABLE[ CANAL_2 ] = 0;
            }
            if( Buffer_NEW_DISABLE[ CANAL_2 ] == 1 ){
                PWM1PCR &= ~( 0x01 << 10 );         // Disable PWM1_2 Output
                Buffer_NEW_DISABLE[ CANAL_2 ] = 0;
            }

        }
        if( iir & PWM_MR3_IIR_FLAG ){   // Interrupcion por MR3
            _FLAGS_INTERRUPCIONES ++;
            BORRAR_PWM_MR3_IIR_FLAG;

            if( Buffer_NEW_TH[ CANAL_3 ] == 1 ){
                PWM1MR3 = CUENTAS_POR_CICLO - Buffer_TH[ CANAL_3 ];     // Cargo el nuevo MR
                PWM1LER |= ( 0x01 << 3 );           // Aviso para que lo haga efectivo
            }
            if( Buffer_NEW_ENABLE[ CANAL_3 ] == 1 ){
                PWM1PCR |= ( 0x01 << 11 );          // Enable PWM1_3 Output
                Buffer_NEW_ENABLE[ CANAL_3 ] = 0;
            }
            if( Buffer_NEW_DISABLE[ CANAL_3 ] == 1 ){
                PWM1PCR &= ~( 0x01 << 11 );         // Disable PWM1_3 Output
                Buffer_NEW_DISABLE[ CANAL_3 ] = 0;
            }

        }
        if( iir & PWM_MR4_IIR_FLAG ){   // Interrupcion por MR4
            _FLAGS_INTERRUPCIONES ++;
            BORRAR_PWM_MR4_IIR_FLAG;

            if( Buffer_NEW_TH[ CANAL_4 ] == 1 ){
                PWM1MR4 = CUENTAS_POR_CICLO - Buffer_TH[ CANAL_4 ];     // Cargo el nuevo MR
                PWM1LER |= ( 0x01 << 4 );           // Aviso para que lo haga efectivo
            }
            if( Buffer_NEW_ENABLE[ CANAL_4 ] == 1 ){
                PWM1PCR |= ( 0x01 << 12 );          // Enable PWM1_4 Output
                Buffer_NEW_ENABLE[ CANAL_4 ] = 0;
            }
            if( Buffer_NEW_DISABLE[ CANAL_4 ] == 1 ){
                PWM1PCR &= ~( 0x01 << 12 );         // Disable PWM1_4 Output
                Buffer_NEW_DISABLE[ CANAL_4 ] = 0;
            }

        }
        if( iir & PWM_MR5_IIR_FLAG ){   // Interrupcion por MR5
            _FLAGS_INTERRUPCIONES ++;
            BORRAR_PWM_MR5_IIR_FLAG;

            if( Buffer_NEW_TH[ CANAL_5 ] == 1 ){
                PWM1MR5 = CUENTAS_POR_CICLO - Buffer_TH[ CANAL_5 ];     // Cargo el nuevo MR
                PWM1LER |= ( 0x01 << 5 );           // Aviso para que lo haga efectivo
            }
            if( Buffer_NEW_ENABLE[ CANAL_5 ] == 1 ){
                PWM1PCR |= ( 0x01 << 13 );          // Enable PWM1_5 Output
                Buffer_NEW_ENABLE[ CANAL_5 ] = 0;
            }
            if( Buffer_NEW_DISABLE[ CANAL_5 ] == 1 ){
                PWM1PCR &= ~( 0x01 << 13 );         // Disable PWM1_5 Output
                Buffer_NEW_DISABLE[ CANAL_5 ] = 0;
            }

        }
    } while( iir & PWM_MR0_IIR_FLAG ||
             iir & PWM_MR1_IIR_FLAG ||
             iir & PWM_MR2_IIR_FLAG ||
             iir & PWM_MR3_IIR_FLAG ||
             iir & PWM_MR4_IIR_FLAG ||
             iir & PWM_MR5_IIR_FLAG );   // Mientras que haya una interrupcion
}

/*  FUNCIONES PARA TPO_INFO_2    */

void PWM1_Init_5Canales( void ){

    PCONP |= ( 0x01 << 6 );         // Energizamos Perif. PWM

    PCLKSEL0 &= ~( 0x03 << 12 );    // PCLK = CCLK / 4 = 25 MHz

    SetPINSEL( P2, 0, PINSEL_FUNC1 );
    SetPINSEL( P2, 1, PINSEL_FUNC1 );
    SetPINSEL( P2, 2, PINSEL_FUNC1 );
    SetPINSEL( P2, 3, PINSEL_FUNC1 );
	SetPINSEL( P2, 4, PINSEL_FUNC1 );

	PWM1MCR |= ( 0x01 << 1 );       // Reset on PWM1MR0 match

	PWM1MCR |= ( 0x01 << 0 );       // Activo Interrupciones cuando TC = MR0
	PWM1MCR |= ( 0x01 << 3 );       // Activo Interrupciones cuando TC = MR1
	PWM1MCR |= ( 0x01 << 6 );       // Activo Interrupciones cuando TC = MR2
	PWM1MCR |= ( 0x01 << 9 );       // Activo Interrupciones cuando TC = MR3
	PWM1MCR |= ( 0x01 << 12 );      // Activo Interrupciones cuando TC = MR4
	PWM1MCR |= ( 0x01 << 15 );      // Activo Interrupciones cuando TC = MR5

    ISER0 |= ( 0x01 << 9 );         // Habilito las interrupciones desde el micro

	PWM1PCR &= ~( 0x01 << 2 );  	// Ponemos en modo Single EDGE
	PWM1PCR &= ~( 0x01 << 3 );  	// Ponemos en modo Single EDGE
	PWM1PCR &= ~( 0x01 << 4 );  	// Ponemos en modo Single EDGE
	PWM1PCR &= ~( 0x01 << 5 );  	// Ponemos en modo Single EDGE

	PWM1PR = VALOR_PR;              // Prescale
	// CCLK = 100 Mhz
	// PCLK = CCLK / 4 = 25 MHz
	//    con PR = 24
	// Count.Freq. = PCLK / ( PR + 1 ) = 1 MHz

    PWM1MR0 = CUENTAS_POR_CICLO;    // Set ciclo del PWM
	PWM1MR1 = VALOR_INICIAL_1;		// Valores Iniciales
	PWM1MR2 = VALOR_INICIAL_2;		// en los Match Register
	PWM1MR3 = VALOR_INICIAL_3;
	PWM1MR4 = VALOR_INICIAL_4;
	PWM1MR5 = VALOR_INICIAL_5;

    PWM1LER |= ( 0x01 << 0 );		// Los hago efectivos
	PWM1LER |= ( 0x01 << 1 );
	PWM1LER |= ( 0x01 << 2 );
	PWM1LER |= ( 0x01 << 3 );
	PWM1LER |= ( 0x01 << 4 );
	PWM1LER |= ( 0x01 << 5 );

    PWM1TCR |= ( 0x01 << 0 );     	// Counter Enable
	PWM1TCR &= ~( 0x01 << 1 );      // Counter Reset
	PWM1TCR |= ( 0x01 << 3 );      	// PWM Enable

	PWM1CTCR &= ~( 0x03 << 0 );     // Counter Mode

    /*PWM1PCR &= ~( 0x01 << 9 );      // Disable PWM1_1
    PWM1PCR &= ~( 0x01 << 10 );     // Disable PWM1_2
    PWM1PCR &= ~( 0x01 << 11 );     // Disable PWM1_3
    PWM1PCR &= ~( 0x01 << 12 );     // Disable PWM1_4
    PWM1PCR &= ~( 0x01 << 13 );     // Disable PWM1_5*/
}

/*  ABAJO, TODAS LAS NO USADAS PARA EL TPO_INFO_2   */

void PWM1_Actualizar_5Canales( void ){

    // Set     ==> Cambio MR_N y Activo LER
    // Cargo los nuevos MR
    PWM1MR1 = Buffer_TH[ DEDO_PULGAR ];
    PWM1MR2 = Buffer_TH[ DEDO_INDICE ];
    PWM1MR3 = Buffer_TH[ DEDO_MAYOR  ];
    PWM1MR4 = Buffer_TH[ DEDO_ANULAR ];
    PWM1MR5 = Buffer_TH[ DEDO_MENOR  ];

    // Aviso para que lo haga efectivos todos los nuevos MR
    PWM1LER |= ( 0x01 << 1 );
    PWM1LER |= ( 0x01 << 2 );
    PWM1LER |= ( 0x01 << 3 );
    PWM1LER |= ( 0x01 << 4 );
    PWM1LER |= ( 0x01 << 5 );

}

void PWM1_Config_Canal( uint8_t Canal, uint32_t Valor_Inicial ){

        switch ( Canal ) {  // SetPINSEL y los configuro como SINGLE EDGE

                case DEDO_PULGAR:
                case CANAL_1:
                        SetPINSEL( P2, 0, PINSEL_FUNC1 );
                        // No se configura, funciona igual para
                        // Single EDGE o Double EDGE
                        break;

                case DEDO_INDICE:
                case CANAL_2:
                        SetPINSEL( P2, 1, PINSEL_FUNC1 );
                        PWM1PCR &= ~( 0x01 << 2 );  // Ponemos en modo Single EDGE
                        break;

                case DEDO_MAYOR:
                case CANAL_3:
                        SetPINSEL( P2, 2, PINSEL_FUNC1 );
                        PWM1PCR &= ~( 0x01 << 3 );  // Ponemos en modo Single EDGE
                        break;

                case DEDO_ANULAR:
                case CANAL_4:
                        SetPINSEL( P2, 3, PINSEL_FUNC1 );
                        PWM1PCR &= ~( 0x01 << 4 );  // Ponemos en modo Single EDGE
                        break;

                case DEDO_MENOR:
                case CANAL_5:
                        SetPINSEL( P2, 4, PINSEL_FUNC1 );
                        PWM1PCR &= ~( 0x01 << 5 );  // Ponemos en modo Single EDGE
                        break;

                case CANAL_6:
                        SetPINSEL( P2, 5, PINSEL_FUNC1 );
                        PWM1PCR &= ~( 0x01 << 6 );  // Ponemos en modo Single EDGE
                        break;

                default:            // default = DEDO_PULGAR o CANAL_1
                        SetPINSEL( P2, 0, PINSEL_FUNC1 );
                        // Modo Single EDGE por default
                        break;
        }

        PWM1PR = VALOR_PR;                    // Prescale
            // CCLK = 100 Mhz
            // PCLK = CCLK / 4 = 25 MHz
            //    con PR = 24
            // Count.Freq. = PCLK / ( PR + 1 ) = 1 MHz

        switch ( Canal ) {  // Cargo Valor_Inicial y aviso para que se haga efectivo

                case DEDO_PULGAR:
                case CANAL_1:
                        PWM1MR1 = Valor_Inicial;
                        PWM1LER |= ( 0x01 << 1 );
                        break;

                case DEDO_INDICE:
                case CANAL_2:
                        PWM1MR2 = Valor_Inicial;
                        PWM1LER |= ( 0x01 << 2 );
                        break;

                case DEDO_MAYOR:
                case CANAL_3:
                        PWM1MR3 = Valor_Inicial;
                        PWM1LER |= ( 0x01 << 3 );
                        break;

                case DEDO_ANULAR:
                case CANAL_4:
                        PWM1MR4 = Valor_Inicial;
                        PWM1LER |= ( 0x01 << 4 );
                        break;

                case DEDO_MENOR:
                case CANAL_5:
                        PWM1MR5 = Valor_Inicial;
                        PWM1LER |= ( 0x01 << 5 );
                        break;

                case CANAL_6:
                        PWM1MR6 = Valor_Inicial;
                        PWM1LER |= ( 0x01 << 6 );
                        break;

                default:            // default = DEDO_PULGAR o CANAL1
                        PWM1MR1 = Valor_Inicial;
                        PWM1LER |= ( 0x01 << 1 );
                        break;
        }
}