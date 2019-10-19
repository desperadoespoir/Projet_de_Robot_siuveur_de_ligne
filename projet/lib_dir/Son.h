#ifndef SON_H
#define SON_H

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
