#include "Van.h"

Van::Van() {
  // Setup GPIO port
  gpio->setup_pin(swt_middle);
  gpio->setup_pin(swt_top);
  gpio->setup_pin(swt_bottom);
  gpio->setup_pin(led);

  // PWM setup
  gpio->setup_pwm(GpioPwmClock::KHZ_9_375);
}

Van::~Van() {
  // Stop the thread
  stop();

  // Unload GPIO
  delete gpio;
  gpio = NULL;
}

void Van::stop() {
  light_ratio = VAN_RATIO_LIGHT_EXIT;
}

bool Van::isStoping() {
  return getLightRatio() == VAN_RATIO_LIGHT_EXIT;
}

int Van::run_loop() {
  int errnum = NO_ERROR;

  std::list<GpioPinIO*> switches = getSwitchesPushed();

  if (!isStoping()) {
    // If a switch is pushed
    if (!switches.empty()) {
      std::int16_t prevVal = getLightRatio();
      // A switch is pushed
      for (GpioPinIO *pin : switches) {
        if (pin == &swt_top) {
          setLightRatio(getLightRatio()+VAN_LIGHT_INCREMENT_STEP);
        } else if (pin == &swt_middle) {
          setLightRatio(getLightRatio()-VAN_LIGHT_INCREMENT_STEP);
        } else if (pin == &swt_bottom) {
          setLightRatio(VAN_RATIO_LIGHT_MIN);
        }
      }

      if (prevVal != getLightRatio()) {
        gpio->write(&led, getLightRatio());
      }
    }
#ifdef DEBUG
    else {
      // No switch pushed
      std::cout << "no switch pushed" << endl;
    }
#endif
    std::this_thread::sleep_for(std::chrono::milliseconds(VAN_MAIN_LOOP_DEFAULT_SLEEP_MS));
  }

  return errnum;
}

std::list<GpioPinIO*> Van::getSwitchesPushed() {
  std::list<GpioPinIO*> switches_pushed = gpio->get_pins_up({ &swt_middle, &swt_top, &swt_bottom });

  // Check wether it's still pushed (not just bouncing)
  std::this_thread::sleep_for(std::chrono::milliseconds(VAN_SWITCH_BOUNCES_TIME_MS));

  return gpio->get_pins_up(switches_pushed);
}

void Van::setLightRatio(std::int16_t val) {
  light_ratio = Clamp<std::int16_t>(val, VAN_RATIO_LIGHT_MIN, VAN_RATIO_LIGHT_MAX);
}

std::int16_t Van::getLightRatio() {
  return light_ratio;
}
