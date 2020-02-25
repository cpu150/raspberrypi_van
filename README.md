# INTRODUCTION
The purpose of this project is to manage lights and other systems (water levels, heater, solar panels, etc.) in a van running on a 12 volts battery<br />
It runs on a [Raspberry Pi Zero W](https://www.raspberrypi.org/products/raspberry-pi-zero-w/) and uses the [GPIO port](https://pinout.xyz/) to interface with the electronic components<br />
There is a basic schema there: `electronic/schema.pdf`<br />
The code is written in C++ and use [*raspberrypi_gpio* project](https://github.com/cpu150/raspberrypi_gpio) which is a C++ wrapper around the [*bcm2835* library](http://www.airspayce.com/mikem/bcm2835)

# DEPENDENCIES
## `RASPBERRYPI_GPIO` GIT REPOSITORY
The *raspberrypi_gpio* repository is connected to this repository via a git submodule.

# COMPILATION
This project use *make* to compile. Here are the available make commands:<br />
    - `all`       - build the project applying the *release* configuration<br />
    - `debug`     - build the project applying the *debug* configuration<br />
    - `clean`     - delete all generated files<br />
    - `install`   - copy files (binaries and scripts) to the OS folders and register the service to make it run at startup<br />
    - `uninstall` - remove files (binaries and scripts) from the OS folders and unregister the service
