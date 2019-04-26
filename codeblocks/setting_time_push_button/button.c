// Setting time push button behavior

#include <wiringPi.h>

#include <stdio.h>

const int INPUT_PIN = 0;

int listenPushButton(int* isSettingTime, int* isSettingHours, int* isSettingMinutes){
  waitForInterrupt(INPUT_PIN, -1);
  return 1;
}
