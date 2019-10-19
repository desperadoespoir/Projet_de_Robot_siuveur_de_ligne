#include <avr/io.h>
#include <stdint.h>
#define 	F_CPU   8000000UL
#include <util/delay_basic.h>
#include <util/delay.h>
#include "Del.h"
#include "moteur.h"
#include "memoire_24.h"
#include "controller.h"
#include "Son.h"

#define DBT 0x01
#define ATT 0x02
#define DAL 0x44
#define DET 0x45
#define SGO 0x48
#define SAR 0x09
#define MAR1 0x60
#define MAR2 0x61
#define MAV 0x62
#define MRE 0x63
#define TRD 0x64
#define TRG 0x65
#define DBC 0xC0
#define FBC 0xC1
#define FIN 0xFF

int main(){
	Memoire24CXXX memoire;
	uint8_t instruction = 0x00;
	uint8_t adresse = 0x02;
	uint8_t operande;
	uint8_t compteur;
	uint8_t debutboucle;

	Del del;
	Moteur moteur;
	Controller controller;
	Son son;

	DDRB = 0xff;    
    DDRD = 0xff;

	while(instruction != 0xFF){
		memoire.lecture(adresse, &instruction); // lecture de l'instruction
		adresse++; //passer a l'adresse suivante pour la prochaine lecture
		memoire.lecture(adresse, &operande); // lecture de l'opérande
		adresse++; //passer a l'adresse suivante pour la prochaine lecture
		switch (instruction){
		case(DBT):
			//mettre instruction de début. Ne pas oublier 3 signaux de lumière
			PORTB = 0x01;
			for (unsigned int i = 0; i < 3; i++){
				del.allumerVert();
				_delay_ms(500);
				del.eteindreDel();
				_delay_ms(500);
			}
			
			break;
		case(ATT):
			//a completer
			for(unsigned int i =0; i <= operande; i++)
				_delay_ms(25);
			break;
		case(DAL):
			//a completer
			switch(operande){
			case(0x01):
				del.allumerRouge();
				break;
			case(0x02):
				del.allumerVert();
				break;
			case(0x03):
				del.allumerAmbre();
				break;
			}
			break;
		case(DET):
			del.eteindreDel(); // eteint la del
			break;
		case(SGO):
			son.jouerSon(operande);
			break;
		case(SAR):
			son.arreterSon();
			break;
		case(MAR1):
			moteur.tournermoteur(0,0, 0x00); // on arrete les deux moteurs
			break;
		case(MAR2):
			moteur.tournermoteur(0,0, 0x00); // on arrete les deux moteurs
			break;
		case(MAV):
			moteur.tournermoteur(operande, operande, 0x00); //avance

			break;
		case(MRE):
			
			moteur.tournermoteur(255,255, 0x03); //recule
			break;
		case(TRD):
			del.allumerRouge();
			moteur.tournermoteur(0,0, 0x00); // pour donner l'impulsion de depart
			moteur.tournermoteur(255,255, 0x02);
			controller.delay(5000);
			moteur.tournermoteur(0,0, 0x00);
			break;
		case(TRG):
			moteur.tournermoteur(0,0, 0x00); // pour donner l'impulsion de depart
			moteur.tournermoteur(255,255, 0x01);
			controller.delay(5000);
			moteur.tournermoteur(0,0, 0x00);
			break;
		case(DBC):
			debutboucle = adresse;
			compteur = operande;
			break;
		case(FBC):
			if(compteur >0) {
				compteur --;
				debutboucle = adresse;
			}
				
			break;
		case(FIN):
			//Pas obliger d'Avoir quelque chose, mais tu peux mettre des signaux de lumire ou un son pour indiquer la fin
			del.allumerRouge();
			_delay_ms(500);
			del.eteindreDel();
			
			break;
		}

	}
}
