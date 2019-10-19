/*
*Fichier: pb1.cpp
*Auteur(s): Louis CORMIER, Dogbéda Georges GNAGA
*Date de creation: 24 janviers 2017
*Date de modification: 24 janvier 2017 par Louis CORMIER, Dogbéda Georges GNAGA
*Description: Programme qui ouvre la lumière en rouge après avoir appuyer 5 fois sur l'interrupteur
*
*/

//60Hz 60 fois par secondes 400Hz 400 fois par secondes

#include <avr/io.h> 
#include <util/delay.h>

#define 	F_CPU   8000000UL

void tournerLesRoues (double hertz, double pourcentage){
	for(int i = 0; i < hertz; i++){
		for (int i = 0; i < int((2000000/ hertz) * (pourcentage / 100)); i++){
			PORTB = 0x01;
			_delay_us(1);
		}
		for (int i = 0; i < int((2000000 / hertz) * ((100-pourcentage) / 100)); i++){
			PORTB = 0x00;
			_delay_us(1);
		}
	}
}

int main () {
	DDRB = 0xff;
	for(;;){

		//60 Hertz
		//100%
		tournerLesRoues(60,0);

		//75%
		tournerLesRoues(60, 25);

		//50%
		tournerLesRoues(60, 50);

		//25%
		tournerLesRoues(60, 75);

		//0%
		tournerLesRoues(60, 100);
		
		//400Hertz
		//100%
		tournerLesRoues(400,0);

		//75%
		tournerLesRoues(400, 25);

		//50%
		tournerLesRoues(400, 50);

		//25%
		tournerLesRoues(400, 75);

		//0%
		tournerLesRoues(400, 100);

	}
}