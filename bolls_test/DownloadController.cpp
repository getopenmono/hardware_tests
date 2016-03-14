//
//  DownloadController.cpp
//  bollsTest
//
//  Created by Kristoffer Andersen on 08/12/2015.
//  Copyright © 2015 your name. All rights reserved.
//

#include "DownloadController.h"
#include "consoles.h"

DownloadController::DownloadController(ui::ConsoleView<176, 110> *con) :
    wifiSpi(RP_SPI_MOSI, RP_SPI_MISO, RP_SPI_CLK),
    comm(wifiSpi, NC, RP_nRESET, RP_INTERRUPT),
    byteCount(geo::Rect(10,180,70,20), "0"),
    errorCount(geo::Rect(120,180,50,20), "0")
{
    url  = "http://10.0.41.1/";
    
    console = con;
    active =  false;
    
    byteTotal = errorTotal = 0;
}

void DownloadController::staticIP(redpine::Module::StaticIPParams *params)
{
    uint8_t ip[4] = { 10, 0, 0, 65 };
    uint8_t mask[4] = { 255, 255, 255, 0 };
    uint8_t gate[4] = { 10, 0, 0, 7 };
    
    memcpy(params->ipAddress, ip, 4);
    memcpy(params->netmask, mask, 4);
    memcpy(params->gateway, gate, 4);
}

void DownloadController::wifiConnect()
{
    redpine::Module::initialize(&comm);
    //redpine::Module::setStaticIPCallback<DownloadController>(this, &DownloadController::staticIP);

//    redpine::Module::setNetworkReadyCallback<DownloadController>(this, &DownloadController::wifiConnected);
//
//    redpine::Module::setupWifiOnly("secher", "pum4h4le");
//
//    byteCount.show();
//    errorCount.show();
//
//    return;

    console->WriteLine("Reading SSID and pass from SD");
    FILE *ssidFile = NULL;
    int timeout = 0;
    
    while (ssidFile == NULL && timeout < 10) {
        ssidFile = fopen("/sd/ssid.txt", "r");
        timeout++;
    }
    
    if (ssidFile == NULL)
    {
        console->WriteLine("Failed to open file: ssid.txt");
        //IApplicationContext::SoftwareResetToApplication();
        //IApplicationContext::ResetOnUserButton();
        return;
    }
    
    if (timeout > 1)
        debug("Opened SD file in %i tries\n\r",timeout);
    
    char buffer[50];
    memset(buffer, 0, 50);
    
    char ch = fgetc(ssidFile);
    int cnt = 0;
    while (ch != '\n' && ch != '\r' && ch != '\0' && cnt < 50 && feof(ssidFile) == 0) {
        buffer[cnt++] = ch;
        ch = fgetc(ssidFile);
    }
    
    String ssid(buffer);
    fclose(ssidFile);
    
    FILE *passFile = fopen("/sd/pass.txt", "r");
    if (passFile == NULL)
    {
        console->WriteLine("Could not open file: pass.txt");
        return;
    }
    
    memset(buffer, 0, 50);
    
    ch = fgetc(passFile);
    cnt = 0;
    while (ch != '\n' && ch != '\r' && ch != '\0' && cnt < 50 && feof(passFile) == 0) {
        buffer[cnt++] = ch;
        ch = fgetc(passFile);
    }
    
    String pass(buffer);
    fclose(passFile);

    console->Write("Connecting to: "); console->WriteLine(ssid);
    
    redpine::Module::setNetworkReadyCallback<DownloadController>(this, &DownloadController::wifiConnected);
    
    redpine::Module::setupWifiOnly(ssid, pass);
    
    byteCount.show();
    errorCount.show();
}

void DownloadController::Start()
{
    if (active != true && redpine::Module::IsNetworkReady())
    {
        active = true;
        activeStateChangeHandler.call();
        Timer::callOnce<DownloadController>(0, this, &DownloadController::beginDownload);
    }
}

void DownloadController::Stop()
{
    if (active == true)
    {
        active = false;
        activeStateChangeHandler.call();
    }
}

bool DownloadController::IsActive() const
{
    return active;
}

void DownloadController::wifiConnected()
{
    console->WriteLine("Connected");
    Start();
}

void DownloadController::beginDownload()
{
    if (!active)
        return;
    
    //console->WriteLine("Downloading...");
    client = HttpClient(url);
    client.setDataReadyCallback<DownloadController>(this, &DownloadController::httpDataReady);
    client.setErrorCallback<DownloadController>(this, &DownloadController::httpErrorHandler);
}

void DownloadController::httpDataReady(const HttpClient::HttpResponseData &data)
{
    //FILE *htmlFile = fopen("/sd/ptype.html", "a");
    //console->WriteLine(data.bodyChunk);
    byteTotal += data.bodyChunk.Length();
    byteCount.setText(String::Format("%i",byteTotal));
//    if (htmlFile != NULL)
//    {
//        fwrite(data.bodyChunk(), data.bodyChunk.Length(), 1, htmlFile);
//        fclose(htmlFile);
//    }
    
    if (data.Finished)
    {
        //console->WriteLine("Done!");
        Timer::callOnce<DownloadController>(0, this, &DownloadController::beginDownload);
    }
}

void DownloadController::httpErrorHandler(INetworkRequest::ErrorEvent *evnt)
{
    //IApplicationContext::SoftwareResetToApplication();

    console->printf("HTTP ERROR: %i\n", evnt->ErrorCode);
    this->Stop();
    
    errorTotal++;
    errorCount.setText(String::Format("%i",errorTotal));
    
    Timer::callOnce<DownloadController>(1000, this, &DownloadController::Start);

}

