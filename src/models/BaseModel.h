//
// Created by Artem on 02.06.2022.
//

#ifndef ESP32_CAR_BASEMODEL_H
#define ESP32_CAR_BASEMODEL_H
#include "Arduino.h"
struct BaseModel {
    String type = "";

    virtual String toJsonString() = 0;
};
#endif //ESP32_CAR_BASEMODEL_H
