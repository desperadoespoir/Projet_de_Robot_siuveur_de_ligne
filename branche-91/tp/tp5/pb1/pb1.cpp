/*
*Fichier: pb1.cpp
*Auteur(s): Louis CORMIER, Dogbéda Georges GNAGA
*Date de creation: 24 janviers 2017
*Date de modification: 7 février 2017 par Louis CORMIER, Dogbéda Georges GNAGA
*Description: Programme qui change les lumières selon l'état dans lequel il se trouve
*/

#include <avr/io.h> 
#include <stdint.h>
#define 	F_CPU   8000000UL
#include <util/delay.h>
#include <util/delay_basic.h>
#include <avr/interrupt.h>

volatile uint8_t etatCourrant = 0; //Etat initial
enum Etat {rougeRelacher, ambreAppuyer, vertRelacher, rougeAppuyer, eteint, vertAppuyer, n_etats};
volatile Etat etat;


// placer le bon type de signal d'interruption
// a prendre en charge en argument
ISR (INT0_vect) { //interruption par poussoir
	// laisser un delai avant de confirmer la reponse du
	// bouton-poussoir: environ 30 ms (anti-rebond)
	_delay_ms ( 30 );
	// Se souvenir ici si le bouton est presse ou relache
	
	// changements d'etats tels que ceux de la
	// semaine precedente
	etat = Etat((uint8_t(etat)+1) % n_etats);
	// Voir la note plus bas pour comprendre cette instruction et son role
	EIFR |= (1 << INTF0) ;
}

void initialisation ( void ) {
	// cli est une routine qui bloque toutes les interruptions.
	// Il serait bien mauvais d'etre interrompu alors que
	// le microcontroleur n'est pas pret...
	cli ();
	
	// configurer et choisir les ports pour les entrees
	// et les sorties. DDRx... Initialisez bien vos variables
	DDRB = 0xff;
	DDRD = 0x00;
	
	// cette procédure ajuste le registre EIMSK
	// de ATmega324PA pour permettre les interruptions externes
	EIMSK |= _BV(INT0);
	
	// il faut sensibiliser les interruptions externes aux
	// changements de niveau du bouton-poussoir
	// en ajustant le registre EICRA
	EICRA |= _BV(ISC00) ; //ISC00 est le régistre 0. Logical change = interrupt request
	
	// sei permet de recevoir a nouveau des interruptions.
	sei ();
}

int main() {
	initialisation();
	
	for (;;){
		switch(etat) {
			case rougeRelacher: {
				PORTB = 0x01;
				break;
			}

			case ambreAppuyer: {
				PORTB = 0x01; //Rouge
				_delay_ms(5);
				PORTB = 0x02; //Vert
				_delay_ms(25);	
				break;
			}

			case vertRelacher: {
				PORTB = 0x02;
				break;
			}

			case rougeAppuyer: {
				PORTB = 0x01;
				break;
			}

			case eteint:{
				PORTB = 0x00;
				break;
			}

			case vertAppuyer: {
				PORTB = 0x02;
				break;
			}
			default:
				PORTB=0x02;
		}
	}
}