#include "esphome.h"
// #include "driver/gpio.h"

using namespace esphome;
using namespace output;

class MyTriStateOutput : public Component, public FloatOutput {
 private:
  esp32::ESP32InternalGPIOPin *gpio_pin_;
 public:

  MyTriStateOutput(uint8_t pin_number) {
    gpio_pin_ = new(esp32::ESP32InternalGPIOPin);
    gpio_pin_->set_pin(static_cast<gpio_num_t>(pin_number));
    gpio_pin_->set_inverted(false);
  }

  void setup() override {
    // This will be called by App.setup()
    gpio_pin_->set_flags(gpio::Flags::FLAG_INPUT);
    gpio_pin_->setup();
    // gpio_set_direction(gpio_pin_, esp32::GPIO_MODE_INPUT_ONLY);
    // gpio_set_pull_mode(gpio_pin_, esp32::GPIO_FLOATING);
  }

  void write_state(float state) override {
    // state is the amount this output should be on, 0.0 for LOW, 0.5 for HIGH-IMPEDANCE, 1.0 for HIGH
    // int value = state * 10;
    int value = state * 10;
    if (value >= 4 && value <= 6) {
      gpio_pin_->pin_mode(gpio::Flags::FLAG_INPUT);
      // gpio_set_direction(gpio_pin_, esp32::GPIO_MODE_INPUT_ONLY);
      // gpio_set_pull_mode(gpio_pin_, esp32::GPIO_FLOATING);
    } else if (value < 5) {
      gpio_pin_->pin_mode(gpio::Flags::FLAG_OUTPUT);
      gpio_pin_->set_inverted(false); //absolutely required, otherwise switching to output and LOW will enable inverted
      gpio_pin_->set_drive_strength(GPIO_DRIVE_CAP_1);
      gpio_pin_->digital_write(false);
      // gpio_set_direction(gpio_pin_, esp32::GPIO_MODE_OUTPUT);
      // gpio_set_level(pin_number, 0);
    } else {
      gpio_pin_->pin_mode(gpio::Flags::FLAG_OUTPUT);
      gpio_pin_->set_inverted(false); //absolutely required, otherwise switching to output and low will enable inverted
      gpio_pin_->set_drive_strength(GPIO_DRIVE_CAP_1);
      gpio_pin_->digital_write(true);
      // gpio_set_direction(gpio_pin_, esp32::GPIO_MODE_OUTPUT);
      // gpio_set_level(pin_number, 1);
    }
  }
};
