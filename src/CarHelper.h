//
// Created by Artem on 02.06.2022.
//

#ifndef ESP32_CAR_CARHELPER_H
#define ESP32_CAR_CARHELPER_H
#include "./models/DriveModel.h"
#include "models/LedModel.h"
#include <ArduinoJson.h>
class CarHelper {

public:
    CarHelper();
    void updateDriveStructure(DriveModel *driveModel, JsonObject &object);
    void updateLedStructure(LedModel *ledModel, JsonObject &object);
    void drivingLoop(DriveModel *driveModel);
    void ledLoop(LedModel *ledModel);
};
#endif //ESP32_CAR_CARHELPER_H
