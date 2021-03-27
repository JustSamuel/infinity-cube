//
// Created by Samuel on 01/03/2021.
//

#pragma once
#include <ArduinoJson.h>
#include "AnimationCommand.h"
#include "Config.h"
#include "WiFiServer.h"
#include "LEDController.h"

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

    static void parseJSON(AnimationCommand *inputCommand, DynamicJsonDocument *dataInput);

    // Private Constructor.
    CServer();

public:
    // Singleton constructor.
    static CServer *getInstance();

    // Checks and connects to any clients.
    void checkForConnections();

    // Connects to WiFi.
    static void connectToWiFi();

    // Parses data
    void getData();

    // WiFi Loop thread
    [[noreturn]] static void wifiLoop(void * parameter);
};