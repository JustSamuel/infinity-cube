//
// Created by Samuel on 01/03/2021.
//
#pragma once

#include <CServer.h>

#include "InfintyCube.h"

CServer *CServer::instance = nullptr;

CServer::CServer() {
    connectToWiFi();
    // Create on stack.
    wifiServer = new WiFiServer(ServerPort);
    wifiServer->begin();

    // Create on stack.
    dataInput = new DynamicJsonDocument(1024);

    xTaskCreatePinnedToCore(
            CServer::wifiLoop,      /* Function to implement the task */
            "WiFiLoop",     /* Name of the task */
            10000,      /* Stack size in words */
            nullptr,       /* Task input parameter */
            0,             /* Priority of the task */
            &wifiLoopTask,          /* Task handle. */
            0);             /* Core where the task should run */
}

void CServer::checkForConnections() {
    if (wifiServer->hasClient()) {
        // If we are already connected to another computer,
        // then reject the new connection. Otherwise accept
        // the connection.
        if (remoteClient.connected()) {
            Serial.println("Connection rejected");
            wifiServer->available().stop();
        } else {
            Serial.println("Connection accepted");
            remoteClient = wifiServer->available();
        }
    }
}

void CServer::connectToWiFi() {
    WiFiClass::mode(WIFI_STA);
    WiFi.begin(SSID, WiFiPassword);
    Serial.print("Connecting to ");
    Serial.println(SSID);

    uint8_t i = 0;
    while (WiFiClass::status() != WL_CONNECTED) {
        Serial.print('.');
        delay(500);

        if ((++i % 16) == 0) {
            Serial.println(F(" still trying to connect"));
        }
    }

    Serial.print(F("Connected. My IP address is: "));
    Serial.println(WiFi.localIP());
}


CServer *CServer::getInstance() {
    if (!instance) {
        instance = new CServer();
    }
    return instance;
}

void CServer::getData() {
    uint8_t ReceiveBuffer[1024];
    int color[3];
    int params[5];

    while (remoteClient.connected() && remoteClient.available()) {
        int received = remoteClient.read(ReceiveBuffer, sizeof(ReceiveBuffer));
        char *data = new char[received];
        data[received] = '\0';

        for (int i = 0; i < received; ++i) {
            char charValue = ReceiveBuffer[i];
            data[i] = charValue;
        }

        // Send what we received back.
        remoteClient.write(data);

        deserializeJson(*dataInput, data);

        // What animation to set.
        int animationId = (*dataInput)["animationId"];

        // Get color out of JSON.
        intToRGB(color, (*dataInput)["color"]);

        // Param objects allow us to encode extra parameters.
        params[0] = (*dataInput)["changes"];

        // Parse the command
        LEDController::getInstance()->parseCommand(animationId, color, params);
    }
}

[[noreturn]] void CServer::wifiLoop(void *parameter) {
    for (;;) {
        CServer::getInstance()->checkForConnections();
        CServer::getInstance()->getData();
        delay(1);
    }
}