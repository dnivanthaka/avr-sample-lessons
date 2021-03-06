/*
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor,
 Boston, MA  02110-1301, USA.
 
 ---
 Copyright (C) 2016, Dinusha Nivanthaka Amerasinghe <nivanthaka@gmail.com>
 */

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>

#include "uart.h"

#define BAUD 9600
#define UBRR F_CPU/16/BAUD-1

//static unsigned char sPORTB = 0;


USART uart(BAUD, 1);

uint16_t adch = 0;

void setup()
{
  //uart = new UART();
  // Setting pin0 as output
  DDRB = (1 << DDB0);
  // Enabling pull up on PORTB1
  PORTB = (1 << PORTB1);
  //PORTB = sPORTB;
  //DDRC = (0 << DDC0);
  //PORTC = (0 << PORTC0);
  
  ADMUX |= (1 << REFS0);
  //Free running mode
  //ADCSRA = (1 << ADEN | 1 << ADFR | 1 << ADIE);
  //ADCSRA |= (1 << ADEN | 1 << ADFR);
  //sei();
  ADCSRA |= (1 << ADPS2); /* ADC clock prescaler /16 */
  ADCSRA |= (1 << ADEN);  /* enable ADC */
}

ISR(ADC_vect)
{
  //adch = ADCL;
  PORTB = 1 << PORTB0;
  //ADCSRA |= 1 << ADSC;
}

int main(void)
{
  char buffer[15];
  setup();
  
  
  
  for(;;){
     ADCSRA |= 1 << ADSC;
     loop_until_bit_is_clear(ADCSRA, ADSC);
     adch = ADC;
     
     //uart.printstr(str);
     itoa(adch, buffer, 10);
     uart.printstr( (const char *)buffer );
     uart.printstr( "\n" );
     _delay_ms(100);
  }

  return 0;
}


