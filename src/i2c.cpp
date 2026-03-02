#include "i2c.h"
#include <avr/delay.h>
#include <avr/io.h>
#include <avr/iom2560.h>
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
}

void I2C::start() {
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
  while (!(TWCR & (1 << TWINT)))
    ;
}

void I2C::write(unsigned char data) {
  TWDR = data;
  TWCR = (1 << TWINT) | (1 << TWEN);
  while (!(TWCR & (1 << TWINT)))
    ;
}

void I2C::stop() { TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO); }

unsigned char I2C::read(unsigned char isLast) {
  // if not last byte to read
  if (isLast == 0) {
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
  } else {
    TWCR = (1 << TWINT) | (1 << TWEN);
  }
  while ((TWCR & (1 << TWINT)) == 0) {
  }
  return TWDR;
}
