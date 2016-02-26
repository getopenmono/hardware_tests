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

using namespace mono::geo;

const int AppController::SaneTempMax = 55000;
const int AppController::SaneTempMin = 18000;
const geo::Rect AppController::SaneTouchCal(300,200,3000,3200);

// Contructor
// initializes the label object with position and text content
// You should init data here, since I/O is not setup yet.
AppController::AppController() :
    wifiSpi(RP_SPI_MOSI,RP_SPI_MISO, RP_SPI_CLK),
    wifiComm(wifiSpi, RP_SPI_CS, RP_nRESET, RP_INTERRUPT),
    timer(1000)
{
    tempCheckOk = accelCheckOk = touchCalOk = redpineOk = false;
    pwrCheckOk = hasBeeped = rssiOk = false;
}

// MARK: Test funcs

void AppController::timerFire()
{

    if (!pwrCheckOk)
        checkPowerSystem();

    if (!tempCheckOk)
        checkTemperatureSensor();

    if (!accelCheckOk)
        checkAccelerometer();

    if (!redpineOk)
        checkRedpine();

    if (redpineOk && !rssiOk)
    {
        signalStrength();
    }

    if (tempCheckOk && accelCheckOk && redpineOk && rssiOk && !touchCalOk)
    {
        enterTouchCal();
    }
}

void AppController::checkPowerSystem()
{
    power::IPowerSubSystem *pwrSub = IApplicationContext::Instance->PowerManager->PowerSystem;
    power::IPowerSubSystem::ChargeState state = pwrSub->ChargeStatus();

    if (state == power::IPowerSubSystem::UNKNOWN)
    {
        runError("powersystem returned UNKNOWN for battery state!");
        timer.Stop();
    }
    else
    {
        println(String::Format("PowerSystem OK (state: %i)",state));
        pwrCheckOk = true;
    }
}

void AppController::enterTouchCal()
{
    timer.Stop();
    tcal.setCalibrationDoneCallback<AppController>(this, &AppController::exitTouchCal);
    tcal.show();
    //println("Run touch calibration...");
}

void AppController::exitTouchCal()
{
    TouchCalibration cal = IApplicationContext::Instance->TouchSystem->CurrentCalibration();

    println(cal.ToString());

    if (SaneTouchCal.contains(cal)) {
        timer.Start();
        println("TouchCalibration OK");
        touchCalOk = true;
    }
    else
    {
        runError("Touch calibration outside sane bounds!");
    }
}

void AppController::checkRedpine()
{
    println("Initializing Redpine module...");
    redpine::Module *redpine = redpine::Module::Instance();
    redpineOk = redpine->initialize(&wifiComm);

    if (!redpineOk)
    {
        runError("Redpine module did not respond with Card Ready!");
        timer.Stop();
        return;
    }
    else
    {
        println("Redpine OK");
    }
}

void AppController::signalStrength()
{
    if (!redpineOk)
    {
        println("cannot check signal strength, when module not ok!");
        return;
    }
    println("Checking SSID signal strength...");
    timer.Stop();
    redpine::Module::scanNetworks<AppController>(this, &AppController::signalStrengthResponse);
}

void AppController::signalStrengthResponse(redpine::ScanFrame::scanResponse *data)
{
    rssiOk = false;
    // look for ptype
    for (int n=0; n<data->scanCount; n++) {
        if (strcmp((const char*)data->scanInfos[n].ssid, "ptype"))
        {
            println(String::Format("SSID: ptype, RSSI: %i",data->scanInfos[n].rssiVal));
            rssiOk = true;
            timer.Start();
            break;
        }
    }

    if (!rssiOk)
    {
        println("Could not find AP: ptype!");
        timer.Stop();
    }
}

void AppController::checkAccelerometer()
{
    println("Checking Accelerometer...");
    sensor::IAccelerometer *accel = IApplicationContext::Instance->Accelerometer;
    accel->Start();

    if (!accel->IsActive())
    {
        runError("Could not activate accelerometer!");
    }
    else
    {
        println("Accelerometer is OK");
        accelCheckOk = true;
    }
}

void AppController::checkTemperatureSensor()
{
    //get temp
    int celcius = IApplicationContext::Instance->Temperature->ReadMilliCelcius();
    println( String::Format("%i mC",celcius) );

    if (celcius < SaneTempMin || celcius > SaneTempMax)
    {
        runError(String::Format("Could not read correct temperature from TEMP SENSOR. got: %i",celcius<<10));
    }
    else
    {
        println("Temp sensor OK");
        tempCheckOk = true;
    }
}

// MARK: Misc

void AppController::runError(mono::String errorDesc)
{
    console.WriteLine(errorDesc);

    if (!hasBeeped)
    {
        for (int b=0; b<4; b++) {
            PWM_WriteCompare2(32);
            wait_ms(200);
            PWM_WriteCompare2(0);
            wait_ms(300);
        }
        hasBeeped = true;
    }
}

void AppController::println(String text)
{
    console.WriteLine(text);
    debug("%s\n\r",text());
}

// MARK: Ctrl setup & sleep funcs

void AppController::monoWakeFromReset()
{
    mono::defaultSerial.printf("Assembly Test"); // force enumeration
    println("Assembly Test"); // force enumeration

    IApplicationContext::Instance->PowerManager->PowerSystem->setPowerFence(false);

    //tell the label to show itself
    console.show();

    timer.setCallback<AppController>(this, &AppController::timerFire);
    timer.Start();

    uint32_t unique;
    CyGetUniqueId(&unique);
    println(String::Format("CPU GUID: %lu\n\r",unique));
}

void AppController::monoWillGotoSleep()
{
    println("GOTO SLEEP"); // force enumeration
}

void AppController::monoWakeFromSleep()
{
    IApplicationContext::SoftwareReset();
}