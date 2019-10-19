#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
void initialisation(void) {


cli ();


DDRA = 0xff ; //PORT A en mode sortie
DDRB = 0xff ; // PORT B en mode sortie
DDRC = 0xff; //PORT C en mode sortie
DDRD = 0x00 ; // PORT D en mode entree
 

EIMSK |= _BV(INT0);


EICRA |= _BV(ISC00) ;


sei ();
    
}

void ajustementPWM ( unit_t A, unit_t B ) {

// mise a un des sorties OC1A et OC1B sur comparaison
// reussie en mode PWM 8 bits, phase correcte
// et valeur de TOP fixe a 0xFF (mode #1 de la table 16-5
// page 130 de la description technique du ATmega324PA)

TCCR1A |= 1 << WGM10;


OCR1A = A ;

OCR1B = B ;


// division d'horloge par 8 - implique une frequence de PWM fixe

TCCR1B = 1 << CSn1;

TCCR1C = 0;

}


int main() {
    
    initialisation ();
    
    PORTA = 2;
    for (int i =0, i <= 500, i++)
        _delay_ms(5);
    
    ajustementPWM(254,0)
    
    for (int i =0, i <=1000, i++)
        _delay_ms(5);
    
    ajustementPWM(254,254)
    
    for (int i =0, i<= 1500, i++)
        _delay_ms(5);
        
}
