#include <wiringPi.h>

#include <stdio.h>

int main(void){

  // Initialize the wiringPi library
  wiringPiSetup();

  const int INPUT_PIN = 7;  // Pin number of the reading
  pinMode(INPUT_PIN, INPUT);
  int isPressed = 0;

  while(1){
    if (digitalRead(INPUT_PIN) == LOW){
      if (isPressed == 0){
        isPressed = 1;
        printf("Button is pressed\n");
      }
    }
    else {
      isPressed = 0;
    }

  }

  return 0;
}
