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

    xTaskCreatePinnedToCore(
            CServer::wifiLoop,      /* Function to implement the task */
            "WiFiLoop",     /* Name of the task */
            10000,      /* Stack size in words */
            nullptr,    /* Task input parameter */
            1,             /* Priority of the task */
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

bool firstPass = true;

/**
 * Receive the JSON and parse it using a DynamicJsonDocument.
 * After parsing update the command in the controller.
 */
void CServer::getData() {
    uint8_t ReceiveBuffer[JSON_PAYLOAD_SIZE];
    // Whilst there is data...
    while (remoteClient.connected() && remoteClient.available()) {
        if (firstPass) {
            Serial.print("First input received at");
            Serial.println(micros());
            firstPass = false;
        }

        //...read data.
        int received = remoteClient.read(ReceiveBuffer, sizeof(ReceiveBuffer));

        // Turn it into a string.
        char data[received];
        data[received] = '\0';

        for (int i = 0; i < received; ++i) {
            char charValue = ReceiveBuffer[i];
            data[i] = charValue;
        }

        // Send what we received back.
        remoteClient.write('0');

        // Create JSON object.
        DynamicJsonDocument dataInput(JSON_PAYLOAD_SIZE);

        // Parse the input JSON.
        DeserializationError error = deserializeJson(dataInput, data);

        // Send to LEDController.
        if (!error) {
            parseJSON(LEDController::getInstance() -> currentCommand, &dataInput);
        }
    }
}

void CServer::parseJSON(AnimationCommand *inputCommand, DynamicJsonDocument *dataInput) {
    inputCommand->animationId = (*dataInput)["animationId"].as<int>();

    int colorInt = (*dataInput)["color"].as<int>();
    if (colorInt) {
        int color[3];
        intToRGB(color, colorInt);
        inputCommand->color.r = color[0];
        inputCommand->color.g = color[1];
        inputCommand->color.b = color[2];
    }

    inputCommand->changes = (*dataInput)["changes"].as<int>();

    inputCommand->height = (*dataInput)["height"].as<double>();

    inputCommand->xfloat = (*dataInput)["xfloat"].as<double>();
}

/**
 * Main loop for the WiFi thread.
 * Checks if there are connections and reads input data.
 */
[[noreturn]] void CServer::wifiLoop(void *parameter) {
    for (;;) {
        CServer::getInstance()->checkForConnections();
        CServer::getInstance()->getData();
        delay(1);
    }
}