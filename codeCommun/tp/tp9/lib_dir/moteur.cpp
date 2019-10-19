/*
*Fichier: moteur.cpp
*Auteur(s): Wajiha BADIROU, Zouhair CHIGUER, Louis CORMIER, Dogbéda Georges GNAGA
*Date de creation: 10 mars 2017
*Date de modification: 10 mars 2017 par Wajiha BADIROU, Zouhair CHIGUER, Louis CORMIER, Dogbéda Georges GNAGA
*Description: Le moteur sur le robot
*/
#include "moteur.h"

/****************************************************************************
* Fonction: Moteur
* Description : constructeur par défaut
* Paramètres: aucun
* Retour: aucun
****************************************************************************/
Moteur::Moteur(){
	TCCR1A |= (1 << WGM10) | (1 << COM1A1)|(1 << COM1B1) ;
  	TCCR1B |= (1<< CS11) ;
}

/****************************************************************************
* Fonction: ~Moteur
* Description : destructeur par défaut
* Paramètres: aucun
* Retour: aucun
****************************************************************************/
Moteur::~Moteur(){}

/****************************************************************************
* Fonction: Moteur::tournermoteur
* Description : Permet de faire fonctionner le moteur
*				Informations pour direction :
*				- Avancer : 0x00
*				- Reculer : 0x03
*				- Tourner Droite : 0x02
*				- Tourner Gauche : 0x01
* Paramètres: 	- uint8_t dureeA : La durée pour le premier moteur (in)
*				- uint8_t dureeB : La durée pour le deuxième moteur (in)
*				- uint8_t direction : La direction du robot
* Retour: aucun
****************************************************************************/
void Moteur::tournermoteur(uint8_t dureeA, uint8_t dureeB, uint8_t direction){
  
  OCR1A = dureeA ; 
  OCR1B = dureeB; 
  PORTD &= 0x3F;
  PORTD = direction << 6;
}