//
// Created by Artem on 07.06.2022.
//
#include <Arduino.h>
#include "esp_camera.h"
#include "CameraStreamer.h"
#include "AsyncJpegStreamResponse.cpp"

#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22
#define PART_BOUNDARY "123456789000000000000987654321"


CameraStreamer::CameraStreamer(){

    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sscb_sda = SIOD_GPIO_NUM;
    config.pin_sscb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;
        config.frame_size = FRAMESIZE_VGA;
        config.jpeg_quality = 10;
        config.fb_count = 3;

    // camera init
    esp_err_t err = esp_camera_init(&config);
    err != ESP_OK ? enable(false): enable(true);

    //drop down frame size for higher initial frame rate
/*    sensor_t * s = esp_camera_sensor_get();
    s->set_framesize(s, FRAMESIZE_VGA);
    s->set_quality(s, 20);*/
}
void CameraStreamer::streamHandler(AsyncWebServerRequest *request) {
    AsyncJpegStreamResponse *response = new AsyncJpegStreamResponse();
    response->addHeader("Access-Control-Allow-Origin", "*");
    request->send(response);
}
void CameraStreamer::captureHandler(AsyncWebServerRequest *request) {

    camera_fb_t * frame = NULL;
    frame = esp_camera_fb_get();

    request->send_P(200, "image/jpeg", (const uint8_t *)frame->buf, frame->len);

    esp_camera_fb_return(frame);
}
