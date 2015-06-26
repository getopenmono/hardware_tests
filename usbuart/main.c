
#include <project.h>
#include "usbuart_test.h"

int main()
{
    
    usbuart_test_init();
    
    while (1) {
        
        usbuart_test_write("This is the USB UART test program\n\r");
        
        CyDelay(1000);
    }
    
    
    
	
	
	return 0;
}