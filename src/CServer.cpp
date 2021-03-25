//
// Created by Samuel on 01/03/2021.
//
#pragma once

#include <CServer.h>
#define ARDUINOJSON_USE_DOUBLE 0
#include "InfintyCube.h"
#include "AnimationCommand.h"

CServer *CServer::instance = nullptr;

CServer::CServer() {
    connectToWiFi();
    // Create on stack.
    wifiServer = new WiFiServer(ServerPort);
    wifiServer->begin();

    currentCommand = LEDController::getInstance() -> currentCommand;

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
    uint8_t ReceiveBuffer[JSON_PAYLOAD_SIZE];
    while (remoteClient.connected() && remoteClient.available()) {
        int received = remoteClient.read(ReceiveBuffer, sizeof(ReceiveBuffer));
        char data[received];
        data[received] = '\0';

        for (int i = 0; i < received; ++i) {
            char charValue = ReceiveBuffer[i];
            data[i] = charValue;
        }

        // Send what we received back.
        remoteClient.write('0');

        // Deserialize the JSON.
        DynamicJsonDocument dataInput(JSON_PAYLOAD_SIZE);

        DeserializationError error = deserializeJson(dataInput, data);
        if (!error) {
            parseJSON(currentCommand, &dataInput);
            LEDController::getInstance() -> parseCommand();
        }
    }
}

void CServer::parseJSON(AnimationCommand *inputCommand, DynamicJsonDocument *dataInput) {
    inputCommand->animationId = (*dataInput)["animationId"].as<int>();

    int colorInt = (*dataInput)["color"].as<int>();
    if (colorInt) {
        int color[3];
        intToRGB(color, colorInt);
        inputCommand->color = CRGB(color[0], color[1], color[2]);
    }

    inputCommand->changes = (*dataInput)["changes"].as<int>();

    inputCommand->height = (*dataInput)["height"].as<double>();

    inputCommand->xfloat = (*dataInput)["xfloat"].as<double>();
}


[[noreturn]] void CServer::wifiLoop(void *parameter) {
    for (;;) {
        CServer::getInstance()->checkForConnections();
        CServer::getInstance()->getData();
        delay(20);
    }
}