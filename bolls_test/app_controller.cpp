//
//  app_controller.cpp
//
//
//
//  
//

#include "app_controller.h"
#include <project.h>
#include <PinNames.h>
#include <mn_digital_out.h>

#ifdef MONO_CONSOLE_STDOUT
extern mono::ui::ConsoleView<176,110> *ui_console_stdout;
#endif

using namespace mono;
using namespace mono::geo;

volatile static bool WDTimerFlag = false;

AppController::AppController() :
    sdfs(SD_SPI_MOSI, SD_SPI_MISO, SD_SPI_CLK, SD_SPI_CS, "sd"),
    console(geo::Point(0,0)),
    downCtrl(&console),
    activeLamp(Rect(10, 10, 8, 8)),
    otgLamp(Rect(160,10,8,8)),
    downloadToggleBtn(Rect(5,125,70,19), "Stop"),
//    tCal(Rect(0,0,176,220)),
    analogView(Rect(0,145,176,20),"N/A"),
    analogPrgs(Rect(10,165,156,15))
{
#ifdef MONO_CONSOLE_STDOUT
    ui_console_stdout = &this->console;
#endif
    analogPrgs.setMaximum(0x1000);
    analogPrgs.setMinimum(0x0);
    
    analog.setValueChangedCallback<AppController>(this, &AppController::analogValueChanged);
    console.setPosition(Point(0,25));
    
    downCtrl.activeStateChangeHandler.attach<AppController>(this, &AppController::downloadActiveChanged);
    downloadToggleBtn.setClickCallback<AppController>(this, &AppController::dwnldButton);
    analogView.setAlignment(TextLabelView::ALIGN_CENTER);

    this->singleShot = false;
}

void AppController::taskHandler()
{
    WDTimerFlag = false;
}

void AppController::monoWakeFromReset()
{
    defaultSerial.printf("");
    //tCal.show();
    //tCal.setCalibrationDoneCallback<AppController>(this, &AppController::touchCalDone);
    touchCalDone();
    IApplicationContext::Instance->UserButton->fall<AppController>(this, &AppController::resetDisp);
//    IApplicationContext::Instance->UserButton->fall<AppController>(this, &AppController::fastReset);
//    otgButtonOff.setClickCallback<AppController>(this, &AppController::otgBtnOff);
//    otgButtonOn.setClickCallback<AppController>(this, &AppController::otgBtnOn);

//    sleepBtn.setClickCallback<AppController>(this, &AppController::gotoSleep);
//    sleepBtn.show();


}

void AppController::touchCalDone()
{
    console.show();
    console.WriteLine("Bolls Test App.");

    downCtrl.wifiConnect();
    activeLamp.show();
    downloadToggleBtn.show();
    analogView.show();
    analogPrgs.show();
//    otgLamp.show();
    
//    otgButtonOn.show();
//    otgButtonOff.show();
//
//    bool success = power.setUSBOTGPower(true);
//    
//    if (!success)
//        console.WriteLine("could not set OTG power");
    
//    power::IPowerSubSystem *power = IApplicationContext::Instance->PowerManager->PowerSystem;
//    
//    console.printf("Charge status: 0x%x\n",power->ChargeStatus());
//    
//    console.printf("Power fence: 0x%x\n",power.PowerFencePeriperals());
    
    analog.Start();

    //IApplicationContext::Instance->RunLoop->addDynamicTask(this);
    //wdTimer.attach_us<AppController>(this, &AppController::fastReset, 100000);
}

void AppController::monoWillGotoSleep()
{
    analog.Stop();
}

void AppController::monoWakeFromSleep()
{
    IApplicationContext::Instance->SoftwareReset();

    console.show();
    activeLamp.show();
    analogView.show();
    
    console.scheduleRepaint();
    activeLamp.scheduleRepaint();
    analogView.scheduleRepaint();

    analog.Start();
}

void AppController::downloadActiveChanged()
{
    activeLamp.setState(downCtrl.IsActive());
}

void AppController::dwnldButton()
{
    if (downCtrl.IsActive())
    {
        downCtrl.Stop();
        downloadToggleBtn.setText("Start");
    }
    else
    {
        downCtrl.Start();
        downloadToggleBtn.setText("Stop");
    }
    
}

