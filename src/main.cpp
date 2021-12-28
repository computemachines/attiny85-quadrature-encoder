#include <avr/interrupt.h>
#include <avr/io.h>

#include "common.h"

const int8_t quadrature_transitions[4][4] = {
  {0, 1, -1, 0},
  {-1, 0, 0, 1},
  {1, 0, 0, -1},
  {0, -1, 1, 0}
};
const bool quadrature_is_error[4][4] = {
  {0, 0, 0, 1},
  {0, 0, 1, 0},
  {0, 1, 0, 0},
  {1, 0, 0, 0}
};
volatile uint8_t last_encoded = 0;

int main() {
  DDRB  = _BV(PB0) | _BV(PB1) | _BV(PB2); // outputs
  PORTB = _BV(PB3) | _BV(PB4);       // pullups
  GIMSK = _BV(PCIE);                 // Enable Pin Change Interrupt, in General Interrupt Mask
  PCMSK = _BV(PCINT4) | _BV(PCINT3); // Enable Pin Change Interrupt 3,4, in Pin Change Interrupt Mask
  sei();                             // Enable global interrupt flag in status register

  while(true){
    // PULSE(PB0);
    // PULSE(PB1);
    // PULSE(PB2);
  }
  return 0;
}

ISR(PCINT0_vect)
{
  uint8_t new_encoded = (PINB >> PB3) & 0b11;

  bool is_error = quadrature_is_error[new_encoded][last_encoded];
  int8_t direction = quadrature_transitions[new_encoded][last_encoded];

  if(is_error == 0){
    CLEAR_IO(PB2);
  }
  if(is_error == 1){
    SET_IO(PB2);
  }
  if(direction == 1){
    PULSE(PB0);
  }
  if(direction == -1){
    PULSE(PB1);
  }

  // if(direction == 1){
  //   PULSE(PB0);
  // } else if(direction == -1){
  //   PULSE(PB1);
  // } else if(is_error){
  //   TOGGLE(PB2);
  // }

  last_encoded = new_encoded;
}