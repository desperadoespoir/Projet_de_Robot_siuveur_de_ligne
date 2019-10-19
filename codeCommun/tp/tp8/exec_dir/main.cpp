/*
*Fichier: main.cpp
*Auteur(s): Wajiha BADIROU, Zouhair CHIGUER, Louis CORMIER, Dogbéda Georges GNAGA
*Date de creation: 10 mars 2017
*Date de modification: 10 mars 2017 par Wajiha BADIROU, Zouhair CHIGUER, Louis CORMIER, Dogbéda Georges GNAGA
*Description: Test de la librairie
*/

#include <avr/io.h> 
#include <stdint.h>
#define F_CPU   8000000UL
#include <util/delay.h>
#include <util/delay_basic.h>
#include <avr/interrupt.h>

#include "Del.h"
#include "controller.h"
#include "moteur.h"
#include "can.h"
#include "memoire_24.h"

int main() {
	DDRB = 0xff;
	
	//test de la classe Del
	Del del;
	del.allumerVert();
	del.allumerRouge();
	del.allumerAmbre();
	del.eteindreDel();
	

	//test de la classe controller
	Controller controller;
	controller.estAppuyer();
	controller.delay(50);

	//test de la classe moteur
	Moteur moteur;
	moteur.tournermoteur(100,100);

	//test de la classe can
	can can;

	//test de la classe memoire
	Memoire24CXXX memoire;
}