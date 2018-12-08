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

// Registro Timer 0 External Match Register
#define T0EMR		*( (volatile uint32_t *) 0x4000403CUL )

// Frecuencias de Muestreo
#define FS_CALIBRATION		200
#define	FS_MANOTRONIC		2500
// FS_MANOTRONIC para los motores debe ser 500Hz
// Para debuggear con app asys 2500Hz

// Para el ADC
#define INPUT_ADC0				0

// Para la configuración del TIMER0
#define MICROSEG				((double)1/(double)1000000)

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

// Frena conversiones
#define ADC_STOP()				AD0CR &= ~(0x7 << 24)

// Empiezo una conversión manual
#define ADC_START()				AD0CR |= (0x01<<24)

// Que el ADC empiece por una señal de MAT0.1
#define	ADC_START_ON_SIGNAL()	AD0CR |= ( (0x4)<<24 )

// Set corresponding External Match bit and MAT pin to high
#define TIMER0_SET_MATCH0_TO_SET_EM0_HIGH()			T0EMR |= ( (0x2)<<6)

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/

volatile uint16_t ADC_Samples[QTY_INPUT_CHANNELS] = {0};

// flags
volatile uint8_t f_ADC_Samples_rdy = 0;

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

// H[15] es AD0.0	-->		P0, 23
// H[20] es AD0.5	-->		P1, 31
// H[17] es AD0.2	-->		P0, 25
// H[18] es AD0.3	-->		P0, 26
// H[19] es AD0.4	-->		P1, 30
static uint8_t input_ports[] = {P0, P1, P0, P0, P1};
static uint8_t input_pins[] = {23, 31, 25, 26, 30};
static uint8_t input_funcs[] = {PINSEL_FUNC1, PINSEL_FUNC3, PINSEL_FUNC1, PINSEL_FUNC1, PINSEL_FUNC3};
static uint8_t input_AD0_number[] = {0, 5, 2, 3, 4};

static volatile uint32_t *ADC_Data_Registers[QTY_INPUT_CHANNELS];

// Driver configuration variables
static volatile uint16_t SampleRate = FS_MANOTRONIC;
static volatile uint8_t InputChannel = 0;

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

void ADC_DR_Initialize(void);
void ADC_Pins_Initialize(void);
void ADC_InputSelect(uint8_t requested);

void TIMER0_ADC_FS_Config(uint16_t input_fs);
void TIMER0_Pin_Initialize(void);

 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

void ADC_DR_Initialize(void){
	uint8_t i=0;

	ADC_Data_Registers[0] = AD0DR;

	i=1;
	while(i<QTY_INPUT_CHANNELS){
		ADC_Data_Registers[i] = &(AD0DR[input_AD0_number[i]]);
		i++;
	}
}

void ADC_IRQHandler(void){
	uint32_t data_reg = 0;

	// Leo el registro con el resultado.
	// Esto además limpia el flag de interrupción de este registro
	data_reg = *(ADC_Data_Registers[InputChannel]);

	// chequeo si bit DONE == 1 => hay un resultado disponible
	if ( (data_reg >> 31) == 0x01 ) {
		// Obtengo la muestra de 12bits y la coloco en su variable de canal correspondiente
		ADC_Samples[InputChannel] = (data_reg >> 4) & 0xFFF;
	}

	ADC_STOP();			// Frenar conversiones
	InputChannel++;

	// caso: Ya se tomó muestras de los 5 canales
	if ( InputChannel == QTY_INPUT_CHANNELS ) {
		T0EMR &= ~(0xFFF);					// plancho EM1 (pin MAT0.1) a 0, para que cuando el timer haga MATCH vuelva a tener flanco ascendente
											// ~((0x1)<1) o ~(0xF) NO FUNCIONAN. 0xFFF sí lo pone en 0
		TIMER0_SET_MATCH0_TO_SET_EM0_HIGH();
		ADC_START_ON_SIGNAL();				// Que el ADC empiece por una señal de MAT0.1
		InputChannel = 0;					// Que vuelva a comenzar del 1er canal
		ADC_InputSelect(InputChannel);
		f_ADC_Samples_rdy = 1;				// Avisa que se hizo 1 ciclo de conversiones
		return;								// Que no se re-dispare el ADC
	}

	ADC_InputSelect(InputChannel);
	ADC_START();		// Conversión Manual
}

void ADC_Pins_Initialize(void){
	uint8_t i=0;

	// Del manual: The PINMODE should be neither pull-up nor pull-down resistor enabled.
	while( i < QTY_INPUT_CHANNELS){
		SetPINSEL(input_ports[i], input_pins[i], input_funcs[i]);
		SetResistorMode(input_ports[i], input_pins[i], PINMODE_TRISTATE);
		i++;
	}
}

void ADC_InputSelect(uint8_t requested){
	uint8_t shift;

	InputChannel = requested;

	// Identifico el shift necesario correspondiente al canal a seleccionar
	shift = input_AD0_number[InputChannel];

	// 2. Lo configuro en el ADC.
	AD0CR &= ~(0xFF);			// Debe haber solo 1 pin en alto. Por las dudas, todos en 0 primero.
	AD0CR |= (0x01<<shift);		// Pongo AD0.x en alto

	// 3. Configuro la interrupción correspondiente.
	AD0INTEN &= ~(0xFF);			// Primero pongo todos en 0 por las dudas.
	AD0INTEN |= (0x01<<shift);		// Habilito interrupción que alerte sobre conversión del canal AD0.x
}

