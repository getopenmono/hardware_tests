
#include "buzzer_test.h"

void buzzerTest()
{
	PWM_Start();
	CyDelay(300);
	
	PWM_Stop();
	CyDelay(700);
}