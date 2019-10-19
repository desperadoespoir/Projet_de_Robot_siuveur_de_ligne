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
Moteur::Moteur(){}

/****************************************************************************
* Fonction: ~Moteur
* Description : destructeur par défaut
* Paramètres: aucun
* Retour: aucun
****************************************************************************/
Moteur::~Moteur(){}

/****************************************************************************
* Fonction: void tournermoteur
* Description : Une fonction qui sert à faire tourner les roues
* Paramètres:	- float puissancedroite : la puissance à faire tourner la roue de droite
*				- float puissancegauche : la puissance à faire tourner la roue de gauche
* Retour: aucun
****************************************************************************/
void Moteur::tournermoteur(float puissancedroite, float puissancegauche){
        float valeurTimerGauche= ((puissancegauche/100)*255);
	float valeurTimerDroite= ((puissancedroite/100)*255);
	TCNT0 = 0;  // cpt commence a 0
	OCR0A = valeurTimerGauche;   // valeur de comparaison moteur gauche
	OCR0B = valeurTimerDroite;  // valeur de comparaison moteur droit
	TCCR0A = 0xA3; 			   // fast pwm  
	TCCR0B = 0x03;             // prescaler 1024  
}