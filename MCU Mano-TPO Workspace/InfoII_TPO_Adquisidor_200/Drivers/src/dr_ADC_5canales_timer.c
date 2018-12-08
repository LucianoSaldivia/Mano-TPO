/*
 * dr_timer_adc.c
 *
 *  Created on: Oct 14, 2018
 *      Author: cha
 */

#include "../inc/dr_ADC_5canales_timer.h"


/********************************/
/* Variables globales al módulo */
/********************************/


static uint8_t analogIn = 0;

volatile uint16_t ADC_sample;
volatile uint8_t ADC_dato_disponible;


/*****************************************/
/* Funciones del Timer que maneja el ADC */
/*****************************************/


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
			Ts = (double)1 / FRECUENCIA_MUESTREO ;

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

	// 5. Habilito la interrupción correspondiente al TIMER0 en el NVIC.
	// Bit 1 == 1
	ISER0 |= ( (0x1)<<1 );

	// 7. Config de acción cuando el TC == MATCH
	T0MCR |= ( (0x1)<<0 );	// Interrupción ON.
	T0MCR |= ( (0x1)<<1 );	// Reset de counters ON.
	T0MCR &= ~( (0x1)<<2 );	// Stop timer OFF.

	// Sacar el timer del estado RESET y habilitarlo para contar lo hago cuando sea necesario.
}

void TIMER0_IRQHandler(void){

	// Limpio la interrupción del TIMER0, escribiendo un 1.
	T0IR |= ( (0x01)<<0 );

	// Disparo una conversión.
	ADC_Start();

	// Saco el estado reset. Es necesario esto ?
	T0TCR &= ~( (0x1)<<1 );

}


/*********************/
/* Funciones del ADC */
/*********************/


void ADC_Init(void){
	uint8_t Channel_Default;

	// 1. Alimentación del ADC.
	PCONP |= (0x01<<12);

	// 2. Habilitar el ADC.
	AD0CR |= (0x01<<21);

	// 3. Clock para el periférico: PCLK_ADC
	// Bits 24:25 == 00 => CCLK/4.
	PCLKSEL0 &= ~(0x03<<24);

	// 4. Selecciono modo "Software Controlled" (llamemoslo manual)
	// Bit 16 (BURST) ==  0.
	AD0CR &= ~( (0x1)<<16 );

	// 5. Apago la conversión.
	// Bits 24:26 == 000
	AD0CR &= ~( (0x7)<<24 );

	// Configuración del canal de entrada. El default será el canal 2.
	Channel_Default = 0;
	ADC_InputSelect(Channel_Default);

	// 8. Habilito interrupción correspondiente al ADC en el NVIC.
	ISER0 |= (1<<22);

	// 9. Definir Sample Rate.

	/* En Software-Controlled mode, una conversión son 65 clocks.
	 *
	 * SAMPLE RATE = CLK_ADC / 65
	 *
	 * CLK_ADC = PCLK_ADC0 / (CLKDIV + 1)
	 *
	 * CLK_ADC debe ser menor o igual a 13 MHz
	 */

	/* CLKDIV son bits 8 a 15 en AD0CR */
	AD0CR |= (0x2);	// CLKDIV == 2

	/* Entonces: CLK_ADC = (100/4)*10^6 / (2+1) = 8 333 333.333
	**
	** Sample Rate = 8 333 333.333 / 65 =~ 128,205 kHz */
}

void ADC_InputSelect(uint8_t selectedInput){
	uint8_t shift;
	uint8_t port, pin, pin_function;

	analogIn = selectedInput;

	/* Nota: Para nosotros las entradas 0, 1 y 2 serán las de la PLACA.
	** Las entradas 4 y 5 serán pines directamente del micro */

	/* EA2 de la placa es AD0.2  */
	if( analogIn == 0){
		shift = 2;
		port = P0;
		pin = 25;
		pin_function = PINSEL_FUNC1;
	}

	/* EA1 de la placa es AD0.1 */
	if( analogIn == 1){
		shift = 1;
		port = P0;
		pin = 24;
		pin_function = PINSEL_FUNC1;
	}

	/* EA0 de la placa es AD0.5 */
	if( analogIn == 2){
		shift = 5;
		port = P1;
		pin = 31;
		pin_function = PINSEL_FUNC3;
	}

	/* Entrada directa al micro: AD0.3 */	// PIN H[18]
	if( analogIn == 3){
		shift = 3;
		port = P0;
		pin = 26;
		pin_function = PINSEL_FUNC1;
	}

	/* Entrada directa al micro: AD0.4 */	// PIN H[19]
	if( analogIn == 4){
		shift = 4;
		port = P1;
		pin = 30;
		pin_function = PINSEL_FUNC3;
	}

	// 5. Config el pin para entrada al ADC0.x
	SetPINSEL(port, pin, pin_function);

	// Del manual: The PINMODE should be neither pull-up nor pull-down resistor enabled.
	SetResistorMode(port, pin, PINMODE_TRISTATE);

	// Configuro el pin como entrada
	SetDIR(port, pin, 0);

	// 6. Selecciono el canal del ADC indicado.
	AD0CR &= ~(0xFF);			// Debe haber solo 1 pin en alto. Por las dudas, todos en 0 primero.
	AD0CR |= (0x01<<shift);		// Pongo AD0.x en alto

	// 7. Sobre la alerta de interrupciones
	AD0INTEN &= ~(0xFF);			// Primero pongo todos en 0 por las dudas.
	AD0INTEN |= (0x01<<shift);		// Habilito interrupción que alerte sobre conversión del canal AD0.x
	AD0INTEN &= ~( (0x1)<<8 );		// Solamente los canales habilitados en este registro pueden generar interrupciones.
}

void ADC_Start(void){
	/* Empieza una conversión de modo Software-Controlled */
	AD0CR |= (0x01<<24);
}

void ADC_IRQHandler(void){
	uint32_t adc_data_reg = 0;

	// Leo el registro con el resultado
	if(analogIn == 0){			// El pulgar se debe conectar a EA2
		adc_data_reg = AD0DR2;
	}
	else if(analogIn == 1){		// El índice se debe conectar a EA1
		adc_data_reg = AD0DR1;
	}
	else if(analogIn == 2){		// El medio se debe conectar a EA0
		adc_data_reg = AD0DR5;
	}
	else if(analogIn == 3){		// El anular se debe conectar a micro H[18]
		adc_data_reg = AD0DR3;
	}
	else if(analogIn == 4){		// El meñique se debe conectar a micro H[19]
		adc_data_reg = AD0DR4;
	}

	// chequeo si bit DONE == 1 => hay un resultado disponible
	if ((adc_data_reg >> 31) == 0x01) {

		// Obtengo los 12 bits de la muestra
		ADC_sample = (adc_data_reg >> 4) & 0xFFF;
		ADC_dato_disponible = 1;

	}

	analogIn++;

	/* Protección para reiniciar el muestreo de los dedos */
	if ( analogIn > 4 ) {
		analogIn = 0;
	}

	ADC_InputSelect(analogIn);
}




/* LAS SIGUIENTES FUNCIONES, TOCAN REGISTROS (SON DRIVERS !!). PERO SE LLAMAN DESDE LA MdE !!? */

void Start_Sampling( void ){

	/* Para asegurarnos de que comienze por la entrada 0, reseteamos analogIn */
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