void AppController::otgBtnOff()
{
//    if(!power.setUSBOTGPower(false))
//    {
//        console.WriteLine("OTG OFF Failed!");
//    }
}

void AppController::otgBtnOn()
{
//    if (!power.setUSBOTGPower(true))
//    {
//        console.WriteLine("OTG ON Failed");
//    }
}

void AppController::otgTimerCallback()
{
    //power.setUSBOTGPower(!power.USBOTGPower());
    //otgLamp.setState(power.USBOTGPower());
}

void AppController::analogValueChanged()
{
    analogView.setText(String::Format("%i",analog.Value()));
    analogPrgs.setValue(analog.Value());
    
    //otgLamp.setState(power.USBOTGPower());
    //console.printf("OTG: 0x%x\n",power.USBOTG());
}

void AppController::gotoSleep()
{
    IApplicationContext::EnterSleepMode();
}

void AppController::fastReset()
{

    if (WDTimerFlag)
    {
        //PWM_WriteCompare2(64);
        //CyDelay(50);
        IApplicationContext::SoftwareResetToApplication();
    }


    WDTimerFlag = true;
}


void AppController::resetDisp()
{
    display::IDisplayController *ctrl = IApplicationContext::Instance->DisplayController;
    ctrl->setBrightness(10);
    wait_ms(100);
    
    ctrl->setBrightness(128);
    wait_ms(50);
    
    ctrl->setBrightness(10);
    wait_ms(100);
    
    ctrl->setBrightness(128);


//    SDFileSystem sd2(SD_SPI_MOSI, SD_SPI_MISO, SD_SPI_CLK, SD_SPI_CS, "sd2");
//    sd2.mount();
//    FILE *test = fopen("/sd2/ssid.txt", "r");
//    
//    debug("test resp: 0x%x\n\r",test);
//    
//    if (test != NULL)
//    {
//        char content[64];
//        int res = fread(content, 64, 1, test);
//        debug("read: %i\n\rContent: %s\n\r",res,content);
//    }
    
//    power::ACT8600PowerSystem *power = (power::ACT8600PowerSystem*) IApplicationContext::Instance->PowerManager->PowerSystem;
//    
//    power->setPowerFencePeripherals(true);
//    //debug("btn fence: %i\n\r", power->PowerFencePeriperals());
//    
//    CyPins_SetPinDriveMode(CYREG_PRT5_PC2, CY_PINS_DM_STRONG);
//    CyPins_ClearPin(CYREG_PRT5_PC2);
//    
//    CyPins_SetPinDriveMode(RP_nRESET, CY_PINS_DM_OD_LO);
//    CyPins_ClearPin(RP_nRESET);
//    
//    uint8_t sda = CY_GET_REG8(CYREG_PRT12_BYP);
//    CY_SET_REG8(CYREG_PRT12_BYP, sda & ~0x20);
//    uint8_t scl = CY_GET_REG8(CYREG_PRT2_BYP);
//    CY_SET_REG8(CYREG_PRT2_PC2, scl & ~0x04);
//    
//    CyPins_SetPinDriveMode(CYREG_PRT2_PC2, CY_PINS_DM_OD_LO);
//    CyPins_ClearPin(CYREG_PRT2_PC2);
//    
//    CyPins_SetPinDriveMode(CYREG_PRT12_PC5, CY_PINS_DM_OD_LO);
//    CyPins_ClearPin(CYREG_PRT12_PC5);
//    
//    CyDelay(1000);
//    
//    // power chip IRQ line
//    CyPins_SetPinDriveMode(CYREG_PRT5_PC2, CY_PINS_DM_DIG_HIZ);
//    
//    CY_SET_REG8(CYREG_PRT12_BYP, sda);
//    CY_SET_REG8(CYREG_PRT2_BYP, scl);
//    
//    
//    power->setPowerFencePeripherals(false);
//    //debug("after fence 0x%x\n\r",power->PowerFencePeriperals());
////
//    IApplicationContext::SoftwareResetToApplication();
    
}
