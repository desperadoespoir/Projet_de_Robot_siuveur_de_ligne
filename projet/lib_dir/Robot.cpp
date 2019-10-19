#include "Robot.h"

Robot::Robot(){
	DDRA = 0x00;
	DDRB = 0xff;  
	DDRD = 0xf8;
	etatDel_ = eteint;
    moteur_ = Moteur();
    capteurCytrus_ = CapteurCytron();
    directionLumiere_ = aucun;

}

EtatDel Robot::getEtat(){
	return etatDel_;
}

uint8_t Robot::getCapteurs(){
    return capteurCytrus_.lecture();  
}

Moteur Robot::getMoteur(){
	return moteur_;
}

DirectionLumiere Robot::getDirectionLumiere(){
	return directionLumiere_;
}

bool Robot::lireCapteurs(){
 capteurCytrus_ = CapteurCytron();
 return true;
}

void Robot::setDirectionLumiere(DirectionLumiere directionLumiere){
	directionLumiere_ = directionLumiere;
}

bool Robot::boutonChangerEstAppuyer(){
	return bouton_.changerEstAppuyer();
}

bool Robot::boutonSelectionnerEstAppuyer(){
	return bouton2_.selectionnerEstAppuyer();
}

bool Robot::estInteruptAppuyer () {
	if (PIND & 0x04){
		_delay_ms(10);
		if (PIND &0x04)
			return true;
		else
			return false;
	}
	else
		return false;
}

//SELECTION COULEUR
void Robot::changerCouleur(){
	switch(etatDel_){
		case(eteint):{
			etatDel_ = vert;
			del_.allumerVert();
			break;
		}
		case(vert):{
			etatDel_ = rouge;
			del_.allumerRouge();
			break;
		}
		case(rouge):{
			etatDel_ = vert;
			del_.allumerVert();
			break;
		}
	}
}

//SECTION MINUTERIE
/*void Robot::partirMinuterie(uint16_t duree){
	minuterie_.partirMinuterie(duree);
}

uint8_t Robot::getMinuterieEstExpiree(){
	return minuterie_.getMinuterieEstExpiree();
}*/


//SÉLECTION DIRECTION SELON LUMIÈRE
DirectionLumiere Robot::choisirDirectionLumiere(){
	can convertisseurAnalogiqueNumerique;
	uint16_t valeurDeLectureDroite = convertisseurAnalogiqueNumerique.lecture(0x00); //lecture sur portB sur la pinA
	uint8_t valeurDroite8bits = valeurDeLectureDroite >> 2;
	if (valeurDroite8bits > 250){
		return droite;
	}

	uint16_t valeurDeLectureGauche = convertisseurAnalogiqueNumerique.lecture(0x01); //lecture sur portB sur la pinA
	uint8_t valeurGauche8bits = valeurDeLectureGauche >> 2;
	if (valeurGauche8bits > 250){
		return gauche;
	}

	return aucun;
}

void Robot::suivreLigneDroite(uint8_t vLigne, uint8_t vVirage){
    lireCapteurs();
	uint8_t valeurCapteur = getCapteurs();
	if(valeurCapteur!=CAPTEUR3 ){
		if(valeurCapteur ==CAPTEUR2 || valeurCapteur ==CAPTEUR2_3 )
			moteur_.tournermoteur(vVirage,vVirage-15, AVANCER);
		if (valeurCapteur ==CAPTEUR1_2 || valeurCapteur ==CAPTEUR1)
			moteur_.tournermoteur(vVirage, vVirage-30, AVANCER);
		if( valeurCapteur ==CAPTEUR4 || valeurCapteur ==CAPTEUR3_4)
	    	moteur_.tournermoteur(vVirage-15,vVirage, AVANCER);
	    if(valeurCapteur ==CAPTEUR4_5 || valeurCapteur ==CAPTEUR5)
	    	moteur_.tournermoteur(vVirage-30, vVirage, AVANCER);
	    if(valeurCapteur==0)
	  		   	tournerSurPlaceG(vVirage, vVirage+10);
		if(valeurCapteur==CAPTEUR1_2_3_4_5){
	  		moteur_.tournermoteur(vVirage,vVirage, AVANCER);
	  	}

    }
    else
    	moteur_.tournermoteur(vLigne, vLigne+10, AVANCER);
}

