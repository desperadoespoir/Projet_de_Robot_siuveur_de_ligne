#include <avr/io.h>
#include <stdint.h>
#define 	F_CPU   8000000UL
#include <util/delay_basic.h>
#include <util/delay.h>
#include "moteur.h"

int main(){
	Moteur moteur;
	DDRD =0xff;
	for (;;){

		moteur.tournermoteur(255,255, 0x02);
	}
}