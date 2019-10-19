/*
*Fichier: pb2.cpp
*Auteur(s): Louis CORMIER, Dogbéda Georges GNAGA
*Date de creation: 21 février 2017
*Date de modification: 27 février 2017 par Louis CORMIER, Dogbéda Georges GNAGA
*Description: Salon de bronzage
*/

#include <avr/io.h> 
#include <stdint.h>
#define 	F_CPU   8000000UL
#include <util/delay_basic.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "can.h"

/****************************************************************************
* Fonction: void ambre
* Description : Crée l'illusion d'une couleur ambre
* Paramètres: aucun
* Retour: aucun
****************************************************************************/
void ambre(){
	PORTB = 0x01;
	_delay_ms(5);
	PORTB = 0x02;
	_delay_ms(25);	
}

int main () {
	DDRC = 0x00;
	DDRB = 0xFF;

	uint8_t minimumPourBronzer = 70;
	uint8_t minimumPourBruler = 250;

	for(;;){
		can convertisseurAnalogiqueNumerique; //Constructeur d'un object convertisseurAnalogiqueNumerique
		uint16_t valeurDeLecture = convertisseurAnalogiqueNumerique.lecture(0x00); //lecture sur portB sur la pinA
		uint8_t valeur8bits = valeurDeLecture >> 2; //Retire les deux derniers bits et place la valeurs dans une variable à 8 bits

		if (valeur8bits < minimumPourBronzer){
			PORTB = 0x02;
		}
		else if (valeur8bits > minimumPourBruler){
			PORTB = 0x01;
		}
		else if(valeur8bits > minimumPourBronzer &&valeur8bits <= minimumPourBruler) {
			ambre();
		}
	} 
}