void Robot::suivreLigneDroiteD(uint8_t vLigne, uint8_t vVirage){
    lireCapteurs();
	uint8_t valeurCapteur = getCapteurs();
	if(valeurCapteur!=CAPTEUR3 ){
		if(valeurCapteur ==CAPTEUR2 || valeurCapteur ==CAPTEUR2_3 )
			moteur_.tournermoteur(vVirage,vVirage-15, AVANCER);
		if (valeurCapteur ==CAPTEUR1_2 || valeurCapteur ==CAPTEUR1)
			moteur_.tournermoteur(vVirage, vVirage-50, AVANCER);
		if( valeurCapteur ==CAPTEUR4 || valeurCapteur ==CAPTEUR3_4)
	    	moteur_.tournermoteur(vVirage-15,vVirage, AVANCER);
	    if(valeurCapteur ==CAPTEUR4_5 || valeurCapteur ==CAPTEUR5)
	    	moteur_.tournermoteur(vVirage-50, vVirage, AVANCER);
	    if(valeurCapteur==0)
	  		   	tournerSurPlaceD(vVirage+10, vVirage);
		if(valeurCapteur==CAPTEUR1_2_3_4_5){
	  		moteur_.tournermoteur(vVirage,vVirage, AVANCER);
	  	}

    }
    else
    	moteur_.tournermoteur(vLigne, vLigne+10, AVANCER);
}
void Robot::arreter(){
	moteur_.tournermoteur(0, 0, AVANCER);
}

void Robot::virage90G(uint8_t temps){
	minuterie_.partirMinuterie();
	do{
		moteur_.tournermoteur(130, 140, TGAUCHE);
	}
	while (minuterie_.getTemps() < temps);
	minuterie_.arreterTimer();
	arreter();
}

void Robot::virage90D(uint8_t temps){
	minuterie_.partirMinuterie();
	do{
		moteur_.tournermoteur(140, 130, TDROITE);
	}
	while (minuterie_.getTemps() < temps);
	minuterie_.arreterTimer();
	arreter();
}

void Robot::virage180G(uint8_t vGauche, uint8_t vDroite){
	do{
		tournerSurPlaceG(vGauche, vDroite);
		lireCapteurs();
	}
	while(getCapteurs() !=0x00);
	tournerSurPlaceG(0,0);

	do{
		tournerSurPlaceG(vGauche, vDroite);
		lireCapteurs();
	}
	while(getCapteurs() !=CAPTEUR2);
	tournerSurPlaceG(0,0);
}

void Robot::virage180D(uint8_t vGauche, uint8_t vDroite){
	do{
		tournerSurPlaceD(vGauche, vDroite);
		lireCapteurs();
	}
	while(getCapteurs() !=0x00);
	tournerSurPlaceG(0,0);

	do{
		tournerSurPlaceD(vGauche, vDroite);
		lireCapteurs();
	}
	while(getCapteurs() !=CAPTEUR4);
	tournerSurPlaceG(0,0);
}

void Robot::trajetSectionUn(uint8_t vLigne, uint8_t vVirage, uint8_t& compteurLignes){
	lireCapteurs();
	uint8_t valeurCapteur = getCapteurs();
	if(valeurCapteur!=CAPTEUR3 ){
	        if(valeurCapteur ==CAPTEUR2 || valeurCapteur ==CAPTEUR2_3 )
			moteur_.tournermoteur(vVirage,vVirage-15, AVANCER);
		if (valeurCapteur ==CAPTEUR1_2 || valeurCapteur ==CAPTEUR1)
			moteur_.tournermoteur(vVirage, vVirage-30, AVANCER);
		if( valeurCapteur ==CAPTEUR4 || valeurCapteur ==CAPTEUR3_4)
	    	moteur_.tournermoteur(vVirage-15,vVirage, AVANCER);
	    if(valeurCapteur ==CAPTEUR4_5 || valeurCapteur ==CAPTEUR5)
	    	moteur_.tournermoteur(vVirage-30, vVirage, AVANCER);
	    if(valeurCapteur==0)
	  		   	tournerSurPlaceG(vVirage, vVirage+10);
	  		if(valeurCapteur==CAPTEUR1_2_3_4_5){
	  			while(valeurCapteur==CAPTEUR1_2_3_4_5){
	  				moteur_.tournermoteur(vVirage, vVirage, AVANCER);
	  				lireCapteurs();
	  				valeurCapteur = getCapteurs();
	  			}

	  			compteurLignes++;
	  		}

        }
    else
    	moteur_.tournermoteur(vLigne, vLigne, AVANCER);
}

void Robot::trajetSectionDeux(uint8_t vLigne, uint8_t vVirage, uint8_t& compteurLignes){
	lireCapteurs();
	uint8_t valeurCapteur = getCapteurs();
	if(valeurCapteur!=CAPTEUR3 ){
	    if(valeurCapteur ==CAPTEUR1_2 || valeurCapteur ==CAPTEUR1 || valeurCapteur ==CAPTEUR2 || valeurCapteur ==CAPTEUR2_3 )
	        moteur_.tournermoteur(vVirage,vVirage-40, AVANCER);
	    if(valeurCapteur ==CAPTEUR4_5 || valeurCapteur ==CAPTEUR5 || valeurCapteur ==CAPTEUR4 || valeurCapteur ==CAPTEUR3_4)
	        moteur_.tournermoteur(vVirage-40,vVirage, AVANCER);
	    if(valeurCapteur==0)
	   		tournerSurPlaceG(vVirage, vVirage+10);
		if(valeurCapteur==CAPTEUR1_2_3_4_5){
			moteur_.tournermoteur(vVirage,vVirage, AVANCER);
		}
		if(valeurCapteur ==CAPTEUR1_2_3 || valeurCapteur ==CAPTEUR1_2_3_4){
		while(valeurCapteur==CAPTEUR1_2_3 || valeurCapteur ==CAPTEUR1_2_3_4){
			moteur_.tournermoteur(vVirage, vVirage, AVANCER);
			lireCapteurs();
			valeurCapteur = getCapteurs();
		}
		compteurLignes++;
	}
    }
    else
    	moteur_.tournermoteur(vLigne, vLigne, AVANCER);
}

