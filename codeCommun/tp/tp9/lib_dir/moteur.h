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


class Moteur{
public:
    Moteur();
    ~Moteur();
    void tournermoteur(uint8_t dureeA, uint8_t dureeB, uint8_t direction);

};
#endif