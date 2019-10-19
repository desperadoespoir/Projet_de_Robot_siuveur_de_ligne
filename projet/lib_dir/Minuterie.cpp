#include "Minuterie.h"

volatile uint8_t minuterieExpiree;

Minuterie::Minuterie(){
	cli ();
	EIMSK |= _BV(INT0);
	EICRA |= _BV(ISC00) ; //ISC00 est le régistre 0. Logical change = interrupt request
	sei ();
}

uint8_t Minuterie::getMinuterieEstExpiree(){
	TIMSK2 = 0; //arreter timer
	return minuterieExpiree;
}

uint8_t Minuterie::getTemps(){
	return minuterieExpiree;
}

void Minuterie::arreterTimer(){
	TIMSK2 = 0;
}

ISR ( TIMER2_COMPA_vect ) { //interruption du timer
	minuterieExpiree++;
}

void Minuterie::partirMinuterie(){
	minuterieExpiree = 0;
	// mode CTC du timer 2 avec horloge divisee par 1024
	// interruption apres la duree specifiee
	TCNT2 = 0 ;
	OCR2A = 0xFF;
	TCCR2A = 0x02 ; //0x02 donne CTC
	TCCR2B = 0x07 ; //0x07	 clck/1024      Prescale
	TIMSK2 = _BV(OCIE2A) ;
}