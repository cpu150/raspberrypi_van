#!/bin/bash

echo 1 >/sys/class/gpio/gpio4/value

./display_status.sh

