#include <Arduino.h>
#include <ArduinoJson.h>
#include "./models/DriveModel.h"
#include "CarHelper.h"
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "CameraStreamer.h"

#define APSSID "esp32-car2"
#define APPSK  "esp32-car2"
#define SERVER_PORT 80;
//ESP32 IP 192.168.4.1
const char *ssid = APSSID;
const char *password = APPSK;
int port = SERVER_PORT;
CameraStreamer* pCamera;
CarHelper carHelper;
//models
DriveModel driveModel;
DriveModel *pDriveModel = &driveModel;
LedModel ledModel;
LedModel *pLedModel = &ledModel;
AsyncWebServer server(port);
AsyncWebSocket ws("/");
AsyncWebSocketClient* wsClient;

void onMessageWS(String json){
    StaticJsonDocument<1536> doc;
    DeserializationError error = deserializeJson(doc, json);
    if (error) {
/*        Serial.println(json+"\r\n");
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());*/
        return;
    }
    JsonObject root = doc.as<JsonObject>();
    JsonVariant type = root.getMember("type");
    if(type.as<String>() == pDriveModel->type){
        carHelper.updateDriveStructure(pDriveModel, root);
    }
    if(type.as<String>() == pLedModel->type){
        carHelper.updateLedStructure(pLedModel, root);
    }
}
void sendModelWS(BaseModel *event){
    String json = event->toJsonString();
    Serial.println("sendModel: " + json);
    wsClient->text(json);
}
void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){
    if(type == WS_EVT_CONNECT){
        Serial.println("WS_EVT_CONNECT!");
        wsClient = client;
        sendModelWS(pLedModel);
    } else if(type == WS_EVT_DISCONNECT){
        wsClient = nullptr;
    }else if(type == WS_EVT_DATA){
        String str = String((char *)data);
        onMessageWS(str);
    }
}

void startWebSocket() {
    CameraStreamer camera;
    pCamera = &camera;
    ws.onEvent(onWsEvent);
    server.addHandler(&ws);
    server.on("/capture",HTTP_GET,[](AsyncWebServerRequest *req){

        pCamera->captureHandler(req);
    });
    server.on("/bgr",HTTP_GET,[](AsyncWebServerRequest *req){

        pCamera->streamHandler(req);
    });

    server.begin();

}
void setup() {
    delay(1000);
    Serial.begin(115200);
    delay(10);
    Serial.println("\r\n");
    WiFi.softAP(ssid, password);
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
    Serial.print("Port: ");
    Serial.println(port);
    startWebSocket();
    Serial.println("\r\nWebSocket server started.");
}

void loop() {
    delay(100);
    carHelper.drivingLoop(pDriveModel);
    carHelper.ledLoop(pLedModel);
}