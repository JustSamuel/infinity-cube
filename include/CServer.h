//
// Created by Samuel on 01/03/2021.
//

#pragma once
#include "Config.h"
#include "WiFiServer.h"

/**
 * Singleton Server class containing WiFi logic.
 */
class CServer {
    // Singleton instance of this CServer.
    static CServer *instance;

    WiFiServer* wifiServer;

    WiFiClient remoteClient;

    TaskHandle_t wifiLoopTask;

    // Private Constructor.
    CServer();

public:

    void checkForConnections();

    // Connects to WiFi.
    void connectToWiFi();

    // Singleton constructor.
    static CServer *getInstance();

    void echoReceivedData();

    [[noreturn]] static void wifiLoop(void * parameter);
};