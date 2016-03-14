//
//  DownloadController.h
//
//
//  Created by Kristoffer Andersen on 08/12/2015.
//  Copyright © 2015 your name. All rights reserved.
//

#ifndef DownloadController_h
#define DownloadController_h

#include <mono.h>
#include <SPI.h>
#include <FunctionPointer.h>
//#include <file_system.h>

using namespace mono;
using namespace mono::network;

class DownloadController {
    mbed::SPI wifiSpi;
    redpine::ModuleSPICommunication comm;
    HttpClient client;
    ui::ConsoleView<176,110> *console;
    
    ui::TextLabelView byteCount, errorCount;
    int byteTotal, errorTotal;
    
    String url;
    
    
    
    bool active;
    
public:
    
    mbed::FunctionPointer activeStateChangeHandler;
    
    DownloadController(ui::ConsoleView<176, 110> *con);
    
    void Start();
    
    void Stop();
    
    bool IsActive() const;
    
    void staticIP(redpine::Module::StaticIPParams *params);
    
    void wifiConnect();
    
    void wifiConnected();
    
    void beginDownload();
    
    void httpDataReady(const HttpClient::HttpResponseData &data);
    
    void httpErrorHandler(INetworkRequest::ErrorEvent *evnt);
    
};

#endif /* DownloadController_h */
