#!/bin/bash

# Export
sudo echo 4  > /sys/class/gpio/export
sudo echo 27 > /sys/class/gpio/export

# Show result
./display_status.sh

