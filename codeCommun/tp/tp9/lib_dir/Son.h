#ifndef SON_H
#define SON_H

#define F_CPU  8000000UL

#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

using namespace std;

class Son{
public: 
    
    void jouerSon(uint8_t operande);
    void arreterSon();


};

#endif
