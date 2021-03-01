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
    // Singleton instance of this Cube.
    static CServer *instance;

    WiFiServer* wifiServer;

    WiFiClient remoteClient;

    // Private Constructor.
    CServer();

public:

    void CheckForConnections();

    // Connects to WiFi.
    void ConnectToWiFi();

    // Singleton constructor.
    static CServer *getInstance();

    void EchoReceivedData();
};