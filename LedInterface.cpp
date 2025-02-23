#include "LedInterface.h"

LedInterface::LedInterface() {

}

void LedInterface::RunSetup() {
  //Serial.println("Setting neopixel to black...");
  strip.setBrightness(0);
  strip.begin();
  for (int p = FIRST_PIXEL; p < FIRST_PIXEL + TOTAL_PIXELS; p++){
    strip.setPixelColor(p, strip.Color(0, 0, 0));
  }
  strip.show();
  delay(100);
  strip.setBrightness(50);
  for (int p = FIRST_PIXEL; p < FIRST_PIXEL + TOTAL_PIXELS; p++){
    strip.setPixelColor(p, strip.Color(0, 0, 0));
  }
  strip.show();
  this->initTime = millis();
  Serial.println("initTime: "+ (String)this->initTime);
}

void LedInterface::main(uint32_t currentTime) {
  if ((!settings_obj.loadSetting<bool>("EnableLED")) ||
      (this->current_mode == MODE_OFF)) {
    this->ledOff();
    return;
  }

  else if (this->current_mode == MODE_RAINBOW) {
    this->rainbow();
  }
  else if (this->current_mode == MODE_ATTACK) {
    this->attackLed();
  }
  else if (this->current_mode == MODE_SNIFF) {
    this->sniffLed();
  }
  else if (this->current_mode == MODE_CUSTOM) {
    return;
  }

  // begin custom modes
  else if (this->current_mode == MODE_ATTACK_WIFI){
    this->ledAttackWifi(currentTime);
  }
  else if (this->current_mode == MODE_SNIFF_WIFI){
    this->ledSniffWifi(currentTime);
  }
  else if (this->current_mode == MODE_SCAN_WIFI){
    this->ledScanWifi(currentTime);
  }
  else if (this->current_mode == MODE_SERVE_WIFI){
    this->ledServeWifi(currentTime);
  }
  else if (this->current_mode == MODE_ATTACK_BT){
    this->ledAttackBt(currentTime);
  }
  else if (this->current_mode == MODE_SNIFF_BT){
    this->ledSniffBt(currentTime);
  }
  else if (this->current_mode == MODE_SCAN_BT){
    this->ledScanBt(currentTime);
  }
  else if (this->current_mode == MODE_GPS_KITT){
    this->ledGpsKitt(currentTime, "red");
  }
  else if (this->current_mode == MODE_GPS_NOFIX){
    this->ledGpsNofix(currentTime);
  }
  else if (this->current_mode == MODE_GPS_FIX){
    this->ledGpsFix(currentTime);
  }
  else if (this->current_mode == MODE_RASTA){
    this->ledRasta(currentTime);
  }
  // end custom modes
  else {
    this->ledOff();
  }
};

void LedInterface::setMode(uint8_t new_mode) {
  this->current_mode = new_mode;
}

uint8_t LedInterface::getMode() {
  return this->current_mode;
}

void LedInterface::setColor(int r, int g, int b) {
  for (int p = FIRST_PIXEL; p < FIRST_PIXEL + TOTAL_PIXELS; p++){
    strip.setPixelColor(p, strip.Color(r, g, b));
  }
  strip.show();  
}

void LedInterface::sniffLed() {
  this->setColor(0, 0, 255);
}

void LedInterface::attackLed() {
  this->setColor(255, 0, 0);
}

void LedInterface::ledOff() {
  this->setColor(0, 0, 0);
}

void LedInterface::rainbow() {
  for (int p = FIRST_PIXEL; p < TOTAL_PIXELS; p++){
    strip.setPixelColor(p, this->Wheel((0 * 256 / 100 + this->wheel_pos) % 256));
  }
  strip.show();

  this->current_fade_itter++;

  this->wheel_pos = this->wheel_pos - this->wheel_speed;
  if (this->wheel_pos < 0)
    this->wheel_pos = 255;
}


