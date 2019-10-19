/*
*Fichier: CapteurCytron.cpp
*Auteur(s): Wajiha BADIROU, Zouhair CHIGUER, Louis CORMIER, Dogbéda Georges GNAGA
*Date de creation: 4 avril 2017
*Date de modification: 4 avril 2017 par Wajiha BADIROU, Zouhair CHIGUER, Louis CORMIER, Dogbéda Georges GNAGA
*Description: Lit et renvoie les capteurs actifs
*/

#include "CapteurCytron.h"


/****************************************************************************
* Fonction: CapteurCytron
* Description : constructeur par parametre
* Paramètres: initialisation du port C pour utilisation
* Retour: aucun
****************************************************************************/
CapteurCytron::CapteurCytron(){
        
    DDRC=0x00;  // PortC en entrée
    recepteur_ = (PINC & 0x1F); //masque des bits du capteurs

}

/****************************************************************************
* Fonction: lecture
* Description : renvoie les capteurs actifs
* Paramètres: aucun
* Retour: uint8_t : capteurs du cytran actifs
****************************************************************************/
uint8_t CapteurCytron::lecture(){
    return recepteur_;
    
}
