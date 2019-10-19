/*
*Fichier: pb2.cpp
*Auteur(s): Louis CORMIER, Dogbéda Georges GNAGA
*Date de creation: 7 février 2017
*Date de modification: 7 février 2017 par Louis CORMIER, Dogbéda Georges GNAGA
*Description: Jeu de réflexe	
*/

#include <avr/io.h> 
#include <stdint.h>
#define 	F_CPU   8000000UL
#include <util/delay.h>
#include <util/delay_basic.h>
#include <avr/interrupt.h>

volatile uint8_t minuterieExpiree;
volatile uint8_t boutonPoussoir;

ISR ( TIMER1_COMPA_vect ) { //interruption du timer
	minuterieExpiree = 1;
}

ISR ( INT0_vect ) { //interruption par poussoir
	_delay_ms(30);
	boutonPoussoir = 1;
	// anti-rebond
	EIFR |= (1 << INTF0); 
}

void initialisation ( void ) {
	cli ();
	DDRB = 0xff;
	DDRD = 0x00;
	EIMSK |= _BV(INT0);
	EICRA |= _BV(ISC00) ; //ISC00 est le régistre 0. Logical change = interrupt request
	sei ();
	PORTB = 0x00;
}

void partirMinuterie ( uint16_t duree ) {
	minuterieExpiree = 0;
	// mode CTC du timer 1 avec horloge divisee par 1024
	// interruption apres la duree specifiee
	TCNT1 = 0 ;
	OCR1A = duree;
	TCCR1A = 0x04 ; //0x04 donne CTC
	TCCR1B = 0x05 ; //0x05 clck/1024      Prescale
	TCCR1C = 0;
	TIMSK1 = _BV(OCIE1A) ;
}

int main() {
	initialisation();
	_delay_ms(10000);
	PORTB=0x01;
	_delay_ms(100);
	PORTB=0x00;
	partirMinuterie(0x1E84>>1); //8000000/1024		fréquence processeur

	do {
	// attendre qu'une des deux variables soit modifiee
	// par une ou l'autre des interruptions.
	} while ( minuterieExpiree == 0 && boutonPoussoir == 0 );

	// Une interruption s'est produite. Arreter toute
	// forme d'interruption. Une seule reponse suffit.
	cli ();
	// Verifier la reponse
	if(boutonPoussoir==1) 
		PORTB=0x02;
		
	else 
		PORTB=0x01;	
		
	return 0;

}