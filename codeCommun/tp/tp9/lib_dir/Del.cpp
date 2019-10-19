/*
*Fichier: Del.cpp
*Auteur(s): Wajiha BADIROU, Zouhair CHIGUER, Louis CORMIER, Dogbéda Georges GNAGA
*Date de creation: 10 mars 2017
*Date de modification: 10 mars 2017 par Wajiha BADIROU, Zouhair CHIGUER, Louis CORMIER, Dogbéda Georges GNAGA
*Description: La del sur le robot
*/

#include "Del.h"

/****************************************************************************
* Fonction: Del
* Description : constructeur par défaut
* Paramètres: aucun
* Retour: aucun
****************************************************************************/
Del::Del() : port_(B){}

/****************************************************************************
* Fonction: Del
* Description : Constructeur par paramètre
* Paramètres: TypePort& : Le type du port
* Retour: aucun
****************************************************************************/
Del::Del(TypePort& type) : port_(type){}

/****************************************************************************
* Fonction: ~Del 
* Description : Destructeur
* Paramètres: aucun
* Retour: aucun
****************************************************************************/
Del::~Del(){}

/****************************************************************************
* Fonction: void allumerRouge
* Description : allume la lumière en rouge
* Paramètres: aucun
* Retour: aucun
****************************************************************************/
void Del::allumerRouge(){
	switch(port_){
		case A : PORTA = 0x01;
		case B : PORTB = 0x01;
		case C : PORTC = 0x01;
		case D : PORTD = 0x01;
	}
}

/****************************************************************************
* Fonction: void allumerVert
* Description : allume la lumière en vert
* Paramètres: aucun
* Retour: aucun
****************************************************************************/
void Del::allumerVert(){
	switch(port_){
		case A : PORTB = 0x02;
		case B : PORTB = 0x02;
		case C : PORTC = 0x02;
		case D : PORTD = 0x02;
	}
}

/****************************************************************************
* Fonction: void allumerAmbre
* Description : allume la lumière en ambre
* Paramètres: aucun
* Retour: aucun
****************************************************************************/
void Del::allumerAmbre(){
	switch(port_){
		case A : {
			PORTA = 0x01;
			_delay_ms(5);
			PORTA = 0x02;
			_delay_ms(25);
		}
		case B : {
			PORTB = 0x01;
			_delay_ms(5);
			PORTB = 0x02;
			_delay_ms(25);
		}
		case C : {
			PORTC = 0x01; //Rouge
			_delay_ms(5);
			PORTC = 0x02; //Vert
			_delay_ms(25);
		}
		case D : {
			PORTD = 0x01; //Rouge
			_delay_ms(5);
			PORTD = 0x02; //Vert
			_delay_ms(25);
		}
	}
}

/****************************************************************************
* Fonction: void enteindreDel
* Description : enteindre la lumière
* Paramètres: aucun
* Retour: aucun
****************************************************************************/
void Del::eteindreDel(){
	switch(port_){
		case A : PORTB = 0x00;
		case B : PORTB = 0x00;
		case C : PORTC = 0x00;
		case D : PORTD = 0x00;
	}
}