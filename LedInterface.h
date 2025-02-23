#pragma once

#ifndef LedInterface_h
#define LedInterface_h

#include "configs.h"
#include "settings.h"
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define MODE_OFF 0
#define MODE_RAINBOW 1
#define MODE_ATTACK 2
#define MODE_SNIFF 3
#define MODE_CUSTOM 4

#define MODE_ATTACK_WIFI 5
#define MODE_SNIFF_WIFI 6
#define MODE_SCAN_WIFI 7
#define MODE_SERVE_WIFI 8
#define MODE_ATTACK_BT 9
#define MODE_SNIFF_BT 10
#define MODE_SCAN_BT 11
#define MODE_GPS_KITT 12
#define MODE_GPS_NOFIX 13
#define MODE_GPS_FIX 14

#define MODE_RASTA 15 // 420 not allowed lol


extern Settings settings_obj;
extern Adafruit_NeoPixel strip;

class LedInterface {

  private:
    uint32_t initTime = 0;

    uint8_t current_fade_itter = 1;
    uint8_t wheel_pos = 255;
    uint8_t wheel_speed = 1; // lower = slower

    //begin custom pixel vars
    int currentWifiBtPixel = 0;
    int currentGpsPixel = 0;
    uint8_t kittDirection = 1; // 0 is going -- 1, is going ++
    //end custom pixel vars

    uint32_t Wheel(byte WheelPos);

    uint8_t current_mode = MODE_OFF;

    void rainbow();
    void scanWifi();
    void ledOff();
    void attackLed();
    void sniffLed();

    // begin custom led modes
    void swipeLedCenter(uint32_t currentTime, String color);
    void swipeLedRight(uint32_t currentTime, String color);

    void ledAttackWifi(uint32_t currentTime);
    void ledSniffWifi(uint32_t currentTime);
    void ledScanWifi(uint32_t currentTime);
    void ledServeWifi(uint32_t currentTime);

    void ledAttackBt(uint32_t currentTime);
    void ledSniffBt(uint32_t currentTime);
    void ledScanBt(uint32_t currentTime);

    void ledGpsKitt(uint32_t currentTime, String color);
    void ledGpsNofix(uint32_t currentTime);
    void ledGpsFix(uint32_t currentTime);

    void ledRasta(uint32_t currentTime);
    // end custom led modes
  
  public:
    LedInterface();

    void RunSetup();
    void main(uint32_t currentTime);

    void setMode(uint8_t);
    void setColor(int r, int g, int b);
    uint8_t getMode();
    
  
};

#endif
