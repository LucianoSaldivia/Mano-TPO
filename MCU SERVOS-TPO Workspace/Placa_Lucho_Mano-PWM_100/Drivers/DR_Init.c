/*
 * DR_Init.c
 *
 *  Created on:
 *  	Author:
 */

#include "DR_Init.h"

void Kit_Init(void){

	//Configuro el PLL: seteo el clock del micro en 100MHz
	PLL_Init();

	LED_Initialize();		// Inicializo LEDS del STICK e Infotronic (IO pins)
	Switches_Initialize();	// Inicializo los switches
	SysTick_Init(2500, MICRO);	// Configuro SysTick en int. cada 2,5ms (2500us)
//	LCD_Init();				// Inicializo LCD. Usa el SysTick para inicializarse, por eso después sí o sí.
	UART0_Initialize();
	PWM1_Init_5Canales();

	//BUZZER APAGADO
	SetPINSEL(P0, 28, 0);
	SetDIR(P0, 28, 1);  //Configuro el pin del buzzer como salida
	SetPIN(P0, 28, 0);  //inicializo buzzer apagado
}

/********************************************************************************
	\fn  void PLL_Init (void)
	\brief: Este bloque de codigo habilita el oscilador externo como fuente de clk
			del micro, y configura el PLL (Phase Locked Loop) para generar un clock
			interno de 100MHz a partir del oscilador conectado.
	\author & date: INFO2 - Nov2012
 	\param 	void
	\return void
*/
void PLL_Init(void)
{
	SCS       = SCS_Value;

	if (SCS_Value & (1 << 5))               /* If Main Oscillator is enabled      */
		while ((SCS & (1<<6)) == 0);/* Wait for Oscillator to be ready    */

	CCLKCFG   = CCLKCFG_Value;      /* Setup Clock Divider                */

	PCLKSEL0  = PCLKSEL0_Value;     /* Peripheral Clock Selection         */
	PCLKSEL1  = PCLKSEL1_Value;

	CLKSRCSEL = CLKSRCSEL_Value;    /* Select Clock Source for PLL0       */

	PLL0CFG   = PLL0CFG_Value;      /* configure PLL0                     */
	PLL0FEED  = 0xAA;
	PLL0FEED  = 0x55;

	PLL0CON   = 0x01;             /* PLL0 Enable                        */
	PLL0FEED  = 0xAA;
	PLL0FEED  = 0x55;

	while (!(PLL0STAT & (1<<26)));/* Wait for PLOCK0                    */

	PLL0CON   = 0x03;             /* PLL0 Enable & Connect              */
	PLL0FEED  = 0xAA;
	PLL0FEED  = 0x55;

	while (!(PLL0STAT & ((1<<25) | (1<<24))));/* Wait for PLLC0_STAT & PLLE0_STAT */

	PLL1CFG   = PLL1CFG_Value;
	PLL1FEED  = 0xAA;
	PLL1FEED  = 0x55;

	PLL1CON   = 0x01;             /* PLL1 Enable                        */
	PLL1FEED  = 0xAA;
	PLL1FEED  = 0x55;

	while (!(PLL1STAT & (1<<10)));/* Wait for PLOCK1                    */

	PLL1CON   = 0x03;             /* PLL1 Enable & Connect              */
	PLL1FEED  = 0xAA;
	PLL1FEED  = 0x55;

	while (!(PLL1STAT & ((1<< 9) | (1<< 8))));/* Wait for PLLC1_STAT & PLLE1_STAT */

	PCONP     = PCONP_Value;        /* Power Control for Peripherals      */

	CLKOUTCFG = CLKOUTCFG_Value;    /* Clock Output Configuration         */

	FLASHCFG  = (FLASHCFG & ~0x0000F000) | FLASHCFG_Value;
}
