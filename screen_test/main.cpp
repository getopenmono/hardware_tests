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
extern "C" {
#include <project.h>
}

#include <mono.h>
#include <display_painter.h>
#include <Serial.h>

mono::ui::ConsoleView<176, 190> uiConsole;


class AppCtrl : public mono::IApplication {
    
public:
    
    void monoWakeFromReset()
    {
        uiConsole.setPosition(mono::geo::Point(0,30));
        uiConsole.WriteLine("Wake from reset!");
        
        int sdkort = CyPins_ReadPin(CYREG_PRT5_PC1);
        
        
        
    }
    void monoWillGotoSleep()
    {
        
    }
    
    void monoWakeFromSleep()
    {
        
    }
    
};


int main()
{
//    CyGlobalIntEnable;
//    USBUART_Start(0, USBUART_DWR_VDDD_OPERATION);
//    while (!USBUART_GetConfiguration());
//    USBUART_CDC_Init();
    
//    USBUART_PutString("main start\n");
    AppCtrl app;
    
    //mono::IApplicationContext::Instance->exec();
    
//    USBUART_PutString("init display controller\n");
    
//    USBUART_PutString("create painter\n");
//    mono::display::DisplayPainter painter(mono::IApplicationContext::Instance->displayController);
//    painter.setForegroundColor(mono::display::RedColor);
//    painter.drawFillRect(0, 0, 176, 220);
    
    
//    USBUART_PutString("set mono app\n");
    
    mono::IApplicationContext::Instance->setMonoApplication(&app);
    
    mbed::Serial pc(USBTX, USBRX);
    pc.printf("USB test 1\n\r");
    pc.printf("USB test 2\n\r");
    pc.printf("USB test 3\n\r");
    
    
	return 0;
}

/* [] END OF FILE */
