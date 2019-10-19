/*
*Fichier: pb3.cpp
*Auteur(s): Louis CORMIER, Dogbéda Georges GNAGA
*Date de creation: 10 février 2017
*Date de modification: 10 février 2017 par Louis CORMIER, Dogbéda Georges GNAGA
*Description: Fonction pour faire tourner les roues	
*/

#include <avr/io.h> 
#include <stdint.h>
#define 	F_CPU   8000000UL
#include <util/delay.h>
#include <util/delay_basic.h>
#include <avr/interrupt.h>

void ajustementPWM ( uint8_t pwn1 ) {
	// mise a un des sorties OC1A et OC1B sur comparaison
	// reussie en mode PWM 8 bits, phase correcte
	// et valeur de TOP fixe a 0xFF (mode #1 de la table 16-5
	// page 130 de la description technique du ATmega324PA)
	TCCR1A = 0x04 ;
	TCNT1 = 0;
	OCR1A = pwn1 ;
	
	// division d'horloge par 8 - implique une frequence de PWM fixe
	TCCR1B =  0x02;
	TCCR1C = 0;
}

int main (){

}