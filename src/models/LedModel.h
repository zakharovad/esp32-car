//
// Created by Artem on 02.06.2022.
//

#ifndef ESP32_CAR_LEDMODEL_H
#define ESP32_CAR_LEDMODEL_H
#include "BaseModel.h"
#include <ArduinoJson.h>
struct LedModel :  BaseModel {
    int brightness = 0;
    String type = "LedModel";
    String toJsonString(){
        StaticJsonDocument<200> doc;
        JsonObject root = doc.to<JsonObject>();
        root["type"] = type;
        root["brightness"] = brightness;
        String output;
        serializeJson(root,output);
        return output;
    };
};
#endif //ESP32_CAR_LEDMODEL_H
