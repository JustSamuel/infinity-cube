//
// Created by Samuel on 01/03/2021.
//

#pragma once
#include <ArduinoJson.h>
#include "Config.h"
#include "WiFiServer.h"

/**
 * Singleton Server class containing WiFi logic.
 */
class CServer {
    // Singleton instance of this CServer.
    static CServer *instance;

    // Connecting to the WiFi.
    WiFiServer* wifiServer;

    // The connected client.
    WiFiClient remoteClient;

    // For multiprocessing.
    TaskHandle_t wifiLoopTask{};

    // JSON input data.
    DynamicJsonDocument* dataInput;

    // Private Constructor.
    CServer();

public:

    // Checks and connects to any clients.
    void checkForConnections();

    // Connects to WiFi.
    static void connectToWiFi();

    // Singleton constructor.
    static CServer *getInstance();

    // Parses data
    void getData();

    // WiFi Loop thread
    [[noreturn]] static void wifiLoop(void * parameter);
};