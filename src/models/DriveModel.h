//
// Created by Artem on 02.06.2022.
//

#ifndef ESP32_CAR_DRIVEMODEL_H
#define ESP32_CAR_DRIVEMODEL_H
#include "BaseModel.h"
#include <ArduinoJson.h>
struct DriveModel :  BaseModel {
    int speed = 0;
    int direction = 0;
    String type = "DriveModel";
    String toJsonString(){
        StaticJsonDocument<200> doc;
        JsonObject root = doc.to<JsonObject>();
        root["type"] = type;
        root["direction"] = direction;
        root["speed"] = speed;
        String output;
        serializeJson(root,output);
        return output;
    };
};
#endif //ESP32_CAR_DRIVEMODEL_H
