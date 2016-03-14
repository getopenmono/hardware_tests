//
//  app_controller.h
//  
//
//  
//
//

#ifndef app_controller_h
#define app_controller_h

#include <SDFileSystem.h>

#include "DownloadController.h"
#include "analog_measure.h"
#include "act8600_power_system.h"

#include <mono.h>



using namespace mono;
using namespace mono::geo;
using namespace mono::ui;


class AppController : public mono::IApplication, IRunLoopTask {
    SDFileSystem sdfs;
    ConsoleView<176, 110> console;
    DownloadController downCtrl;
    StatusIndicatorView activeLamp;
    StatusIndicatorView otgLamp;
    ButtonView downloadToggleBtn;
    AnalogMeasure analog;
    TextLabelView analogView;
    ProgressBarView analogPrgs;
    //power::ACT8600PowerSystem power;
    mbed::Ticker wdTimer;
    
public:
    
    AppController();

    void taskHandler();

    void dwnldButton();
    
    void monoWakeFromReset();

    void monoWillGotoSleep();

    void monoWakeFromSleep();
    
    void downloadActiveChanged();
    
    void touchCalDone();
    
    void analogValueChanged();
    
    void otgBtnOn();
    
    void otgBtnOff();
    
    void otgTimerCallback();
    
    void resetDisp();

    void gotoSleep();

    void fastReset();
};

#endif /* app_controller_h */
