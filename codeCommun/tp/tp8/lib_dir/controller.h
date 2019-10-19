/*
*Fichier: controller.h
*Auteur(s): Wajiha BADIROU, Zouhair CHIGUER, Louis CORMIER, Dogbéda Georges GNAGA
*Date de creation: 10 mars 2017
*Date de modification: 10 mars 2017 par Wajiha BADIROU, Zouhair CHIGUER, Louis CORMIER, Dogbéda Georges GNAGA
*Description: Classe avec des fonctions générales
*/
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <avr/io.h> 
#include <util/delay.h>


class Controller  {

public: 

Controller();
~Controller();

bool estAppuyer ();

void delay(uint16_t temps);

};

#endif
