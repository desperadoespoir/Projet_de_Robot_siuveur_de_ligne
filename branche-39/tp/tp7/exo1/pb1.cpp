/* Fichier: TP7 - Probleme 1.cpp
* Auteurs : Wajiha Bissola BADIROU 
*           Zouhair Chiguer 
* Date : 26 Fevrier 2016
* Description : Probleme 1
****************************************************************************/            
               

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#define  F_CPU 8000000UL
#include <util/delay.h>

#define debounceTime 10

enum color { RIEN, VERT, ROUGE , AMBRE};  

volatile uint8_t minuterieExpiree;
volatile uint8_t compteur =0;

// Antirebond
bool boutonAppuye()
{
    if (PIND & 0x04)
    {
      _delay_ms(10);
      if(PIND & 0x04)
      {
          return true;
      }
    }
    return false;
}

void initialisation ( void ) {

        compteur = 0;
        
        cli ();
        
        DDRB = 0xff;
        DDRD = 0x00;
        
        
        EIMSK |= _BV(INT0);
        
        EICRA |= (1 << ISC00);
        
        sei ();
}


// On utilise le PORTB pour envoyer le code couleur à la LED.

void colorer(color c)
{
   switch (c)
   {
      case RIEN:
         {
            PORTB = 0x00;
            break;
         }
      case VERT:
         {  
            PORTB = 0x01;
            break;
         }
      case ROUGE:
         {
            PORTB = 0x02;
            break;
         }
      case AMBRE:
         {
            PORTB = 0x01;  _delay_ms(1);
            PORTB = 0x02;  _delay_ms(2);
            break;
         }      
   }
}


//Ajustement des registres pour timer1
void demarrerTimer ( uint16_t duree ) {
        minuterieExpiree = 0;
       
        TCNT1 = 0 ;
        OCR1A = duree;
        TCCR1A |= (1<< WGM01) ;
        TCCR1B |= (1 << CS12 ) | (1 << CS10) ;
        TIMSK1 = (1 << OCIE1A);         
}

//Interruption à chaque 1/10 de seconde
ISR ( TIMER1_COMPA_vect ) {
       if(compteur<120) compteur++;
       if(compteur==120 || boutonAppuye()) 
       {
            minuterieExpiree =1;
        }
}

//Interruption par appuie du bouton poussoir
ISR ( INT0_vect ) {

        if (!boutonAppuye())
        {
            demarrerTimer(781);           
        }
        EIFR = (1 << INTF0);
}

//Cette fonction permet de faire clignoter la LED avec la couleur c fournie à un interval de temps k
void blink(int16_t k, color c)
{    
    while(k>=0)
    {
        colorer(c);
        _delay_ms(25);
        colorer(RIEN);
        _delay_ms(25);
        k-=50;
    }
}

//Cette fonction permet de faire clignoter une couleur c fournie un nombre de fois avec une frequence de 2 fois par seconde
void blink1(color c, uint8_t nb)
{
	
    for(int i=1; i<=nb; i++)
    {
            colorer(c);
            _delay_ms(250);
            colorer(RIEN);
            _delay_ms(250);
    }    
}

int main(void)
{
   
         initialisation();
         do
         {        
                //Wait expiration de la minuterie ou relachement du bouton
         } while ( minuterieExpiree == 0);

         // S'il y a interruption, le processeur n'en accepte plus.
         cli ();
        
         //Faire clignoter la couleur rouge sur un intervalle de 1/2 seconde
         blink(500,ROUGE);
        
         //Etteindre la LED et attendre 2 seconde
         colorer(RIEN);
         _delay_ms(2000);
        
         //Faire clignoter la couleur rouge compteur/2 fois avec une frequence de 2 fois par seconde   
         blink1(ROUGE,compteur/2);
           
         //Mettre la LED à vert pendant une seconde 
         colorer(VERT);
         _delay_ms(1000);
         
         //Fermer la LED
         colorer(RIEN);   
  
   return 0;
}
