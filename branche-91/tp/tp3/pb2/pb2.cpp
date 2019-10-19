/*
*Fichier: pb2.cpp
*Auteur(s): Louis CORMIER, Dogbéda Georges GNAGA
*Date de creation: 24 janviers 2017
*Date de modification: 24 janvier 2017 par Louis CORMIER, Dogbéda Georges GNAGA
*Description: Programme qui change les lumières selon l'état dans lequel il se trouve
*
*Table d'états
*-------------
*	-------------------------------------------------
*	|	 			|	 Poussoir (Next State)		|
*	| états			|		0		|		1		|
*	|---------------|---------------|---------------|
*	| rougeRelacher	| rougeRelacher	| ambreAppuyer	|
*	|---------------|---------------|---------------|
*	| ambreAppuyer	| vertRelacher	| ambreAppuyer	|
*	|---------------|---------------|---------------|
*	| vertRelacher	| vertRelacher	| rougeAppuyer	|
*	|---------------|---------------|---------------|
*	| rougeAppuyer	| eteint		| rougeAppuyer	|
*	|---------------|---------------|---------------|
*	| eteint		| eteint		| vertAppuyer	|
*	|---------------|---------------|---------------|
*	| vertAppuyer	| rougeRelacher	| vertAppuyer	|
*	-------------------------------------------------
*/

#include <avr/io.h> 
#define 	F_CPU   8000000UL
#include <util/delay.h>

enum Etat {rougeRelacher, ambreAppuyer, vertRelacher, rougeAppuyer, eteint, vertAppuyer};

/****************************************************************************
* Fonction: bool estAppuyer()
* Description : Vérifie si le bouton est appuyé
* Paramètres: aucun
* Retour: (bool) Vrai si le bouton est appuyé
****************************************************************************/
bool estAppuyer (){
	if (PIND & 0x04){
		_delay_ms(10);
		if (PIND &0x04)
			return true;
	}
	else
		return false;
}

int main() {
	DDRB = 0xff;
	DDRD = 0x00;
	PORTB = 0x00;
	Etat etatActuel = rougeRelacher;
	
	for (;;){
		switch(etatActuel) {
			case rougeRelacher: {
				PORTB = 0x01;
				if (estAppuyer())
					etatActuel = ambreAppuyer;
				break;
			}

			case ambreAppuyer: {
				while (PIND & 0x04){
					PORTB = 0x01; //Rouge
					_delay_ms(5);
					PORTB = 0x02; //Vert
					_delay_ms(25);	
				}
				
				etatActuel = vertRelacher;
				break;
			}

			case vertRelacher: {
				PORTB = 0x02;
				if (estAppuyer())
						etatActuel = rougeAppuyer;
				break;
			}

			case rougeAppuyer: {
				while (PIND & 0x04){
					PORTB = 0x01;
				}

				etatActuel = eteint;
				break;
			}

			case eteint:{
				PORTB = 0x00;
				if (estAppuyer()){
						etatActuel = vertAppuyer;
				}
				break;
			}

			case vertAppuyer: {
				while (PIND & 0x04){
					PORTB = 0x02;
				}
				
				etatActuel = rougeRelacher;
				break;
			}
		}
	}
}