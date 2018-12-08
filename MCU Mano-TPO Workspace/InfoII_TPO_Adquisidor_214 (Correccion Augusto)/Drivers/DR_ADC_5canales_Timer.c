/* Recordar que según nuestra definición, los buffers y entradas se corresponden como:
 *
 * H[15] = AD0.0 = meñique
 * H[16] = AD0.1 = anular
 * H[17] = AD0.2 = medio
 * H[18] = AD0.3 = índice
 * H[19] = AD0.4 = pulgar
 *
**/

/*******************************************************************************************************************************//**
 *
 * @file		DR_ADC_5canales_Timer.c
 * @brief		--Descripción del Módulo--
 * @date		14/10/2018
 * @author		Esteban Chiama
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/


#include "DR_ADC_5canales_Timer.h"


/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/


#define FRECUENCIA_MUESTREO		(double)20
#define MICROSEG				((double)1/(double)1000000)

#define INPUT_ADC0		0


/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/


volatile uint16_t ADC_sample;
volatile uint8_t ADC_dato_disponible;


/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/


static uint8_t analogIn = 0;
static volatile uint32_t aux_cnt_Timer = 0;
static volatile uint32_t aux_cnt_ADC = 0;


/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/


void ADC_Pins_Initialize(void);
void ADC_InputSelect( uint8_t selectedInput );
void ADC_Start( void );


 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/


void TIMER0_IRQHandler(void){

	// Limpio la interrupción del TIMER0, escribiendo un 1.
	T0IR |= ( (0x01)<<0 );

	aux_cnt_Timer++;

//	// Saco el ADC de standby
//	AD0CR |= (0x01<<21);

	// Disparo una ciclo de conversiones.
	ADC_Start();

	// Saco el estado reset. Es necesario esto ?
	T0TCR &= ~( (0x1)<<1 );

}

void ADC_Pins_Initialize(void){

	// Del manual: The PINMODE should be neither pull-up nor pull-down resistor enabled.

	/* H[15] es AD0.0 */
	SetPINSEL( P0, 23, PINSEL_FUNC1);
	SetResistorMode( P0, 23, PINMODE_TRISTATE);

	/* H[16] es AD0.1 */
	SetPINSEL( P0, 24, PINSEL_FUNC1);
	SetResistorMode( P0, 24, PINMODE_TRISTATE);

	/* H[17] es AD0.2  */
	SetPINSEL( P0, 25, PINSEL_FUNC1);
	SetResistorMode( P0, 25, PINMODE_TRISTATE);

	/* H[18] es AD0.3 */
	SetPINSEL( P0, 26, PINSEL_FUNC1);
	SetResistorMode( P0, 26, PINMODE_TRISTATE);

	/* H[19] es AD0.4 */
	SetPINSEL( P1, 30, PINSEL_FUNC3);
	SetResistorMode( P1, 30, PINMODE_TRISTATE);

}


void ADC_InputSelect(uint8_t selectedInput){
	uint8_t shift;

	analogIn = selectedInput;

	// 1. Identifico el canal a seleccionar
	if( analogIn == 0){	shift = 0; }	// AD0.0
	if( analogIn == 1){	shift = 1; }	// AD0.1
	if( analogIn == 2){ shift = 2; }	// AD0.2
	if( analogIn == 3){ shift = 3; }	// AD0.3
	if( analogIn == 4){	shift = 4; }	// AD0.4

	// 2. Lo configuro en el ADC.
	AD0CR &= ~(0xFF);			// Debe haber solo 1 pin en alto. Por las dudas, todos en 0 primero.
	AD0CR |= (0x01<<shift);		// Pongo AD0.x en alto

	// 3. Configuro la interrupción correspondiente.
	AD0INTEN &= ~(0xFF);			// Primero pongo todos en 0 por las dudas.
	AD0INTEN |= (0x01<<shift);		// Habilito interrupción que alerte sobre conversión del canal AD0.x
}


void ADC_Start(void){
	// Empiezo una conversión manual
	AD0CR |= (0x01<<24);
}


void ADC_IRQHandler(void){
	uint32_t adc_data_reg = 0;

	// Leo el registro con el resultado.
	// Esto además limpia el flag de interrupción de este registro
	if(analogIn == 0){ adc_data_reg = AD0DR0; }
	else if(analogIn == 1){	adc_data_reg = AD0DR1; }
	else if(analogIn == 2){ adc_data_reg = AD0DR2; }
	else if(analogIn == 3){ adc_data_reg = AD0DR3; }
	else if(analogIn == 4){ adc_data_reg = AD0DR4; }

	aux_cnt_ADC++;

	// chequeo si bit DONE == 1 => hay un resultado disponible
	if ((adc_data_reg >> 31) == 0x01) {

		// Obtengo los 12 bits de la muestra
		ADC_sample = (adc_data_reg >> 4) & 0xFFF;
		ADC_dato_disponible = 1;

	}

	// Frenar conversiones
	AD0CR &= ~(0x1 << 24);

	analogIn++;

	// Una vez obtenida una muestra de cada uno de los 5 canales no se re-dispara el ADC.
	if ( analogIn > 4 ) {
		analogIn = 0;
		ADC_InputSelect(analogIn);
		return;
	}

	ADC_InputSelect(analogIn);
	ADC_Start();
}


 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/