void Robot::trajetSectionPointillee(uint8_t vLigne, uint8_t vVirage, uint8_t& compteurLignes){
	lireCapteurs();
	uint8_t valeurCapteur = getCapteurs();
	if(valeurCapteur!=CAPTEUR3 ){
	    if(valeurCapteur ==CAPTEUR1_2 || valeurCapteur ==CAPTEUR1 || valeurCapteur ==CAPTEUR2 || valeurCapteur ==CAPTEUR2_3 )
	        moteur_.tournermoteur(vVirage,vVirage-40, AVANCER);
	    if(valeurCapteur ==CAPTEUR4_5 || valeurCapteur ==CAPTEUR5 || valeurCapteur ==CAPTEUR4 || valeurCapteur ==CAPTEUR3_4)
	        moteur_.tournermoteur(vVirage-40,vVirage, AVANCER);
	    if(valeurCapteur==0){
	  	  	moteur_.tournermoteur(vLigne, vLigne, AVANCER);
	  	  	while(valeurCapteur==0){
	  			moteur_.tournermoteur(vVirage, vVirage, AVANCER);
	  			lireCapteurs();
	  			valeurCapteur = getCapteurs();
	  		}
	  		compteurLignes++;
	    }
	  	if(valeurCapteur==CAPTEUR1_2_3_4_5){
	  		moteur_.tournermoteur(vVirage,vVirage, AVANCER);
	  	}
    }
    else
    	moteur_.tournermoteur(vLigne, vLigne, AVANCER);
}

void Robot::tournerSurPlaceG(uint8_t vGauche, uint8_t vDroite){
        moteur_.tournermoteur(vGauche,vDroite,TGAUCHE);
}

void Robot::tournerSurPlaceD(uint8_t vGauche, uint8_t vDroite){
        moteur_.tournermoteur(vGauche,vDroite,TDROITE);
}

void Robot::virageGauche(){
    if(getCapteurs()==CAPTEUR3_4_5){
	moteur_.tournermoteur(50,50,TGAUCHE);
    }
}

void Robot::virageDroite(){
    if(getCapteurs()==CAPTEUR1_2_3){
	moteur_.tournermoteur(50,50,TDROITE);
    }
}

void Robot::compteurRotation540(uint8_t& compteurLignes){
	lireCapteurs();
	uint8_t valeurCapteur = getCapteurs();
	if(valeurCapteur == CAPTEUR1){
		while(valeurCapteur == CAPTEUR1){
			lireCapteurs();
			valeurCapteur = getCapteurs();
		}
		compteurLignes++;
	}		
}


void Robot::trajetDerniereSection(uint8_t vLigne, uint8_t vVirage, uint8_t& compteurLignes){
	lireCapteurs();
	uint8_t valeurCapteur = getCapteurs();
	if(valeurCapteur!=CAPTEUR3 ){
	    if(valeurCapteur ==CAPTEUR1_2 || valeurCapteur ==CAPTEUR1 || valeurCapteur ==CAPTEUR2 || valeurCapteur ==CAPTEUR2_3 )
	        moteur_.tournermoteur(vVirage,vVirage-40, AVANCER);
	    if(valeurCapteur ==CAPTEUR4_5 || valeurCapteur ==CAPTEUR5 || valeurCapteur ==CAPTEUR4 || valeurCapteur ==CAPTEUR3_4)
	        moteur_.tournermoteur(vVirage-40,vVirage, AVANCER);
	    if(valeurCapteur==0)
	   		tournerSurPlaceG(vVirage, vVirage);
		if(valeurCapteur==CAPTEUR1_2_3_4_5){
			moteur_.tournermoteur(vVirage,vVirage, AVANCER);
		}
		if(valeurCapteur ==CAPTEUR1_2_3 || valeurCapteur ==CAPTEUR1_2_3_4){
		while(valeurCapteur==CAPTEUR1_2_3 || valeurCapteur ==CAPTEUR1_2_3_4){
			moteur_.tournermoteur(vVirage, vVirage, AVANCER);
			lireCapteurs();
			valeurCapteur = getCapteurs();
		}
		compteurLignes++;
	}
    }
    else
    	moteur_.tournermoteur(vLigne, vLigne, AVANCER);
}