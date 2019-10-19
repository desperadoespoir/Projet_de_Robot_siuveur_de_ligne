//
//  TP3- Probleme 1.cpp
//  
//
//  Created by Wajiha Badirou on 17-01-26.
//
//

/****************************************************************************
 * Fichier: TP3- Probleme 1.cpp
 * Auteurs: Wajiha Bissola BADIROU 1770039
 *          Zouhair Chiguer        1848475
 * Date: 26 Janvier 2016
 * Description: Probleme 1
 *
 * Etat Present     ||    Entrée     ||    Etat suivant     ||    Sortie ( Couleur de la DEL)
 * INIT             ||       0       ||      INIT           ||     0 ( Éteinte)
 * INIT             ||       1       ||      A              ||     0 ( Éteinte)
 * A                ||       0       ||      A              ||     0 ( Éteinte)
 * A                ||       1       ||      B              ||     0 ( Éteinte)
 * B                ||       0       ||      B              ||     0 ( Éteinte)
 * B                ||       1       ||      C              ||     0 ( Éteinte)
 * C                ||       0       ||      C              ||     0 ( Éteinte)
 * C                ||       1       ||      D              ||     0 ( Éteinte)
 * D                ||       0       ||      D              ||     0 ( Éteinte)
 * D                ||       1       ||      E              ||     0 ( Éteinte)
 * E                ||       0       ||      E              ||     0 ( Éteinte)
 * E                ||       1       ||      INIT           ||     1 ( Rouge )
 ****************************************************************************/

#define F_CPU 8000000
#include <avr/io.h> 
#include <util/delay.h>



int main()
{
    DDRD = 0x00; // PORT D est en mode entree
    DDRA = 0xff; // PORT B est en mode sortie
    
    //Variables
    
    enum Etat{INIT=0,A=1,B=2,C=3,D=4,E=5};
    int etatSuivant=INIT;
    int bouton=0;   
    
    
    for(;;){ //Boucle infini 
        if(PIND & 0x04)
        { 
        _delay_ms(10);
         if(PIND & 0x04)
            while(PIND & 0x04){
                
            };
            bouton=1;
                
       }else {
           bouton=0;
           
          }
       
    switch (etatSuivant) {
        case INIT : 
        {
            if(bouton==1) {
                    etatSuivant++;
            }
                break;
        }
        case A: 
        { 
            if(bouton==1) {
                 etatSuivant++;
            }
            break;
        }
        case B:
        {    
            if(bouton==1) {
                 etatSuivant++;
                break;
            }
        }
        case C:
        {
            if(bouton==1) {
                 etatSuivant++;
                break;
            }
        }
        case D:
        {
            if(bouton==1) {
                 etatSuivant++;
            }
              break;
        }
        case E :
        {
            PORTA=2;
            _delay_ms(1000);
            PORTA=0;
            etatSuivant=INIT;
            break;
            
        }
      }
    }
    return 0;
}
