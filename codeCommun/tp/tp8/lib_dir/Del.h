/*
*Fichier: Del.h
*Auteur(s): Wajiha BADIROU, Zouhair CHIGUER, Louis CORMIER, Dogbéda Georges GNAGA
*Date de creation: 10 mars 2017
*Date de modification: 10 mars 2017 par Wajiha BADIROU, Zouhair CHIGUER, Louis CORMIER, Dogbéda Georges GNAGA
*Description: La del sur le robot
*/
#ifndef DEL_H
#define DEL_H


#include <util/delay.h>
#include <avr/io.h>

#include "TypePort.h"

class Del
{
public:
	Del();
	Del(TypePort& port);
	~Del();

	void allumerRouge();
	void allumerVert();
	void allumerAmbre();
	void eteindreDel();
private:
	TypePort port_;
};

#endif