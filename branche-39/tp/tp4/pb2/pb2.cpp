#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

int main()
{

DDRB = 0xff; //PORT B est en mode sorie

PORTB = 0;

// Puissance de 0%
for( int i=0; i<125; i++){
            for (int j=0; j<0 ; j++){
                PORTB=1;
                _delay_ms(1);
                }
            for (int j=0; j<16;j++){
                PORTB=0;
                _delay_ms(1);
                }
}
// Puissance de 25%
for( int i=0; i<125; i++){
            for (int j=0; j<4 ; j++){
                PORTB=1;
                _delay_ms(1);
                }
            for (int j=0; j<12;j++){
                PORTB=0;
                _delay_ms(1);
                }
}
// Puissance de 50%
for( int i=0; i<125; i++){
            for (int j=0; j<8 ; j++){
                PORTB=1;
                _delay_ms(1);
                }
            for (int j=0; j<8;j++){
                PORTB=0;
                _delay_ms(1);
                }
}
// Puissance de 75%
for( int i=0; i<125; i++){
            for (int j=0; j<12 ; j++){
                PORTB=1;
                _delay_ms(1);
                }
            for (int j=0; j<4;j++){
                PORTB=0;
                _delay_ms(1);                
                }
}                
// Puissance de 100%
for( int i=0; i<125; i++){
            for (int j=0; j<16 ; j++){
                PORTB=1;
                _delay_ms(1);
                }
            for (int j=0; j<0;j++){
                PORTB=0;
                _delay_ms(1);
                }
}
// Puissance de 00%
for( int i=0; i<800; i++){
            for (int j=0; j<0 ; j++){
                PORTB=1;
                _delay_us(1);
                }
            for (int j=0; j<2500;j++){
                PORTB=0;
                _delay_us(1);
                }
}                
// Puissance de 25%
for( int i=0; i<800; i++){
            for (int j=0; j<750 ; j++){
                PORTB=1;
                _delay_us(1);
                }
            for (int j=0; j<1750;j++){
                PORTB=0;
                _delay_us(1);
                }
}                
// Puissance de 50%
for( int i=0; i<800; i++){
            for (int j=0; j<1250 ; j++){
                PORTB=1;
                _delay_us(1);
                }
            for (int j=0; j<1250;j++){
                PORTB=0;
                _delay_us(1);
                }
}                
// Puissance de 75%
for( int i=0; i<800; i++){
            for (int j=0; j<1750 ; j++){
                PORTB=1;
                _delay_us(1);
                }
            for (int j=0; j<750;j++){
                PORTB=0;
                _delay_us(1);
                }
}                
// Puissance de 100%
for( int i=0; i<800; i++){
            for (int j=0; j<2500 ; j++){
                PORTB=1;
                _delay_us(1);
                }
            for (int j=0; j<0;j++){
                PORTB=0;
                _delay_us(1);
            } 
}            
   return 0;
}
