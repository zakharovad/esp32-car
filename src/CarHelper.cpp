//
// Created by Artem on 02.06.2022.
//
#include "CarHelper.h"
#include <Arduino.h>
#include <ArduinoJson.h>
//left motors
#define ENA_PIN 1 //for driver ena
#define IN1_PIN 14 //for driver in1
#define IN2_PIN 2 //for driver in1
#define PWM_ENA_PIN 0 //PWM for driver in1
//right motors
#define ENB_PIN 12 //for driver enb
#define IN3_PIN 15 //for driver in2
#define IN4_PIN 13 //for driver in2
#define PWM_ENB_PIN 1 //PWM for driver in2
//for driver  deceleration ratio
#define SPEED_COEF 3
//for brightness
#define LED_PIN 4
#define PWM_LED_PIN 2 //PWM for led
const unsigned int  moveForward = 1; //0001;
const unsigned int  moveBack = 2;//0010;
const unsigned int  moveLeft = 4;//0100;
const unsigned int  moveRight = 8;//1000;
const unsigned int  moveStop = 0;//0000;
CarHelper::CarHelper() {
    //start PWM channel setup
    ledcSetup(PWM_ENA_PIN, 50, 8);
    ledcSetup(PWM_ENB_PIN, 50, 8);
    ledcSetup(PWM_LED_PIN, 100, 8);
    //end PWM PWM channel setup
    pinMode (LED_PIN, OUTPUT);
    pinMode (ENA_PIN, OUTPUT);
    pinMode (ENB_PIN, OUTPUT);
    pinMode (IN1_PIN, OUTPUT);
    pinMode (IN2_PIN, OUTPUT);
    pinMode (IN3_PIN, OUTPUT);
    pinMode (IN4_PIN, OUTPUT);
    ledcAttachPin(ENA_PIN, PWM_ENA_PIN);
    ledcAttachPin(ENB_PIN, PWM_ENB_PIN);
    ledcAttachPin(LED_PIN, PWM_LED_PIN);

}
void CarHelper::updateDriveStructure(DriveModel *driveModel, JsonObject &object){
    JsonVariant speed = object.getMember("speed");
    JsonVariant direction = object.getMember("direction");
    driveModel->speed = speed.as<int>();
    driveModel->direction = direction.as<int>();

}
void CarHelper::updateLedStructure(LedModel *ledModel, JsonObject &object){
    JsonVariant brightness = object.getMember("brightness");
    ledModel->brightness = brightness.as<int>();

}
void CarHelper::ledLoop(LedModel *ledModel) {
    ledcWrite(PWM_LED_PIN, ledModel->brightness);
}
void CarHelper::driverUpdatePins(int in1, int in2, int in3, int in4){
    digitalWrite(IN1_PIN, in1);
    digitalWrite(IN2_PIN, in2);
    digitalWrite(IN3_PIN, in3);
    digitalWrite(IN4_PIN, in4);
}
void CarHelper::drivingLoop(DriveModel *driveModel){
    switch(driveModel->direction){
        case moveStop:
            this->driverUpdatePins(LOW, LOW, LOW, LOW);
            break;
        case moveForward:
            this->driverUpdatePins(HIGH, LOW, HIGH, LOW);
            break;
        case moveBack:
            this->driverUpdatePins(LOW, HIGH, LOW, HIGH);
            break;
        case moveRight:
            this->driverUpdatePins(HIGH, LOW, LOW, HIGH);
            break;
        case moveLeft:
            this->driverUpdatePins(LOW, HIGH, HIGH, LOW);
            break;
        case (moveForward | moveLeft):
            this->driverUpdatePins(LOW, HIGH, LOW, LOW);
            break;
        case (moveForward | moveRight):
            this->driverUpdatePins(HIGH, LOW, LOW, LOW);
            break;
        case (moveBack | moveLeft):
            this->driverUpdatePins(LOW, LOW, LOW, HIGH);
            break;
        case (moveBack | moveRight):
            this->driverUpdatePins(LOW, HIGH, LOW, LOW);
            break;

    }
}