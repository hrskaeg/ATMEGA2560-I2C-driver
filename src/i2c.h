#pragma once
#include <stdint.h>

class I2C {
public:
  void init_I2C(uint32_t clockFreq);
  void start();
  void stop();
  void write(uint8_t data);
  uint8_t read(bool sendAck);
  void error(uint8_t status);
};
