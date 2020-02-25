#!/bin/bash

echo 4 >/sys/class/gpio/unexport
echo 27 >/sys/class/gpio/unexport
#echo 22 >/sys/class/gpio/unexport
#echo 10 >/sys/class/gpio/unexport

ls /sys/class/gpio/
