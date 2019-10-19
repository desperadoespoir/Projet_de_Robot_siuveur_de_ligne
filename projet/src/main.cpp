#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include "Robot.h"
#include "can.h"
#include "controller.h"
#include "Son.h"
#include "Minuterie.h"




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
#define CAPTEUR2_3_4_5 0x1E
#define CAPTEUR3_4 0x0C
#define CAPTEUR3_4_5 0x1C

#define AUCUN_CHOIX 0x00
#define DIRECTION_DROITE 0x01
#define DIRECTION_GAUCHE 0x02

#define NOMBRE_OCCURENCES_CHEMIN_LUMIERE 2

volatile uint8_t boutonInterrupt;

ISR (INT0_vect) {
	_delay_ms ( 30 );
	boutonInterrupt = true;
	EIFR |= (1 << INTF0) ;
}

int main(){
	Robot robot;
	Del del;
	Minuterie minuterie;
	boutonInterrupt = false;
	Moteur moteur;
	Son son;

	DDRA = 0x00;



	//Choisir la couleur
	while (robot.getEtat() == eteint){
		if(robot.boutonChangerEstAppuyer()){
			robot.changerCouleur();
		}
	}


	bool couleurChoisi = false;
	while(!couleurChoisi){
		if(robot.boutonChangerEstAppuyer())
			robot.changerCouleur();

		if(robot.boutonSelectionnerEstAppuyer()){
			couleurChoisi = true;
		}
	}
	_delay_ms(4000);
	
	//Direction Section 1
	
	minuterie.partirMinuterie();
	do{
		robot.tournerSurPlaceD(140, 130);
		robot.lireCapteurs();
	}
	while(robot.getCapteurs() !=0x00);
	robot.tournerSurPlaceG(0,0);

	do{
		robot.tournerSurPlaceD(140, 130);
		robot.lireCapteurs();
	}
	while(robot.getCapteurs() !=CAPTEUR3);
	robot.arreter();
	uint8_t tempsRotation = minuterie.getMinuterieEstExpiree();
	_delay_ms(1000);
	
	//Obtenir le temps pour faire une ligne
	uint8_t compteurLignes = 0;
	do{
		robot.trajetSectionUn(120, 110, compteurLignes);
	}
	while(compteurLignes != 2);


	//SECTION AB
	minuterie.partirMinuterie();
	do{
		robot.trajetSectionUn(120, 110, compteurLignes);
	}
	while(compteurLignes != 3);

	//OBTENIR LE TEMPS ENTRE DEUX LIGNES
	uint8_t tempsEntreDeuxLignes = minuterie.getMinuterieEstExpiree();

	//Chemin selon Etat
	uint8_t ligneMax = 0;
	switch(robot.getEtat()){
		case(vert):
			ligneMax = 4;
			break;
		case(rouge):
			ligneMax = 7;
			break;
		default:
			break;
	}

	do{
		robot.trajetSectionUn(120, 110, compteurLignes);
	}
	while(compteurLignes != ligneMax);
	robot.arreter();
	
	//Se rendre à la zone de parking
	minuterie.partirMinuterie();
	while(minuterie.getTemps() < (7*tempsEntreDeuxLignes/2)){
		robot.suivreLigneDroite(120, 110);
	}
	minuterie.arreterTimer();
	robot.arreter();
	
	//Rotation
	robot.virage90D(tempsRotation/2);
	robot.arreter();
	moteur.tournermoteur(180,180, RECULER);
	_delay_ms(2500);
	robot.arreter();
	_delay_ms(2500);
	son.jouerSon(50);
	_delay_ms(1000);
	son.arreterSon();

	
	//EN ATTENTE DU INTERRUPT

	while(!boutonInterrupt){
	}
	boutonInterrupt = false;
	
	robot.virage180G(120,120);

	

	//SECTION BC
	compteurLignes = 0;
	switch(robot.getEtat()){
		case(vert):
			do{
				robot.trajetSectionDeux(120, 110, compteurLignes);
			}
			while(compteurLignes!=3);
			robot.arreter();
			_delay_ms(1500);
			do{robot.tournerSurPlaceG(120,160);
				robot.lireCapteurs();
			}
			while(robot.getCapteurs() != 0);
			robot.arreter();
			while(robot.getCapteurs() != CAPTEUR1_2_3_4_5){
				robot.suivreLigneDroite(120, 110);
				robot.lireCapteurs();
			}
			//robot.virage180G(120, 160);
			break;
		case(rouge):
			do{
				robot.trajetSectionDeux(120, 110, compteurLignes);
			}
			while(compteurLignes!=5);
			robot.arreter();
			_delay_ms(1500);
			do{robot.tournerSurPlaceG(120,160);
				robot.lireCapteurs();
			}
			while(robot.getCapteurs() != CAPTEUR5);
			robot.arreter();
			while(robot.getCapteurs() != 0x00){
				robot.suivreLigneDroite(120, 110);
				robot.lireCapteurs();
			}
			robot.arreter();
			while(robot.getCapteurs() != CAPTEUR3){
					robot.tournerSurPlaceG(110,110);
					robot.lireCapteurs();
			}
			robot.arreter();
			while(robot.getCapteurs() != CAPTEUR1_2_3_4_5){
				robot.suivreLigneDroiteD(120, 110);
				robot.lireCapteurs();
			}
			//robot.virage180D(120, 160);
			break;
		default:
			break;
	}
	
	robot.arreter();
	_delay_ms(2000);
	

	//SECTION ROTATION 540
	//Positionnement
	while(robot.getCapteurs() != CAPTEUR3_4_5 && robot.getCapteurs() != CAPTEUR5){
		robot.suivreLigneDroite(130,110);
		robot.lireCapteurs();
	}
	robot.arreter();
	_delay_ms(2000);
	while(robot.getCapteurs() != 0x00){
		moteur.tournermoteur(130,130, AVANCER);
		robot.lireCapteurs();
	}
	while(robot.getCapteurs() == 0x00){
		moteur.tournermoteur(130,130, AVANCER);
		robot.lireCapteurs();
	}
	_delay_ms(2000);
	robot.arreter();
	_delay_ms(2000);
	do{robot.tournerSurPlaceD(110,110);
		robot.lireCapteurs();}
	while(robot.getCapteurs()!=0);

	do{robot.tournerSurPlaceD(110,110);
		robot.lireCapteurs();}
	while(robot.getCapteurs()!=CAPTEUR4);
	robot.arreter();
	_delay_ms(2000);
	robot.tournerSurPlaceG(140,160);
	compteurLignes = 0;
	while(compteurLignes != 9){
		robot.compteurRotation540(compteurLignes);
	}
	robot.arreter();
	_delay_ms(200);
	
	
	//DIRECTION POINT E
	uint8_t valeurCapteur;
	
	while(valeurCapteur != CAPTEUR2_3_4_5 && valeurCapteur != CAPTEUR3_4_5 && valeurCapteur != CAPTEUR1_2_3_4_5){
		robot.suivreLigneDroiteD(120, 120);
		robot.lireCapteurs();
		valeurCapteur = robot.getCapteurs();
	}
	moteur.tournermoteur(120,110, AVANCER);
	_delay_ms(5000);
	robot.arreter();
	_delay_ms(2000);
	while (robot.getCapteurs() != CAPTEUR5 && robot.getCapteurs() != CAPTEUR4_5 && robot.getCapteurs() != CAPTEUR3){
		robot.tournerSurPlaceD(100,110);
		robot.lireCapteurs();
		valeurCapteur = robot.getCapteurs();
	}
	while (robot.getCapteurs() != CAPTEUR1_2 && robot.getCapteurs() != CAPTEUR1_2_3 && robot.getCapteurs()!= CAPTEUR1_2_3_4){
		robot.suivreLigneDroite(130, 130);
		robot.lireCapteurs();
		valeurCapteur = robot.getCapteurs();
	}
	moteur.tournermoteur(130,130, AVANCER);
	_delay_ms(4000);
	robot.arreter();
	_delay_ms(4000);
	valeurCapteur = 0x00;
	while(valeurCapteur != CAPTEUR2 && valeurCapteur != CAPTEUR2_3){
		robot.tournerSurPlaceG(130,100);
		robot.lireCapteurs();
		valeurCapteur = robot.getCapteurs();
	}
	

	// section fourches capteurs breadboard

	uint8_t choixDirectionLumiere = AUCUN_CHOIX;
	for(int i = 0; i < NOMBRE_OCCURENCES_CHEMIN_LUMIERE; i++){
		valeurCapteur = 0x00;
		while(valeurCapteur != CAPTEUR1_2_3_4_5){
			robot.suivreLigneDroite(120, 110);
			robot.lireCapteurs();
			valeurCapteur = robot.getCapteurs();
		}
		robot.arreter();
		choixDirectionLumiere = AUCUN_CHOIX;
		boutonInterrupt = false;
		while(!boutonInterrupt){
			boutonInterrupt = false;
			can convertisseurAnalogiqueNumerique; //Constructeur d'un object convertisseurAnalogiqueNumerique
			uint16_t valeurDeLectureD = convertisseurAnalogiqueNumerique.lecture(0x00);
			uint8_t valeur8bitsD = valeurDeLectureD >> 2;
			uint16_t valeurDeLectureG = convertisseurAnalogiqueNumerique.lecture(0x01); //lecture sur portB sur la pinA
			uint8_t valeur8bitsG = valeurDeLectureG >> 2; //Retire les deux derniers bits et place la valeurs dans une variable à 8 bits
			if (valeur8bitsD > 250){
				choixDirectionLumiere = DIRECTION_DROITE;
			}
			else if (valeur8bitsG > 250){
				choixDirectionLumiere = DIRECTION_GAUCHE;
			}
		}
		boutonInterrupt = false;
	
		if(choixDirectionLumiere == DIRECTION_DROITE){
			valeurCapteur = 0x00;
			moteur.tournermoteur(130,130,AVANCER);
			_delay_ms(6000);// UTILISER LE CODE COMMENTER LORSQUE CODE COMPLET
			/*minuterie.partirMinuterie();
			while(minuterie.getTemps() < (3*tempsEntreDeuxLignes/2)){
				moteur.tournermoteur(140,140,AVANCER);
			}
			minuterie.arreterTimer();
			*/

			while (robot.getCapteurs() != CAPTEUR4 && robot.getCapteurs() != CAPTEUR3_4 && robot.getCapteurs() != CAPTEUR3){
				robot.tournerSurPlaceD(120,140);
				robot.lireCapteurs();
				valeurCapteur = robot.getCapteurs();
			}
			robot.arreter();
			_delay_ms(2000);
			moteur.tournermoteur(140,140,AVANCER);
			_delay_ms(8000); //ENCORE UNE FOIS UTILISER LE CODE COMMENTÉ
			/*minuterie.partirMinuterie();
			while(minuterie.getTemps() < (3*tempsEntreDeuxLignes/2)){
				moteur.tournermoteur(140,140,AVANCER);
			}
			minuterie.arreterTimer();*/
			robot.arreter();
			_delay_ms(2000);
			//robot.virage90G(tempsRotation/2);
			robot.virage90G(32);
			_delay_ms(2000);
			robot.lireCapteurs();
			while(robot.getCapteurs() == 0x00){
				moteur.tournermoteur(140,140,AVANCER);
				robot.lireCapteurs();
			}
			robot.arreter();
		}
		else if(choixDirectionLumiere == DIRECTION_GAUCHE){
			valeurCapteur = 0x00;
			moteur.tournermoteur(140,140,AVANCER);
			_delay_ms(6000);// UTILISER LE CODE COMMENTER LORSQUE CODE COMPLET
			/*minuterie.partirMinuterie();
			while(minuterie.getTemps() < (3*tempsEntreDeuxLignes/2)){
				moteur.tournermoteur(140,140,AVANCER);
			}
			minuterie.arreterTimer();*/
			while (robot.getCapteurs() != CAPTEUR2 && robot.getCapteurs() != CAPTEUR2_3 && robot.getCapteurs() != CAPTEUR3){
				robot.tournerSurPlaceG(120,140);
				robot.lireCapteurs();
				valeurCapteur = robot.getCapteurs();
			}
			robot.arreter();
			_delay_ms(2000);
			moteur.tournermoteur(140,140,AVANCER);
			_delay_ms(8000); //ENCORE UNE FOIS UTILISER LE CODE COMMENTÉ
			/*minuterie.partirMinuterie();
			while(minuterie.getTemps() < (3*tempsEntreDeuxLignes/2)){
				moteur.tournermoteur(140,140,AVANCER);
			}
			minuterie.arreterTimer();*/
			robot.arreter();
			_delay_ms(2000);
			//robot.virage90G(tempsRotation/2);
			robot.virage90D(32);
			_delay_ms(2000);
			robot.lireCapteurs();
			while(robot.getCapteurs() == 0x00){
				moteur.tournermoteur(120,120,AVANCER);
				robot.lireCapteurs();
			}
			robot.arreter();
		}
	}
	_delay_ms(2000);
	robot.lireCapteurs();
	while(robot.getCapteurs() ==0x00){
		if(choixDirectionLumiere == DIRECTION_DROITE)
			robot.suivreLigneDroiteD(120,110);
		else if(choixDirectionLumiere == DIRECTION_GAUCHE)
			robot.suivreLigneDroite(120,110);
		robot.lireCapteurs();
	}

	robot.lireCapteurs();
	while(robot.getCapteurs() !=0x00){
		robot.suivreLigneDroite(120,110);
	}
	robot.arreter(); 
	uint8_t compteurEspacesVides = 0;
	son.jouerSon(45);
	while(compteurEspacesVides != 5){
		robot.trajetSectionPointillee(120,110,compteurEspacesVides);
	}
	son.arreterSon();
	robot.arreter();
	

	// Derniere section
	compteurLignes=0;
	while(compteurLignes!=2){
		robot.trajetDerniereSection(120,120,compteurLignes);
	}
	
	moteur.tournermoteur(130,130,AVANCER);
	_delay_ms(1000);
	robot.arreter();

	while(robot.getCapteurs()!= CAPTEUR1 && robot.getCapteurs()!= CAPTEUR1_2){
		robot.tournerSurPlaceG(110,120);
		robot.lireCapteurs();
	}
	minuterie.partirMinuterie();
	while(robot.getCapteurs()!= 0x00){
		robot.suivreLigneDroite(150,110);
		robot.lireCapteurs();
	}
	uint8_t tempsStationnement = minuterie.getMinuterieEstExpiree();
	robot.arreter();
	
	boutonInterrupt = false;
	while(!boutonInterrupt){
	}
	
	//Stationnement
	
	if(robot.getEtat() == vert){
		minuterie.partirMinuterie();	
		while(minuterie.getTemps() < (tempsStationnement/2)){
			moteur.tournermoteur(150,150,AVANCER);
		}
		robot.arreter();
		minuterie.arreterTimer();
		minuterie.partirMinuterie();
		while(minuterie.getTemps()<tempsStationnement/2){
			moteur.tournermoteur(150,0,AVANCER);
		}
		
	}
	else if(robot.getEtat() == rouge){
		minuterie.partirMinuterie();	
		while(minuterie.getTemps() < (tempsStationnement/2)){
			moteur.tournermoteur(145,160,AVANCER);
		}
		robot.arreter();
		minuterie.arreterTimer();
		minuterie.partirMinuterie();
		while(minuterie.getTemps()<tempsStationnement/2){
			moteur.tournermoteur(0,170,AVANCER);
		}
		
	}
	robot.arreter();
	minuterie.arreterTimer();
	
}

