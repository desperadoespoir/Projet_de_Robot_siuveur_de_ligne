#include "Son.h"


/****************************************************************************
* Fonction: jouerSon
* Description : Fonction permettant de faire jouer le son sur le robot
* Paramètres: uint8_t operande : La fréquence du son
* Retour: aucun
****************************************************************************/
void Son::jouerSon(uint8_t operande){
    if (operande >= 45 || operande <= 81) {
      TCCR0A |= (1<<WGM01)|(1<<COM0A0);     // CTC mode, toggle OC0 on compare match
      TCCR0B |= (1<<CS02);                   // Start timer0 with prescaler 256
      OCR0A = floor((operande-44)*255/36);
  }
}

/****************************************************************************
* Fonction: arreterSon
* Description : arrête le son
* Paramètres: aucun
* Retour: aucun
****************************************************************************/
void Son::arreterSon(){
    TCCR0B &= ~(1<<CS02);
}