void LedInterface::swipeLedCenter(uint32_t currentTime, String color = "green"){
  if (this->currentWifiBtPixel >= FIRST_PIXEL_STRIP_WIFI && this->currentWifiBtPixel <= TOTAL_PIXELS_STRIP_WIFI) {
    uint8_t pixelIsVisible = 0;

    for (uint8_t r = FIRST_PIXEL_STRIP_WIFI; r <= LAST_PIXEL_STRIP_WIFI; r++){
      if (r == this->currentWifiBtPixel && r <= LAST_PIXEL_STRIP_WIFI / 2) {
        pixelIsVisible = 1;
        if (color == "red") {
          strip.setPixelColor(this->currentWifiBtPixel, strip.Color(255, 0, 0));
          strip.setPixelColor(LAST_PIXEL_STRIP_WIFI - this->currentWifiBtPixel, strip.Color(255, 0, 0));
        } else if (color == "green") {
          strip.setPixelColor(this->currentWifiBtPixel, strip.Color(0, 255, 0));
          strip.setPixelColor(LAST_PIXEL_STRIP_WIFI - this->currentWifiBtPixel, strip.Color(0, 255, 0));
       
        } else if (color == "blue") {
          strip.setPixelColor(this->currentWifiBtPixel, strip.Color(0, 0, 255));
          strip.setPixelColor(LAST_PIXEL_STRIP_WIFI - this->currentWifiBtPixel, strip.Color(0, 0, 255));
        }
        for (uint8_t p = FIRST_PIXEL_STRIP_WIFI; p <= LAST_PIXEL_STRIP_WIFI; p++){
          if (p != this->currentWifiBtPixel && p != LAST_PIXEL_STRIP_WIFI - this->currentWifiBtPixel) {
            strip.setPixelColor(p, strip.Color(0, 0, 0));
          }
        }
      }
    }

    if (pixelIsVisible == 0) {
        for (uint8_t p = FIRST_PIXEL_STRIP_WIFI; p <= LAST_PIXEL_STRIP_WIFI; p++){
            strip.setPixelColor(p, strip.Color(0, 0, 0));
        }
    }
  }
}

void LedInterface::swipeLedRight(uint32_t currentTime, String color = "green"){
  if (this->currentWifiBtPixel >= FIRST_PIXEL_STRIP_WIFI && this->currentWifiBtPixel <= TOTAL_PIXELS_STRIP_WIFI) {
    if (this->currentWifiBtPixel >= FIRST_PIXEL_STRIP_WIFI && this->currentWifiBtPixel <= LAST_PIXEL_STRIP_WIFI) {
      if (color == "red") {
        strip.setPixelColor(this->currentWifiBtPixel, strip.Color(255, 0, 0));
      } else if (color == "green") {
        strip.setPixelColor(this->currentWifiBtPixel, strip.Color(255, 255, 0));
      } else if (color == "blue") {
        strip.setPixelColor(this->currentWifiBtPixel, strip.Color(0, 0, 255));
      }
    }
    
    for (uint8_t p = FIRST_PIXEL_STRIP_WIFI; p <= LAST_PIXEL_STRIP_WIFI; p++){
      if (p != this->currentWifiBtPixel) {
        strip.setPixelColor(p, strip.Color(0, 0, 0));
      }
    }
  }
}


