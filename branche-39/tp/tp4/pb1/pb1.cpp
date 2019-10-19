#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

int main()
{

DDRB = 0xff; //PORT B est en mode sorie

PORTB = 0;

for(;;){
  
  PORTB=1;
  for(int i=0;i<1500;i++) {
            for (int j=0; j< 1500-i; j++){
                PORTB=1;
                _delay_us(1);
                }
            for (int j=0; j<i;j++){
                PORTB=0;
                _delay_us(1);
                }
                
            }
  _delay_ms(1000);
  
  PORTB=2;
  for(int i=0;i<1500;i++) {
            for (int j=0; j< 1500-i; j++){
                PORTB=2;
                _delay_us(1);
                }
            for (int j=0; j<i;j++){
                PORTB=0;
                _delay_us(1);
                }
                
            }
    _delay_ms(1000);
}      
   return 0;
}
