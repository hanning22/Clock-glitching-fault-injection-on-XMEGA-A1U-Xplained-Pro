/*
 * cwtoxplained2.c
 *
 * Created: 1/2/2026 10:57:16 pm
 * Author : honha
 */ 

#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>
#include "simpleserial.h"
#include "xmega_hal.h"

//uint8_t infinite_loop(uint8_t* in);
//uint8_t glitch_loop(uint8_t* in);
//uint8_t password(uint8_t* pw);

// Make sure no optimization happens for demo glitch logic.
// #pragma GCC push_options
// #pragma GCC optimize ("O0")

#if SS_VER == SS_VER_2_1
uint8_t glitch_loop(uint8_t cmd, uint8_t scmd, uint8_t len, uint8_t* in)
#else
uint8_t glitch_loop(uint8_t* in, uint8_t len)
#endif
{
	volatile uint16_t i, j;
	volatile uint32_t cnt;
	cnt = 0;
	trigger_high();
	for(i=0; i<50; i++){
		for(j=0; j<50; j++){
			cnt++;
		}
	}
	trigger_low();
	simpleserial_put('r', 4, (uint8_t*)&cnt);
#if SS_VER == SS_VER_2_1
	return (cnt != 2500) ? 0x10 : 0x00;
#else
	return (cnt != 2500);
#endif
}

#if SS_VER == SS_VER_2_1
uint8_t glitch_comparison(uint8_t cmd, uint8_t scmd, uint8_t len, uint8_t* in)
#else
uint8_t glitch_comparison(uint8_t* in, uint8_t len)
#endif
{
	uint8_t ok = 5;
	trigger_high();
	if (*in == 0xA2){
		ok = 1;
		} else {
		ok = 0;
	}
	trigger_low();
	simpleserial_put('r', 1, (uint8_t*)&ok);
	return 0x00;
}

#if SS_VER == SS_VER_2_1
uint8_t password(uint8_t cmd, uint8_t scmd, uint8_t len, uint8_t* pw)
#else
uint8_t password(uint8_t* pw, uint8_t len)
#endif
{
	char passwd[] = "touch";
	char passok = 1;
	int cnt;

 
	trigger_high();

	for(cnt = 0; cnt < 5; cnt++){
		if (pw[cnt] != passwd[cnt]){
			passok = 0;
		}
	}

	trigger_low();

	simpleserial_put('r', 1, (uint8_t*)&passok);
	return 0x00;
}

#if SS_VER == SS_VER_2_1
uint8_t infinite_loop(uint8_t cmd, uint8_t scmd, uint8_t len, uint8_t* in)
#else
uint8_t infinite_loop(uint8_t* in, uint8_t len)
#endif
{


	//Some fake variable
	volatile uint8_t a = 0;

	//External trigger logic
	trigger_high();
	trigger_low();

	//Should be an infinite loop
	while(a != 2){
		;
	}

	

	putch('r');
	putch('B');
	putch('R');
	putch('E');
	putch('A');
	putch('K');
	putch('O');
	putch('U');
	putch('T');
	putch('\n');



	return 0;
}

// #pragma GCC pop_options

int main(void)
{
	platform_init();
	init_uart();
	trigger_setup();

/*	
	putch('r');
	putch('R');
	putch('E');
	putch('S');
	putch('E');
	putch('T');
	putch(' ');
	putch(' ');
	putch(' ');
	putch('\n'); */

	simpleserial_init();
	simpleserial_addcmd('g', 0, glitch_loop);
	simpleserial_addcmd('c', 1, glitch_comparison);
	#if SS_VER == SS_VER_2_1
	simpleserial_addcmd(0x01, 5, password);
	#else
	simpleserial_addcmd('p', 5, password);
	#endif
	simpleserial_addcmd('i', 0, infinite_loop);
	while(1)
	simpleserial_get();
}





