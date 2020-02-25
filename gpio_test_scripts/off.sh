#!/bin/bash

echo 0 >/sys/class/gpio/gpio4/value

./display_status.sh