//begin custom led modes
void LedInterface::ledAttackWifi(uint32_t currentTime){
  #ifdef DUALLEDSTRIP
  if (currentTime - this->initTime > 20) { // miliseconds interval between led change
    this->initTime = currentTime;
    if (this->currentWifiBtPixel < FIRST_PIXEL_STRIP_WIFI) {
      this->currentWifiBtPixel = LAST_PIXEL_STRIP_WIFI + 10; // a small hack to move the current pixel at a defined offset without getting into other regions of the strip
    }
    this-swipeLedRight(currentTime, "red"));
    this->currentWifiBtPixel--;
    strip.show();
    // Serial.println("currentWifiBtPixel"+ (String) this->currentWifiBtPixel);
  }
  #else
  if (currentTime - this->initTime > 20) { // miliseconds interval between led change
    this->initTime = currentTime;
    if (this->currentWifiBtPixel < FIRST_PIXEL_STRIP_WIFI) {
      this->ledOff();
      this->currentWifiBtPixel = LAST_PIXEL_STRIP_WIFI + 10; // a small hack to move the current pixel at a defined offset without getting into other regions of the strip
    }
    this->swipeLedCenter(currentTime, "red");
    
    this->currentWifiBtPixel--;
    strip.show();
    // Serial.println("currentWifiBtPixel"+ (String) this->currentWifiBtPixel);
  }
  #endif
}
void LedInterface::ledSniffWifi(uint32_t currentTime){
  #ifdef DUALLEDSTRIP
  if (currentTime - this->initTime > 20) { // miliseconds interval between led change
    this->initTime = currentTime;
    if (this->currentWifiBtPixel > LAST_PIXEL_STRIP_WIFI) {
      this->currentWifiBtPixel = FIRST_PIXEL_STRIP_WIFI - 10; // a small hack to move the current pixel at a defined offset without getting into other regions of the strip
    }
    this-swipeLedRight(currentTime, "green"));
    this->currentWifiBtPixel++;
    strip.show();
    // Serial.println("currentWifiBtPixel"+ (String) this->currentWifiBtPixel);
  }
  #else
  if (currentTime - this->initTime > 20) { // miliseconds interval between led change
    this->initTime = currentTime;
    if (this->currentWifiBtPixel > LAST_PIXEL_STRIP_WIFI) {
      this->currentWifiBtPixel = FIRST_PIXEL_STRIP_WIFI - 10; // a small hack to move the current pixel at a defined offset without getting into other regions of the strip
    }
    this->swipeLedCenter(currentTime, "green");
    
    this->currentWifiBtPixel++;
    strip.show();
    // Serial.println("currentWifiBtPixel"+ (String) this->currentWifiBtPixel);
  }
  #endif
}
void LedInterface::ledScanWifi(uint32_t currentTime){
  #ifdef DUALLEDSTRIP
  if (currentTime - this->initTime > 50) { // miliseconds interval between led change
    this->initTime = currentTime;
    if (this->currentWifiBtPixel > LAST_PIXEL_STRIP_WIFI) {
      this->currentWifiBtPixel = FIRST_PIXEL_STRIP_WIFI - 20; // a small hack to move the current pixel at a defined offset without getting into other regions of the strip
    }
    this-swipeLedRight(currentTime, "green"));
    this->currentWifiBtPixel++;
    strip.show();
    // Serial.println("currentWifiBtPixel"+ (String) this->currentWifiBtPixel);
  }
  #else
  if (currentTime - this->initTime > 50) { // miliseconds interval between led change
    this->initTime = currentTime;
    if (this->currentWifiBtPixel > LAST_PIXEL_STRIP_WIFI) {
      this->currentWifiBtPixel = FIRST_PIXEL_STRIP_WIFI - 20; // a small hack to move the current pixel at a defined offset without getting into other regions of the strip
    }
    this->swipeLedCenter(currentTime, "green");
    
    this->currentWifiBtPixel++;
    strip.show();
    // Serial.println("currentWifiBtPixel"+ (String) this->currentWifiBtPixel);
  }
  #endif
}
void LedInterface::ledServeWifi(uint32_t currentTime){
  #ifdef DUALLEDSTRIP
  if (currentTime - this->initTime > 100) { // miliseconds interval between led change
    this->initTime = currentTime;
    if (this->currentWifiBtPixel > LAST_PIXEL_STRIP_WIFI) {
      this->currentWifiBtPixel = FIRST_PIXEL_STRIP_WIFI - 50; // a small hack to move the current pixel at a defined offset without getting into other regions of the strip
    }
    this-swipeLedRight(currentTime, "green"));
    this->currentWifiBtPixel++;
    strip.show();
    // Serial.println("currentWifiBtPixel"+ (String) this->currentWifiBtPixel);
  }
  #else
  if (currentTime - this->initTime > 100) { // miliseconds interval between led change
    this->initTime = currentTime;
    if (this->currentWifiBtPixel > LAST_PIXEL_STRIP_WIFI) {
      this->currentWifiBtPixel = FIRST_PIXEL_STRIP_WIFI - 50; // a small hack to move the current pixel at a defined offset without getting into other regions of the strip
    }
    this->swipeLedCenter(currentTime, "green");
    
    this->currentWifiBtPixel++;
    strip.show();
    // Serial.println("currentWifiBtPixel"+ (String) this->currentWifiBtPixel);
  }
  #endif
}
void LedInterface::ledAttackBt(uint32_t currentTime){
  #ifdef DUALLEDSTRIP
  if (currentTime - this->initTime > 20) { // miliseconds interval between led change
    this->initTime = currentTime;
    if (this->currentWifiBtPixel < FIRST_PIXEL_STRIP_WIFI) {
      this->currentWifiBtPixel = LAST_PIXEL_STRIP_WIFI + 10; // a small hack to move the current pixel at a defined offset without getting into other regions of the strip
    }
    this-swipeLedRight(currentTime, "blue"));
    this->currentWifiBtPixel--;
    strip.show();
    // Serial.println("currentWifiBtPixel"+ (String) this->currentWifiBtPixel);
  }
  #else
  if (currentTime - this->initTime > 20) { // miliseconds interval between led change
    this->initTime = currentTime;
    if (this->currentWifiBtPixel < FIRST_PIXEL_STRIP_WIFI) {
      this->ledOff();
      this->currentWifiBtPixel = LAST_PIXEL_STRIP_WIFI + 10; // a small hack to move the current pixel at a defined offset without getting into other regions of the strip
    }
    this->swipeLedCenter(currentTime, "blue");
    
    this->currentWifiBtPixel--;
    strip.show();
    // Serial.println("currentWifiBtPixel"+ (String) this->currentWifiBtPixel);
  }
  #endif
}
void LedInterface::ledSniffBt(uint32_t currentTime){
  #ifdef DUALLEDSTRIP
  if (currentTime - this->initTime > 20) { // miliseconds interval between led change
    this->initTime = currentTime;
    if (this->currentWifiBtPixel > LAST_PIXEL_STRIP_WIFI) {
      this->currentWifiBtPixel = FIRST_PIXEL_STRIP_WIFI - 10; // a small hack to move the current pixel at a defined offset without getting into other regions of the strip
    }
    this-swipeLedRight(currentTime, "blue"));
    this->currentWifiBtPixel++;
    strip.show();
    // Serial.println("currentWifiBtPixel"+ (String) this->currentWifiBtPixel);
  }
  #else
  if (currentTime - this->initTime > 20) { // miliseconds interval between led change
    this->initTime = currentTime;
    if (this->currentWifiBtPixel > LAST_PIXEL_STRIP_WIFI) {
      this->currentWifiBtPixel = FIRST_PIXEL_STRIP_WIFI - 10; // a small hack to move the current pixel at a defined offset without getting into other regions of the strip
    }
    this->swipeLedCenter(currentTime, "blue");
    
    this->currentWifiBtPixel++;
    strip.show();
    // Serial.println("currentWifiBtPixel"+ (String) this->currentWifiBtPixel);
  }
  #endif
}
void LedInterface::ledScanBt(uint32_t currentTime){
  #ifdef DUALLEDSTRIP
  if (currentTime - this->initTime > 50) { // miliseconds interval between led change
    this->initTime = currentTime;
    if (this->currentWifiBtPixel > LAST_PIXEL_STRIP_WIFI) {
      this->currentWifiBtPixel = FIRST_PIXEL_STRIP_WIFI - 20; // a small hack to move the current pixel at a defined offset without getting into other regions of the strip
    }
    this-swipeLedRight(currentTime, "blue"));
    this->currentWifiBtPixel++;
    strip.show();
    // Serial.println("currentWifiBtPixel"+ (String) this->currentWifiBtPixel);
  }
  #else
  if (currentTime - this->initTime > 50) { // miliseconds interval between led change
    this->initTime = currentTime;
    if (this->currentWifiBtPixel > LAST_PIXEL_STRIP_WIFI) {
      this->currentWifiBtPixel = FIRST_PIXEL_STRIP_WIFI - 20; // a small hack to move the current pixel at a defined offset without getting into other regions of the strip
    }
    this->swipeLedCenter(currentTime, "blue");
    
    this->currentWifiBtPixel++;
    strip.show();
    // Serial.println("currentWifiBtPixel"+ (String) this->currentWifiBtPixel);
  }
  #endif
}
void LedInterface::ledGpsKitt(uint32_t currentTime, String color = "red"){
  if (currentTime - this->initTime > 100) { // miliseconds interval between led change
    this->initTime = currentTime;
    if (this->currentGpsPixel >= FIRST_PIXEL_STRIP_GPS && this->currentGpsPixel <= LAST_PIXEL_STRIP_GPS) {
      if (color == "red") {
       strip.setPixelColor(this->currentGpsPixel, strip.Color(255, 0, 0));
      } else if (color == "green") {
        strip.setPixelColor(this->currentGpsPixel, strip.Color(0, 255, 0));
      }
    }
    
    for (uint8_t p = FIRST_PIXEL_STRIP_GPS; p <= LAST_PIXEL_STRIP_GPS; p++){
      if (p != this->currentGpsPixel) {
        strip.setPixelColor(p, strip.Color(0, 0, 0));
      }
    }
    if (this->currentGpsPixel < FIRST_PIXEL_STRIP_GPS - 10 && this->kittDirection == 0) {
      this->kittDirection = 1;
    } else if (this->currentGpsPixel > LAST_PIXEL_STRIP_GPS + 10 && this->kittDirection == 1) {
      this->kittDirection = 0;
    }
    if (this->kittDirection == 1) {
        this->currentGpsPixel++;
    } else if (this->kittDirection == 0) {
        this->currentGpsPixel--;
    }
    
    strip.show();
    // Serial.println("currentGpsPixel"+ (String) this->currentGpsPixel);
  }
}
void LedInterface::ledGpsNofix(uint32_t currentTime){
  this->ledGpsKitt(currentTime, "red");
}
void LedInterface::ledGpsFix(uint32_t currentTime){
  this->ledGpsKitt(currentTime, "green");
}
void LedInterface::ledRasta(uint32_t currentTime){
  #ifdef DUALLEDSTRIP
    if (LAST_PIXEL_STRIP_WIFI > FIRST_PIXEL_STRIP_WIFI && TOTAL_PIXELS_STRIP_WIFI >= 3 
    && FIRST_PIXEL_STRIP_GPS < LAST_PIXEL_STRIP_GPS && TOTAL_PIXELS_STRIP_GPS >= 3) {
      for (int p = FIRST_PIXEL_STRIP_WIFI; p < ((int) LAST_PIXEL_STRIP_WIFI / 3); p++){
        strip.setPixelColor(p, strip.Color(255, 0, 0));
      }
      for (int p = ((int) LAST_PIXEL_STRIP_WIFI / 3); p < ((int) LAST_PIXEL_STRIP_WIFI / 3 * 2); p++){
        strip.setPixelColor(p, strip.Color(255, 255, 0));
      }
      for (int p = ((int) LAST_PIXEL_STRIP_WIFI / 3 * 2); p < LAST_PIXEL_STRIP_WIFI; p++){
        strip.setPixelColor(p, strip.Color(0, 255, 0));
      }

      for (int p = FIRST_PIXEL_STRIP_GPS; p < ((int) LAST_PIXEL_STRIP_GPS / 3); p++){
        strip.setPixelColor(p, strip.Color(255, 0, 0));
      }
      for (int p = ((int) LAST_PIXEL_STRIP_GPS / 3); p < ((int) LAST_PIXEL_STRIP_GPS / 3 * 2); p++){
        strip.setPixelColor(p, strip.Color(255, 255, 0));
      }
      for (int p = ((int) LAST_PIXEL_STRIP_GPS / 3 * 2); p < LAST_PIXEL_STRIP_GPS; p++){
        strip.setPixelColor(p, strip.Color(0, 255, 0));
      }
    }
  #else
    if (LAST_PIXEL_STRIP_WIFI > FIRST_PIXEL_STRIP_WIFI && TOTAL_PIXELS_STRIP_WIFI >= 3) {
      for (int p = FIRST_PIXEL_STRIP_WIFI; p < ((int) LAST_PIXEL_STRIP_WIFI / 3); p++){
        strip.setPixelColor(p, strip.Color(255, 0, 0));
      }
      for (int p = ((int) LAST_PIXEL_STRIP_WIFI / 3); p < ((int) LAST_PIXEL_STRIP_WIFI / 3 * 2); p++){
        strip.setPixelColor(p, strip.Color(255, 255, 0));
      }
      for (int p = ((int) LAST_PIXEL_STRIP_WIFI / 3 * 2); p < LAST_PIXEL_STRIP_WIFI; p++){
        strip.setPixelColor(p, strip.Color(0, 255, 0));
      }
      strip.show();
    }
  #endif
}
//end custom led modes

uint32_t LedInterface::Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
