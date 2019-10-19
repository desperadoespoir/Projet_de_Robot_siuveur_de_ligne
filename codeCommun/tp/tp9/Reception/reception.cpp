#define F_CPU 8000000UL
#include <avr/io.h>
#include <stdint.h>
#include <util/delay_basic.h>
#include <util/delay.h>
#include "memoire_24.h"

void initialisationUART ( void ) {

	// 2400 bauds. Nous vous donnons la valeur des deux
	// premier registres pour vous éviter des complications
	UBRR0H = 0;
	UBRR0L = 0xCF;
	// permettre la reception et la transmission par le UART0
	UCSR0A = 0x00;  //'modifier ici' 3 flags bits
	UCSR0B = 0x18; // bit 3-4,  rx enable, tx enable
	// Format des trames: 8 bits, 1 stop bits, none parity
	UCSR0C = 0x06;

}

uint8_t USART_Receive(void){ // De l'USART vers le PC 
	while (!(UCSR0A & (1 << RXC0))){ //Attend que l'information soit reçu

	}
	return UDR0; //Prend l'information et la retourne
}
	
int main(){
	initialisationUART();
	Memoire24CXXX memoire;
	uint8_t temp[2];
	for(int i = 0; i < 2; i++){
		temp[i] = USART_Receive(); //recoit le nombre d'octets à mettre sur la mémoire
	}

	uint16_t nOctets= temp[0];
	nOctets<<8; //décaler les 8 bits du nombre d'octets pour faire de l'espace pour les 8 prochain bits
	nOctets += temp[1];

	uint8_t informations[nOctets];
	
	informations[0] = temp[0]; 	//ajout de la première information
	informations[1] = temp[1];	//ajout de la seconde information

	for (unsigned int i = 2; i < nOctets; i++){
		informations[i] = USART_Receive(); //ajout du reste des informations
	}

	const uint8_t depart = 0x00;
	memoire.ecriture(depart, informations, nOctets); //ecriture des informations dans la memoire
}

