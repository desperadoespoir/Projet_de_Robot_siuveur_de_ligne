
/****************************************************************************
 * Fichier: TP3- Probleme 2.cpp
 * Auteurs: Wajiha Bissola BADIROU 1770039
 *          Zouhair Chiguer        1848475
 * Date: 26 Janvier 2016
 * Description: Probleme 2
 *
 * Etat Present     ||    Entrée     || Etat suivant        ||    Sortie ( Couleur de la DEL)
                     (Bouton Poussoir)
 * INIT             ||       0       ||      INIT           ||      ROUGE
 * INIT             ||       1       ||      AMBRE          ||      AMBRE
 * AMBRE            ||       0       ||      VERT_R         ||      VERTE
 * AMBRE            ||       1       ||      AMBRE          ||      AMBRE
 * VERT_R           ||       0       ||      VERT_R         ||      VERTE
 * VERT_R           ||       1       ||      ROUGE          ||      ROUGE
 * ROUGE            ||       0       ||      ETEINT         ||      ETEINT
 * ROUGE            ||       1       ||      ROUGE          ||      ROUGE
 * ETEINT           ||       0       ||      ETEINT         ||      ETEINT
 * ETEINT           ||       1       ||      VERT_A         ||      VERT
 * VERT_A           ||       0       ||      INIT           ||      ROUGE
 * VERT_A           ||       1       ||      VERT_A         ||      VERTE
 ****************************************************************************/


#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void initialisation(void) {
// cli est une routine qui bloque toutes les interruptions.
// Il serait bien mauvais d'etre interrompu alors que
// le microcontroleur n'est pas pret...

cli ();

// configurer et choisir les ports pour les entrees
// et les sorties. DDRx... Initialisez bien vos variables

DDRA = 0xff ; //PORT A en mode sortie
DDRB = 0xff ; // PORT B en mode sortie
DDRC = 0xff; //PORT C en mode sortie
DDRD = 0x00 ; // PORT D en mode entree
 


// cette procédure ajuste le registre EIMSK
// de ATmega324PA pour permettre les interruptions externes

EIMSK |= _BV(INT0);


// il faut sensibiliser les interruptions externes aux
// changements de niveau du bouton-poussoir
// en ajustant le registre EICRA

EICRA |= _BV(ISC00) ;


// sei permet de recevoir a nouveau des interruptions.

sei ();
}
enum Etat {INIT, AMBRE, VERT_R, ROUGE, ETEINT, VERT_A};
volatile Etat nouvelEtat = INIT;


Etat changementEtat(Etat etatProchain) {
 if(etatProchain == INIT )
	return AMBRE;
 if(etatProchain == AMBRE)
	return VERT_R;
 if(etatProchain == VERT_R)
	return ROUGE;
 if(etatProchain == ROUGE) 
	return ETEINT;
 if(etatProchain == ETEINT)
	return VERT_A;
 if (etatProchain == VERT_A)
	return INIT;
}

// placer le bon type de signal d'interruption
// a prendre en charge en argument

ISR ( INT0_vect) {

// laisser un delai avant de confirmer la reponse du
// bouton-poussoir: environ 30 ms (anti-rebond)

_delay_ms (30);


// Se souvenir ici si le bouton est presse ou relache

//if(PIND & 0x04)

// changements d'etats tels que ceux de la
// semaine precedente
	nouvelEtat = changementEtat(nouvelEtat);


// Voir la note plus bas pour comprendre cette instruction et son role

EIFR |= (1 << INTF0) ;

}


int main()
{
    
    initialisation();

    for (;; ) // boucle infini
    {
        switch (nouvelEtat) {
            case INIT :  PORTA = 2;
				break;
            case AMBRE : {
              
                   //Affichage de la couleur ambre si le bouton reste appuye
                   PORTA = 2;
                    _delay_ms(30);
                    PORTA = 1 ;
                    _delay_ms(30);
		
            }
				break;
            case VERT_R :  PORTA = 1; break;
            case ROUGE :   PORTA = 2; break;
            case ETEINT :  PORTA = 0 ; break;
            case VERT_A :  PORTA = 1; break;
            
        }
    }

    
    return 0;
    
}

