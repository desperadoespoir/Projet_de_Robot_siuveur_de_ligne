/*
*Fichier: pb1.cpp
*Auteur(s): Louis CORMIER, Dogbéda Georges GNAGA
*Date de creation: 21 février 2017
*Date de modification: 21 février 2017 par Louis CORMIER, Dogbéda Georges GNAGA
*Description: Jeu de réflexe	
*/

#include <avr/io.h> 
#include <stdint.h>
#define 	F_CPU   8000000UL
#include <util/delay.h>
#include <util/delay_basic.h>
#include <avr/interrupt.h>
#define VITESSE_COMPTEUR 781 // Prescaler de 1024 => 8000000/1024 = 7812.5. On prend un dizième

volatile uint8_t compteur;

/****************************************************************************
* Fonction: ISR (TIMER1_COMPA_vect)
* Description : Incrémente le compteur à chaque fois que le timer expire
* Paramètres: aucun
* Retour: (bool) Vrai si le bouton est appuyé
****************************************************************************/
ISR ( TIMER1_COMPA_vect ) { //interruption du timer
	compteur++;
}

/****************************************************************************
* Fonction: voiid initialisation(void)
* Description : Initialise les données du robot
* Paramètres: aucun
* Retour: aucun
****************************************************************************/
void initialisation(void) //Initialisation des ports en entrée et sortie et la LED est éteinte.
{
	cli ();
	DDRB = 0xff;
  	DDRC = 0x00;
	sei ();
	PORTB = 0x00;
	compteur = 0;
}

/****************************************************************************
* Fonction: void partirMinuterie ( uint16_t duree)
* Description : Part la minuterie
* Paramètres: uint16_t duree : lLa durée de la minuterie
* Retour: aucun
****************************************************************************/
void partirMinuterie ( uint16_t duree ) {
	// mode CTC du timer 1 avec horloge divisee par 1024
	// interruption apres la duree specifiee
	TCNT1 = 0 ;
	OCR1A = duree;
	TCCR1A = 0; //CTC
	TCCR1B = _BV(WGM12)|_BV(CS12)|_BV(CS10) ; //clck/1024      Prescale
	TIMSK1 = _BV(OCIE1A) ;
}

/****************************************************************************
* Fonction: void fermerMinuterie
* Description : Arrête la minuterie
* Paramètres: aucun
* Retour: aucun
****************************************************************************/
void fermerMinuterie(){
	TCCR1B = _BV(WGM12)|_BV(CS10) ; //clck/1024      Prescale
}

/****************************************************************************
* Fonction: bool estAppuyer()
* Description : Vérifie si le bouton est appuyé
* Paramètres: aucun
* Retour: (bool) Vrai si le bouton est appuyé
****************************************************************************/
bool estAppuyee(){
	if(!(PINC & (1<<0))){
		_delay_ms(10);
		if(!(PINC & (1<<0))){
			return true;
		}
	}
	return false;
}


int main(){
	for (;;){
		initialisation();
		if (estAppuyee()){
			partirMinuterie(VITESSE_COMPTEUR);
			while (estAppuyee() && compteur != 120) {}
			fermerMinuterie();
			PORTB=0x02;
			_delay_ms(500);
			PORTB=0x00;	
			_delay_ms(2000);

			for (int i = 0; i < compteur; i++){
				PORTB^=0x01;
				_delay_ms(250);
			}
			PORTB=0x02;
			_delay_ms(1000);
		}
	}
}