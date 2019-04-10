#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/time.h>
#include <wiringPi.h>


// What GPIO input are we using?
//	This is a wiringPi pin number

#define	BUTTON_PIN	7

// globalCounter:
//	Global variable to count interrupts
//	Should be declared volatile to make sure the compiler doesn't cache it.

struct timeval time_pushed, time_released;
static int isSettingTime = 0;
static int isSettingHours = 0;
static int isSettingMinutes = 0;

static const int TIME_THRESHOLD = 3;

/*
 * myInterrupt:
 *********************************************************************************
 */

void myInterrupt (void){
	// The time is not being set
	if (isSettingTime == 0){
		// Up
		if (digitalRead(BUTTON_PIN) == LOW)
			gettimeofday(&time_pushed, NULL);
		// Down
		else{
			gettimeofday(&time_released, NULL);
			double time_pushing = time_released.tv_sec - time_pushed.tv_sec;
			if (time_pushing >= TIME_THRESHOLD){
				printf("Set Time\n");
				isSettingTime = 1;
				isSettingHours = 1;
			}
		}
	}
	else{
		if (digitalRead(BUTTON_PIN) == LOW){
			if (isSettingMinutes){
				printf("Time is set\n");
				isSettingTime = 0;
				isSettingHours = 0;
				isSettingMinutes = 0;
				// Reset the timer
				gettimeofday(&time_pushed, NULL);
				gettimeofday(&time_pushed, NULL);

			}
			if (isSettingHours){
				printf("Now set the minutes\n");
				isSettingHours = 0;
				isSettingMinutes = 1;
			}
		}
	}
}


/*
 *********************************************************************************
 * main
 *********************************************************************************
 */

int main (void)
{

  if (wiringPiSetup () < 0)
  {
    fprintf (stderr, "Unable to setup wiringPi: %s\n", strerror (errno)) ;
    return 1 ;
  }

  if (wiringPiISR (BUTTON_PIN, INT_EDGE_BOTH, &myInterrupt) < 0)
  {
    fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno)) ;
    return 1 ;
  }


  for (;;)
  {
	continue;
  }

  return 0 ;
}

