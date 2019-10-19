/* Fichier: TP7 - Probleme 2.cpp
* Auteurs : Wajiha Bissola BADIROU 1770039
*           Zouhair Chiguer        1848475
* Date : 26 Fevrier 2016
* Description : Probleme 2
****************************************************************************/


#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "can.cpp"




int main()
{
	DDRB = 0xff; // On utilise PORT B pour envoyer l'information de couleur à la LED
	DDRA = 0x00; // On utilise PORT D pour recevoir l'information du photorecepteur
	can convertisseur; // Convertisseur analogique/numerique

	for (;;) {


		uint16_t seuil = convertisseur.lecture(0);

		//intensite lumineuse faible
		if (seuil < 70) {
			PORTB = 2; // affichage couleur verte

		}
		//intensite lumineuse normale - lumiere ambiante
		else if (seuil >= 70 && seuil < 190) {
			for (int i = 0; i < 20; i++) //affichage couleur ambre
			{
				PORTB = 1;
				_delay_ms(5);
				PORTB = 2;
				_delay_ms(5);
			}
		}
		//intensite lumineuse trop forte
		else if (seuil >= 190) { 
			PORTC = 1; // affichage rouge
		}
	}

	return 0;
}