void Timer0_ADC_Init( void ){

	double Ts=0;
	uint32_t match=0;

	// 1. Alimentar el timer.
	PCONP |= ( (0x1)<<1 );

	// 2. Set up PCLK del timer.
	// Bits 2:3 == 00 => CCLK/4 = 25MHz.
	PCLKSEL0 &= ~( (0x3)<<2 );

	// 3. Seleciono modo Timer.
	// Bits 0:1 == 00
	*T0CTCR &=  ~( (0x3)<<0 );

	// 3. Configuro el prescale, y el max. timer count

			// Queremos Fs = 4 kHz
			// Son 5 dedos. 4kHz / 5 = 800 Hz para una mano entera
			Ts = (double)1 / (double)FRECUENCIA_MUESTREO ;

			// 3.1 Prescale Counter.
			/* El timer hará (T0PR+1) ciclos de su clock (CCLK/4) hasta hacer Timer Count + 1.
			** Con este valor, +1 Timer Counter es un ciclo de 1 microseg. */
			T0PR = 24;
			match = (uint32_t) ( Ts / MICROSEG );

			// 3.2 Timer Match. Valor hasta el que cuenta el timer.
			/* Fs = 4 kHz => match = 250 useg hasta empezar ADC.
			** Fs debe ser menor a frecuencia del ADC. */
			T0MR0 = match;

	// Detengo el timer.
	T0TCR &= ~( (0x1)<<0 );
	// Pongo el timer en estado RESET.
	T0TCR |= ( (0x1)<<1 );

	// 4. Limpio la interrupción del TIMER0, escribiendo un 1.
	T0IR |= ( (0x01)<<0 );

	// 7. Config de acción cuando el TC == MATCH
	T0MCR |= ( (0x1)<<0 );	// Interrupción ON.
	T0MCR |= ( (0x1)<<1 );	// Reset de counters ON.
	T0MCR &= ~( (0x1)<<2 );	// Stop timer OFF.

	// Sacar el timer del estado RESET y habilitarlo para contar lo hago cuando sea necesario.

	// 5. Habilito la interrupción correspondiente al TIMER0 en el NVIC.
	// Bit 1 == 1
	ISER0 |= ( (0x1)<<1 );
}


void ADC_Init(void){

	// 1. Alimentación del ADC.
	PCONP |= (0x01<<12);

	// 2. Habilitar el ADC. (sacarlo de standby)
	AD0CR |= (0x01<<21);

	// 3. PCLK_ADC = CCLK/8 = 12.5 MHz
	PCLKSEL0 |= ( (0x3) << 24 );	// Bits 24:25 == 11

	// 4. Modo: "Software Controlled"
	AD0CR &= ~( (0x1)<<16 );		// Bit 16 (BURST) = 0

	// 5. START = 0
	AD0CR &= ~( (0x7)<<24 );		// Bits 24:26 = 000

	// 6. Sample Rate.
	// En modo manual una conversión son 65 clocks.
	// CLK_ADC debe ser <= 13 MHz
	// CLK_ADC = PCLK_ADC0 / (CLKDIV + 1)
	// SAMPLE RATE = CLK_ADC / 65
	AD0CR &= ~( (0xFF) << 8 );		// Bits 8:15 (CLKDIV) = 0
	// Entonces:
	// CLK_ADC = (100/8)*10^6 / (0+1) = 12.5 MHz
	// SAMPLE RATE = 12.5 MHz / 65 =~ 192,307 kHz

	// 7. Inicialización de los pines
	ADC_Pins_Initialize();

	// 8. Configuro interrupciones para que sean por cada canal
	AD0INTEN &= ~( (0x1)<<8 );		// Bit 8 = 0 ( Only the individual ADC channels enabled by ADINTEN7:0 will generate	interrupts )

	// 9. Configuro:
	// - Canal a muestrear
	// - Interrupción correspondiente.
	ADC_InputSelect( INPUT_ADC0 );

	// 9. Habilito interrupción correspondiente al ADC en el NVIC.
	ISER0 |= (1<<22);
}


/* LAS SIGUIENTES FUNCIONES, TOCAN REGISTROS (SON DRIVERS !!). PERO SE LLAMAN DESDE LA MdE !!? */

void Start_Sampling( void ){

	// Reseteamos analogIn para que comienze por la entrada 0
	analogIn = 0;

	// Saco el timer del estado RESET.
	T0TCR &= ~( (0x01)<<1 );

	// Arranco el timer.
	T0TCR |= ( (0x01)<<0 );

}


void Stop_Sampling( void ){

	// Detengo el timer.
	T0TCR &= ~( (0x01)<<0 );
	// Pongo el timer en estado RESET.
	T0TCR |= ( (0x1)<<1 );

	// En RESET ya se hace, pero por las dudas: pongo en 0 el timer counter y el prescale counter.
	T0TC = 0x0;
	T0PC = 0x0;

	// Limpio la interrupción del TIMER0, escribiendo un 1.
	T0IR |= ( (0x01)<<0 );
}
