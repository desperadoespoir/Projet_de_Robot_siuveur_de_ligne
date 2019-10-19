/*
*Fichier: pb1.cpp
*Auteur(s): Louis CORMIER, Dogbéda Georges GNAGA
*Date de creation: 24 janviers 2017
*Date de modification: 24 janvier 2017 par Louis CORMIER, Dogbéda Georges GNAGA
*Description: Programme qui ouvre la lumière en rouge après avoir appuyer 5 fois sur l'interrupteur
*
*/

#include <avr/io.h> 
#include <util/delay.h>

int main () {

	DDRB = 0xff;
	DDRD = 0x00;
	PORTB = 0x00;

	unsigned int tempsAllume = 12;
	unsigned int tempsEteind = 0;

	unsigned int compteur = 0;

	for (;;){
		for (int i = 0; i < tempsAllume; i++){
			PORTB = 0x01;
		}
		for (int i = 0; i < tempsEteind; i++){
			PORTB = 0x00;
		}
		if(compteur == 6){
			tempsAllume--;
			tempsEteind++;
		}
		if(tempsAllume == 0){
			_delay_ms(10000);
			tempsAllume = 15;
			tempsEteind = 0;
			compteur = 0;
		}
		compteur++;
	}
}