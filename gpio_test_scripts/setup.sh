#!/bin/bash

# SETUP
sudo echo out > /sys/class/gpio/gpio4/direction
sudo echo in >  /sys/class/gpio/gpio27/direction
sudo echo 1 >   /sys/class/gpio/gpio27/active_low

./display_status.sh

