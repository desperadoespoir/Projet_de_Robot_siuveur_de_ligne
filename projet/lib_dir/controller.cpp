/*
*Fichier: controller.cpp
*Auteur(s): Wajiha BADIROU, Zouhair CHIGUER, Louis CORMIER, Dogbéda Georges GNAGA
*Date de creation: 10 mars 2017
*Date de modification: 10 mars 2017 par Wajiha BADIROU, Zouhair CHIGUER, Louis CORMIER, Dogbéda Georges GNAGA
*Description: Classe avec des fonctions générales
*/
#include <avr/io.h> 
#include <util/delay.h>
#include "controller.h"

#define UNE_MILLISECONDE 1


/****************************************************************************
* Fonction: Controller
* Description : Constructeur par défaut
* Paramètres: aucun
* Retour: aucun
****************************************************************************/
Controller::Controller() {}

/****************************************************************************
* Fonction: ~Controller
* Description : Destructeur
* Paramètres: aucun
* Retour: aucun
****************************************************************************/
Controller::~Controller(){}


/****************************************************************************
* Fonction: void delay
* Description : Crée un delay d'un temps pré-définie
* Paramètres: aucun
* Retour: aucun
****************************************************************************/
void Controller::delay (uint16_t temps){
	for (uint16_t i = 0; i < temps; i++)
		_delay_ms(UNE_MILLISECONDE);
}