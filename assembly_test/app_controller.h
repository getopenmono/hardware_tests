//
//  app_controller.h
//  
//
//  
//
//

#ifndef app_controller_h
#define app_controller_h

#include <mono.h>
#include <wireless/redpine_module.h>
#include <mbed.h>

using namespace mono;
using namespace mono::ui;

class AppController : public mono::IApplication {

    static const int SaneTempMax;
    static const int SaneTempMin;
    static const geo::Rect SaneTouchCal;

    bool tempCheckOk, accelCheckOk, touchCalOk, redpineOk, hasBeeped;
    bool pwrCheckOk, rssiOk;

    // This is the text label object that will displayed
    ConsoleView<176, 220> console;
    TouchCalibrateView tcal;
    mbed::SPI wifiSpi;
    redpine::ModuleSPICommunication wifiComm;

    Timer timer;

public:
    
    AppController();

    void timerFire();

    void checkPowerSystem();

    void checkAccelerometer();

    void checkTemperatureSensor();

    void enterTouchCal();

    void exitTouchCal();

    void checkRedpine();

    void signalStrength();

    void signalStrengthResponse(redpine::ScanFrame::scanResponse *data);

    // MARK: Misc

    void runError(String errorDesc);

    void println(String text);

    // MARK : Setup & Sleep
    
    void monoWakeFromReset();

    void monoWillGotoSleep();

    void monoWakeFromSleep();
    
};

#endif /* app_controller_h */
