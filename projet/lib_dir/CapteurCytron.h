/*
*Fichier: CapteurCytron.cpp
*Auteur(s): Wajiha BADIROU, Zouhair CHIGUER, Louis CORMIER, Dogbéda Georges GNAGA
*Date de creation: 4 avril 2017
*Date de modification: 4 avril 2017 par Wajiha BADIROU, Zouhair CHIGUER, Louis CORMIER, Dogbéda Georges GNAGA
*Description: Lit et renvoie les capteurs actifs
*/

#ifndef CAPTEURCYTRON_H
#define CAPTEURCYTRON_H

#include <avr/io.h> 
#include <stdint.h>
#include <avr/interrupt.h>
#include "TypePort.h"

class CapteurCytron{
public:
	CapteurCytron();
    uint8_t lecture();
    
private:
    uint8_t recepteur_;
};

#endif
