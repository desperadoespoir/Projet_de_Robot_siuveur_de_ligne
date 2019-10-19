#ifndef ROBOT_H
#define ROBOT_H

#include <avr/io.h> 
#include <stdint.h>
#include <avr/interrupt.h>
#define 	F_CPU   8000000UL
#include "CapteurCytron.h"
#include "Bouton.h"
#include "can.h"
#include "Del.h"
#include "Moteur.h"
#include "Son.h"
#include "Minuterie.h"
#include "EtatDel.h"

#define CAPTEUR1 0x01
#define CAPTEUR2 0x02
#define CAPTEUR3 0x04
#define CAPTEUR4 0x08
#define CAPTEUR5 0x10
#define CAPTEUR1_2 0x03
#define CAPTEUR1_2_3 0x07
#define CAPTEUR1_2_3_4 0x0F
#define CAPTEUR1_2_3_4_5 0x1F
#define CAPTEUR1_3 0x05
#define CAPTEUR3_5 0x14
#define CAPTEUR2_3 0x06
#define CAPTEUR3_4 0x0C
#define CAPTEUR3_4_5 0x1C 
#define CAPTEUR4_5 0x18

#define AVANCER 0x00
#define RECULER 0x03
#define TDROITE 0x02
#define TGAUCHE 0x01

enum DirectionLumiere {gauche, droite, aucun};

class Robot {
public:
	Robot();

	//Getter
	EtatDel getEtat();
    uint8_t getCapteurs();
    Moteur getMoteur();
    DirectionLumiere getDirectionLumiere();
    bool lireCapteurs();
	
    //Setter
    void setDirectionLumiere(DirectionLumiere directionLumiere);

	//Bouton poussoirs
	bool boutonChangerEstAppuyer();
	bool boutonSelectionnerEstAppuyer();
	bool estInteruptAppuyer();
	
	//Choix couleur
	void changerCouleur();

	//Minuterie
	//void partirMinuterie(uint16_t duree);
	//uint8_t getMinuterieEstExpiree();

	//Capteur lumière
	DirectionLumiere choisirDirectionLumiere();

	//Controle moteurs
	void suivreLigneDroite(uint8_t vLigne, uint8_t vVirage);
	void suivreLigneDroiteD(uint8_t vLigne, uint8_t vVirage);
	void arreter();
	void virage90G(uint8_t temps);
	void virage90D(uint8_t temps);
	void virage180G(uint8_t vGauche, uint8_t vDroite);
	void virage180D(uint8_t vGauche, uint8_t vDroite);
	void trajetSectionUn(uint8_t vLigne, uint8_t vVirage, uint8_t& compteurLignes);
	void trajetSectionDeux(uint8_t vLigne, uint8_t vVirage, uint8_t& compteurLignes);
	void trajetSectionPointillee(uint8_t vLigne, uint8_t vVirage, uint8_t& compteurLignes);
	void trajetDerniereSection(uint8_t vLigne, uint8_t vVirage, uint8_t& compteurLignes);

    void tournerSurPlaceG(uint8_t vGauche, uint8_t vDroite);
    void tournerSurPlaceD(uint8_t vGauche, uint8_t vDroite);
    void virageGauche();
    void virageDroite();
	void compteurRotation540(uint8_t& compteurLignes);

private:
	CapteurCytron capteurCytrus_;
	Bouton bouton_;
	Bouton bouton2_;
	Del del_;
	Moteur moteur_; 
	Minuterie minuterie_;
	EtatDel etatDel_;
	DirectionLumiere directionLumiere_;
};

#endif
