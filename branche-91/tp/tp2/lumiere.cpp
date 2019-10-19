/*
Fichier: lumiere.cpp
Auteur(s): Louis CORMIER, Dogbéda Georges GNAGA
Date de creation: 20 janviers 2017
Date de modification: 24 janvier 2017 par Louis CORMIER, Dogbéda Georges GNAGA
Description: Programme qui active la LED de couleur ambre lorsque l'interrupteur est activé
*/


#include <avr/io.h> 
#include <util/delay.h>

int main() {
	
	DDRB = 0xff; // PORT B est en mode sortie

	for (;;){
		PORTB = 0x00; //Initialisé à off mettre dans for pour qu'il redevienne a off si bouton laché
		if (PIND & 0x04) {
			_delay_ms(10); //en miliseconde
			if (PIND & 0x04){ //contre-vérification Anti-rebond
				PORTB = 0x01; //Rouge
				_delay_ms(5);
				PORTB = 0x02; //Vert
				_delay_ms(25);
			}
		}
	}

}

