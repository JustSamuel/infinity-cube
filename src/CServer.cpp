//
// Created by Samuel on 01/03/2021.
//
#pragma once

#include <CServer.h>

#include "InfintyCube.h"

CServer *CServer::instance = nullptr;

CServer::CServer() {
    ConnectToWiFi();
    wifiServer = new WiFiServer(ServerPort);
    wifiServer->begin();
}

void CServer::CheckForConnections() {
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

void CServer::ConnectToWiFi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, WiFiPassword);
    Serial.print("Connecting to ");
    Serial.println(SSID);

    uint8_t i = 0;
    while (WiFi.status() != WL_CONNECTED) {
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

void CServer::EchoReceivedData() {
    uint8_t ReceiveBuffer[30];
    while (remoteClient.connected() && remoteClient.available()) {
        int Received = remoteClient.read(ReceiveBuffer, sizeof(ReceiveBuffer));
        remoteClient.write(Received);
        for (int i = 0; i < Received; ++i) {
            Serial.println(ReceiveBuffer[i]);
        };
        Serial.println();
    }
}