/*
*Fichier: moteur.h
*Auteur(s): Wajiha BADIROU, Zouhair CHIGUER, Louis CORMIER, Dogbéda Georges GNAGA
*Date de creation: 10 mars 2017
*Date de modification: 10 mars 2017 par Wajiha BADIROU, Zouhair CHIGUER, Louis CORMIER, Dogbéda Georges GNAGA
*Description: Le moteur sur le robot
*/
#ifndef MOTEUR_H
#define MOTEUR_H

#include "controller.h"
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

#define AVANCER 0x00
#define RECULER 0x03
#define TDROITE 0x02
#define TGAUCHE 0x01

class Moteur{
public:
    Moteur();
    ~Moteur();
    void tournermoteur(uint8_t dureeA, uint8_t dureeB, uint8_t direction);

};
#endif
