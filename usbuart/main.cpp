#include <mono.h>
#include <mbed.h>

int main()
{
    
    
//    USBUART_Start(0, USBUART_DWR_VDDD_OPERATION);
//    while(!USBUART_GetConfiguration());
//    USBUART_CDC_Init();
    
    int num = 1;
    while (1) {
        
        //USBUART_PutString("test");
        
        mono::defaultSerial.printf("hej med dig %i\n\r",num++);
        
        mbed::wait_ms(1000);
    }
    
    
    
	
	
	return 0;
}