#include "Bouton.h"

bool Bouton::changerEstAppuyer(){
	if(!(PINA & (1<<2))){ 	//A MODIFIER EN FONCTION DE LA BONNE PIN
		_delay_ms(100);
		if(!(PINA & (1<<2))){
			return true;
		}
	}
	return false;
}

bool Bouton::selectionnerEstAppuyer(){
	if(!(PINA & (1<<3))){ 	//A MODIFIER EN FONCTION DE LA BONNE PIN
		_delay_ms(100);
		if(!(PINA & (1<<3))){
			return true;
		}
	}
	return false;
}