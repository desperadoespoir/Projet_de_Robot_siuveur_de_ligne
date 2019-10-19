#ifndef MINUTERIE_H
#define MINUTERIE_H

#include <avr/io.h> 
#include <stdint.h>
#include <avr/interrupt.h>

class Minuterie {
public:
	Minuterie();

	uint8_t getMinuterieEstExpiree();
	uint8_t getTemps();	
	void arreterTimer();

	void partirMinuterie();
};
#endif