void TIMER0_ADC_FS_Config(uint16_t input_fs){
	double Ts=0;
	uint32_t match=0;

	SampleRate = input_fs;
	Ts = (double)1 / (double)SampleRate ;

	// 1. Prescale Counter. El timer hará (T0PR+1) ciclos de su clock (CCLK/4) hasta hacer Timer Count + 1.
	// Con este valor, +1 Timer Counter es un ciclo de 1 microseg.
	T0PR = 24;
	match = (uint32_t) ( Ts / MICROSEG );

	// 2. Timer Match. Valor hasta el que cuenta el timer.
	// Por default, sample_rate = 2.5kHz => match=400 useg hasta disparar una conversión
	// Con este valor, la frecuencia del timer es menor a la del adc. f = 2500 Hz
	// Fs debe ser menor a frecuencia del ADC.
	T0MR0 = match;
}

// Función para inicializar el pin de la señal MAT0.1
void TIMER0_Pin_Initialize(void){
	SetPINSEL( P1, 29, PINSEL_FUNC3);
}

 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/

void TIMER0_ADC_Init( void ){
	// 1. Alimentar el timer.
	PCONP |= ( (0x1)<<1 );

	// 2. Set up PCLK del timer.
	// Bits 2:3 == 00 => CCLK/4 = 25MHz.
	PCLKSEL0 &= ~( (0x3)<<2 );

	// Inicializo el pin para señal MAT0.1
	TIMER0_Pin_Initialize();

	// 3. Seleciono modo Timer.
	// Bits 0:1 == 00
	*T0CTCR &=  ~( (0x3)<<0 );

	// 3. Configuro el prescale, y el max. timer count
	TIMER0_ADC_FS_Config(SampleRate);

	// Detengo el timer.
	T0TCR &= ~( (0x1)<<0 );
	// Pongo el timer en estado RESET.
	T0TCR |= ( (0x1)<<1 );

	// 4. Limpio la interrupción del TIMER0, escribiendo un 1.
	T0IR |= ( (0x01)<<0 );

	// 7. Config de acción cuando el TC == MATCH
	T0MCR &= ( (0x1)<<0 );	// Interrupción OFF.
	T0MCR |= ( (0x1)<<1 );	// Reset de counters ON.
	T0MCR &= ~( (0x1)<<2 );	// Stop timer OFF.

	// 8. Config External Match Signal	(for pin MAT0.1 see T0EMR1)
	T0EMR &= ~(0xFFF);		// clear (EM1 set to 0)
											// Bits 6:7 correspond to EM1
	TIMER0_SET_MATCH0_TO_SET_EM0_HIGH();	// 10:	Set corresponding External Match bit and MAT pin to high

	// Sacar el timer del estado RESET y habilitarlo para contar lo hago cuando sea necesario.

	// 5. Interrupción correspondiente al TIMER0 en el NVIC.
	// Bit 1 == 1
	ICER0 |= ( (0x1)<<1 );	// NVIC Timer0 Interrupt OFF
}

void ADC_Init(void){

	ADC_DR_Initialize();

	// 1. Alimentación del ADC.
	PCONP |= (0x01<<12);

	// 2. Habilitar el ADC. (sacarlo de standby)
	AD0CR |= (0x01<<21);

	// 3. PCLK_ADC = CCLK/8 = 12.5 MHz
	PCLKSEL0 |= ( (0x3) << 24 );	// Bits 24:25 == 11

	// 4. Modo: "Software Controlled"
	AD0CR &= ~( (0x1)<<16 );		// Bit 16 (BURST) = 0

	// 5. Modo de comienzo (START)
	// Bits 24:26
	ADC_STOP();						// 000: No start
	ADC_START_ON_SIGNAL();			// 100: mira pin MAT0.1
	AD0CR &= ~( (0x1)<<27 );		// Starts on rising edge

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

void Start_Sampling(uint8_t app){
	InputChannel = 0;					// Reseteamos analogIn para que comienze por la entrada 0
	// Config. FS acorde a la aplicación
	if( app == MANOTRONIC ){ TIMER0_ADC_FS_Config(FS_MANOTRONIC); }
	if( app == CALIBRATION ){ TIMER0_ADC_FS_Config(FS_CALIBRATION); }

	T0TCR &= ~( (0x01)<<1 );			// Saco el timer del estado RESET.
	T0TCR |= ( (0x01)<<0 );				// Arranco el timer.
}

void Stop_Sampling(void){
	T0TCR &= ~( (0x01)<<0 );	// Detengo el timer.
	T0TCR |= ( (0x1)<<1 );		// Pongo el timer en estado RESET.

	// En RESET ya se hace, pero por las dudas: pongo en 0 el timer counter y el prescale counter.
	T0TC = 0x0;
	T0PC = 0x0;
}