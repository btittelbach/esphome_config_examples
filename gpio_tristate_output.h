#include "esphome.h"
using namespace esphome;

class MyTriStateOutput : public Component, public FloatOutput {
 private:
  int pin_number_ = 0;
 public:

  MyTriStateOutput(int pin_number) : pin_number_(pin_number) {}

  void setup() override {
    // This will be called by App.setup()
    pinMode(pin_number_, INPUT);
  }

  void write_state(float state) override {
    // state is the amount this output should be on, 0.0 for LOW, 0.5 for HIGH-IMPEDANCE, 1.0 for HIGH
    int value = state * 10;
    if (value >= 4 && value <= 6) {
      pinMode(pin_number_, INPUT);
    } else if (value < 5) {
      pinMode(pin_number_, OUTPUT);
      digitalWrite(pin_number_, LOW);
    } else {
      pinMode(pin_number_, OUTPUT);
      digitalWrite(pin_number_, HIGH);
    }
  }
};
