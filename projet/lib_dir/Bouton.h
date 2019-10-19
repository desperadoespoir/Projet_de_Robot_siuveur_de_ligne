#ifndef BOUTON_H
#define BOUTON_H

#include <avr/io.h> 
#include <stdint.h>
#include <util/delay.h>
#include <util/delay_basic.h>
#include <avr/interrupt.h>

class Bouton {
public:
	bool changerEstAppuyer();
	bool selectionnerEstAppuyer();
private:
};

#endif