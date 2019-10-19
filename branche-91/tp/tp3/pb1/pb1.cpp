/*
*Fichier: pb1.cpp
*Auteur(s): Louis CORMIER, Dogbéda Georges GNAGA
*Date de creation: 24 janviers 2017
*Date de modification: 24 janvier 2017 par Louis CORMIER, Dogbéda Georges GNAGA
*Description: Programme qui ouvre la lumière en rouge après avoir appuyer 5 fois sur l'interrupteur
*
*Table d'états
*-------------
*	-------------------------------------------------------------------------
*	| 			| 						Poussoir							|
*	| états		| 	0		|      					1						|
*	|			|			|compteur<5	|compteur=5	| < 1s		| = 1s		|
*	|-----------|-----------|-----------|-----------|-----------|-----------|
*	| Off 		| Off 		| Off 		| On 		| X			| X			|
*	|			|			|Compteur++	|Compteur =0|			|			|
*	|-----------|-----------|-----------|-----------|-----------|-----------|
*	| On 		| X			| X			| X			| On 		| Off		|
*	|			|			|			|			|			|			|
*	-------------------------------------------------------------------------
*/

#include <avr/io.h> 
#include <util/delay.h>

/****************************************************************************
* Fonction: bool estFrontMontat(bool dernierEtat, bool etatActuel)
* Description: Vérifie si le signal de l'interrupteur est sur un front montant
* Paramètres:	- bool dernierEtat : Le signal du dernier état (IN)
*				- bool etatActuel : Le signal de l'état actuel (IN)
* Retour: (bool) Vrai si le signal est sur un front montant
****************************************************************************/
bool estFrontMontant(bool dernierEtat, bool etatActuel) {
	if (dernierEtat != etatActuel && etatActuel == true){
		_delay_ms(10);
		if (dernierEtat != etatActuel && etatActuel == true)
			return true;
	}
	return false;
}

/****************************************************************************
* Fonction: bool estFrontDescendant(bool dernierEtat, bool etatActuel)
* Description: Vérifie si le signal de l'interrupteur est sur un front descendant
* Paramètres:	- bool dernierEtat : Le signal du dernier état (IN)
*				- bool etatActuel : Le signal de l'état actuel (IN)
* Retour: (bool) Vrai si le signal est sur un front descendant
****************************************************************************/
bool estFrontDescendant(bool dernierEtat, bool etatActuel) {
	if (dernierEtat != etatActuel && etatActuel == false){
		_delay_ms(10);
		if (dernierEtat != etatActuel && etatActuel == false)
			return true;
	}
	return false;
}	

int main () {
	DDRB = 0xff;
	DDRD = 0x00;
	PORTB = 0x00;

	//Lorsque le bouton est appuyer, l'état est 1 et lorsque le bouton est relâcher il devient 0
	bool dernierEtat = PIND & 0x04; //initialisation de dernierEtat
	bool etatActuel = PIND & 0x04; //initialisation de etatActuel

	unsigned int compteur = 0;
	for (;;){
		etatActuel = PIND & 0x04;
		if (estFrontMontant(dernierEtat, etatActuel)){
			dernierEtat = etatActuel; //Changement d'état
		}

		else if (estFrontDescendant(dernierEtat, etatActuel)){
			compteur++;
			dernierEtat = etatActuel; //Changement d'état
		}

		const unsigned int NOMBRE_OCCURENCES_POUR_LUMIERE_ROUGE =  5;
		if(compteur == NOMBRE_OCCURENCES_POUR_LUMIERE_ROUGE){
			PORTB = 0x01; //Lumière rouge
			_delay_ms(1000);
			PORTB = 0x00; //Éteindre la LED
			compteur = 0;
		}
	}
	
}

