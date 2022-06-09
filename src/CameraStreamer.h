//
// Created by Artem on 07.06.2022.
//

#ifndef ESP32_CAR_CAMERASTREAMER_H
#define ESP32_CAR_CAMERASTREAMER_H
#include "esp_camera.h"
//#include "esp_http_server.h"
#include "ESPAsyncWebServer.h"

class CameraStreamer{
private:
    bool _enabled;
    void enable(bool e){ _enabled = e; }
public:
    camera_config_t config;
    bool enabled() const { return _enabled; }
    CameraStreamer();
    void captureHandler(AsyncWebServerRequest * request);
    void streamHandler(AsyncWebServerRequest * request);
};
#endif //ESP32_CAR_CAMERASTREAMER_H
