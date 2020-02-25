#ifndef VAN_CLASS_H
#define VAN_CLASS_H

#include "raspberrypi_gpio/Gpio.h"
#include <cstdint>
#include <algorithm>
#include <thread>
#include <chrono>

// Sleep timings (in milliseconds)
#define VAN_MAIN_LOOP_DEFAULT_SLEEP_MS  100
#define VAN_SWITCH_BOUNCES_TIME_MS      25
#define VAN_LIGHT_LOOP_DEFAULT_SLEEP_MS 1

// Light ratio
#define VAN_RATIO_LIGHT_EXIT      -1
#define VAN_RATIO_LIGHT_MAX       32
#define VAN_RATIO_LIGHT_MIN       0
#define VAN_LIGHT_INCREMENT_STEP  4

using namespace std;

template <typename T> T Clamp(T value, T low, T high) {
  return (value < low) ? low : ((value > high) ? high : value);
}

class Van {
  public:
    Van();
    ~Van();
    int run_loop();

  private:
    // Light thread
    void stop();
    bool isStoping();

    // Light
    std::int16_t light_ratio = 0; // 0 -> lights off
    void setLightRatio(std::int16_t val);
    std::int16_t getLightRatio();

    // GPIO related
    std::list<GpioPinIO*> getSwitchesPushed();
    Gpio* gpio = new Gpio();
    GpioPinIO swt_top     { GpioPinName::gpio22, GpioFunction::input, GpioPullUp::up };
    GpioPinIO swt_middle  { GpioPinName::gpio27, GpioFunction::input, GpioPullUp::up };
    GpioPinIO swt_bottom  { GpioPinName::gpio10, GpioFunction::input, GpioPullUp::up };
    GpioPwm led           { GpioPwmItem::create(GpioPwmName::pwm1_gpio13), VAN_RATIO_LIGHT_MAX, GpioPwmMode::markspace };
};

#endif
