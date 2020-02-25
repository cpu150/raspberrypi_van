#!/bin/bash

# Show result
ls /sys/class/gpio/
echo "GPIO 4:"
echo "  - value=$(cat /sys/class/gpio/gpio4/value)"
echo "  - direction=$(cat /sys/class/gpio/gpio4/direction)"
echo ""
echo "GPIO 27:"
echo "  - value=$(cat /sys/class/gpio/gpio27/value)"
echo "  - direction=$(cat /sys/class/gpio/gpio27/direction)"
echo "  - active_low=$(cat /sys/class/gpio/gpio27/active_low)"

