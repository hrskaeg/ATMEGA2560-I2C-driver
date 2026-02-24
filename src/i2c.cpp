#include "i2c.h"
#include <avr/delay.h>
#include <avr/io.h>
#include <stdint.h>

#define I2C_START 0x08
#define I2C_REP_START 0x10
#define I2C_MT_SLA_ACK 0x18
#define I2C_MT_DATA_ACK 0x28
#define I2C_MR_SLA_ACK 0x40
#define I2C_MR_DATA_ACK 0x50
#define I2C_MR_DATA_NACK 0x58

void I2C::init_I2C(uint32_t clockFreq) {
  TWSR = 0x00;
  TWBR = ((F_CPU / clockFreq) - 16) / 2;
  TWCR = (1 << TWEN);
}

void I2C::start() {
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
  while (!(TWCR & (1 << TWINT)))
    ;
  if ((TWSR & 0xF8) != I2C_START)
    ERROR();
}

void I2C::write(uint8_t data) {
  TWDR = data;
  TWCR = (1 << TWINT) | (1 << TWEN);
  while (!(TWCR & (1 << TWINT)))
    ;
  if ((TWSR & 0xF8) != I2C_MR_SLA_ACK)
    ERROR();
}

void I2C::stop() { TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO); }

uint8_t I2C::read(bool sendAck) {
  TWCR = (1 << TWINT) | (1 << TWEN) | (sendAck ? (1 << TWEA) : 0);
  while (!(TWCR & (1 << TWINT)))
    ;
  if ((TWSR & 0xF8) != (sendAck ? I2C_MR_DATA_ACK : I2C_MR_DATA_NACK))
    ERROR();
  return TWDR;
}

void I2C::error(uint8_t status) {
  DDRB |= (1 << PB7); // set PB7 as output
  while (1) {
    PORTB |= (1 << PB7); // LED on
    _delay_ms(200);
    PORTB &= ~(1 << PB7); // LED off
    _delay_ms(200);
  }
}
