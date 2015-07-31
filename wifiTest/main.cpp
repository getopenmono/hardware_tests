/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <mono.h>
#include "app_controller.h"


int main()
{
    PWM_Start();
    PWM_WriteCompare1(128);
    CyDelay(300);
    PWM_WriteCompare1(0);
    CyDelay(300);
    PWM_WriteCompare1(128);
    CyDelay(300);
    PWM_WriteCompare1(0);
    
    AppController app;
	
    mono::IApplicationContext::Instance->setMonoApplication(&app);
    
	return 0;
}

/* [] END OF FILE */
