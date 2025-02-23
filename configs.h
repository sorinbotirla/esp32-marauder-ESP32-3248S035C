#pragma once

#ifndef configs_h

  #define configs_h

  #define POLISH_POTATO

  #define ROTATION_PORTRAIT 0
  #define ROTATION_LANDSCAPE 1

  #define TFT_MODEL_COLOR 2 // 1 - blue display, 2 - red display

  #ifndef CALIBRATION_PORTRAIT 
    #ifndef CALIBRATION_LANDSCAPE 
      #if TFT_MODEL_COLOR == 1  // blue display
        #define CALIBRATION_PORTRAIT { 233, 3539, 200, 3511, 0 }
        #define CALIBRATION_LANDSCAPE { 215, 3498, 267, 3553, 5 }
      #elif TFT_MODEL_COLOR == 2  // red display
        #define CALIBRATION_PORTRAIT { 327, 3438, 404, 3468, 4 }
        #define CALIBRATION_LANDSCAPE { 355, 3512, 293, 3458, 7 }
      #endif
    #endif
  #endif

  //// BOARD TARGETS
  #define MARAUDER_SUNTON35



  // BEGIN LED STRIP MOD CONFIG
  // change this number if you want to use a single or dual led strip mod
  #define LED_STRIP_MOD 1 // 0 - disabled, 1 - single led strip, 2 - dual led strip

  #ifdef LED_STRIP_MOD
    #if LED_STRIP_MOD == 1
      #define SINGLE_LED_STRIP
    #elif LED_STRIP_MOD == 2
      #define DUAL_LED_STRIP
    #endif
  #endif

  #ifdef DUAL_LED_STRIP
    // if you're using 2 led strips edit these values
    #define TOTAL_PIXELS 10 // total pixels used on both strips (wifi/bt strip + gps strip)
    #define FIRST_PIXEL 0 // first pixel used
    #define FIRST_PIXEL_STRIP_WIFI 0 // first pixel of the wifi/bt strip
    #define LAST_PIXEL_STRIP_WIFI 4 // last pixel of the wifi/bt strip - must not be higher than TOTAL_PIXELS
    #define FIRST_PIXEL_STRIP_GPS 5 // first pixel of the gps strip
    #define LAST_PIXEL_STRIP_GPS 9 // last pixel of the gps strip - must not be higher than TOTAL_PIXELS

    #define TOTAL_PIXELS_STRIP_WIFI LAST_PIXEL_STRIP_WIFI - FIRST_PIXEL_STRIP_WIFI
    #define TOTAL_PIXELS_STRIP_GPS LAST_PIXEL_STRIP_GPS - FIRST_PIXEL_STRIP_GPS
  #else 

    // if you're using a single led strip edit these values
    #define TOTAL_PIXELS 7 // total pixels used for the single led strip
    #define FIRST_PIXEL 0
    #define FIRST_PIXEL_STRIP_WIFI FIRST_PIXEL // first pixel of the wifi/bt strip
    #define LAST_PIXEL_STRIP_WIFI TOTAL_PIXELS // last pixel of the wifi/bt strip - must not be higher than TOTAL_PIXELS
    #define FIRST_PIXEL_STRIP_GPS FIRST_PIXEL // first pixel of the gps strip
    #define LAST_PIXEL_STRIP_GPS TOTAL_PIXELS // last pixel of the gps strip - must not be higher than TOTAL_PIXELS

    #define TOTAL_PIXELS_STRIP_WIFI LAST_PIXEL_STRIP_WIFI - FIRST_PIXEL_STRIP_WIFI
    #define TOTAL_PIXELS_STRIP_GPS LAST_PIXEL_STRIP_GPS - FIRST_PIXEL_STRIP_GPS
  #endif

  // END LED STRIP MOD CONFIG

  //// END BOARD TARGETS

  #define MARAUDER_VERSION "v2.55 Escape Edition"

  //// HARDWARE NAMES
  #if defined(MARAUDER_SUNTON35)
    #define HARDWARE_NAME "Marauder Sunton 3.5"
  #else
    #define HARDWARE_NAME "ESP32"
  #endif

  //// END HARDWARE NAMES

 //// BOARD FEATURES
  
  #if defined(MARAUDER_SUNTON35)
    //#define FLIPPER_ZERO_HAT
    // #define HAS_BATTERY
    #define HAS_BT
    #define HAS_BT_REMOTE
    // #define HAS_BUTTONS
    #define HAS_NEOPIXEL_LED
    //#define HAS_PWR_MGMT
    #define HAS_SCREEN
    #define HAS_SD
    #define USE_SD
    // #define HAS_TEMP_SENSOR
    #define HAS_GPS
  #endif

  
  //// END BOARD FEATURES

  //// POWER MANAGEMENT
  #ifdef HAS_PWR_MGMT
    #ifdef MARAUDER_M5STICKC
      #include "AXP192.h"
    #endif
  #endif
  //// END POWER MANAGEMENT

  //// BUTTON DEFINITIONS
  #ifdef HAS_BUTTONS

    #ifdef MARAUDER_SUNTON35
      #define L_BTN -1
      #define C_BTN 0
      #define U_BTN -1
      #define R_BTN -1
      #define D_BTN -1

      //#define HAS_L
      //#define HAS_R
      //#define HAS_U
      //#define HAS_D
      #define HAS_C

      #define L_PULL true
      #define C_PULL true
      #define U_PULL true
      #define R_PULL true
      #define D_PULL true
    #endif

  #endif
  //// END BUTTON DEFINITIONS

  //// DISPLAY DEFINITIONS
  #ifdef HAS_SCREEN

    #ifdef MARAUDER_SUNTON35 
      #define MENU_BUTTON_SPACING_LEFT 40

      #define SCREEN_CHAR_WIDTH 40
      #define HAS_ST7796
    
      #define BANNER_TEXT_SIZE 2


      #define TFT_DIY
    
      #define SCREEN_WIDTH TFT_WIDTH
      #define SCREEN_HEIGHT TFT_HEIGHT
      #define HEIGHT_1 TFT_WIDTH
      #define WIDTH_1 TFT_HEIGHT
      #define STANDARD_FONT_CHAR_LIMIT (TFT_WIDTH/6) // number of characters on a single line with normal font
      #define TEXT_HEIGHT 24 // Height of text to be printed and scrolled
      #define BOT_FIXED_AREA 0 // Number of lines in bottom fixed area (lines counted from bottom of screen)
      #define TOP_FIXED_AREA 48 // Number of lines in top fixed area (lines counted from top of screen)
      #define YMAX 480 // Bottom of screen area
      #define minimum(a,b)     (((a) < (b)) ? (a) : (b))
      //#define MENU_FONT NULL
      #define MENU_FONT &FreeMono9pt7b // Winner
      //#define MENU_FONT &FreeMonoBold9pt7b
      //#define MENU_FONT &FreeSans9pt7b
      //#define MENU_FONT &FreeSansBold9pt7b
      #define BUTTON_SCREEN_LIMIT 12
      #define BUTTON_ARRAY_LEN 12
      #define STATUS_BAR_WIDTH 16
      #define LVGL_TICK_PERIOD 6

      #define FRAME_X 100
      #define FRAME_Y 64
      #define FRAME_W 160
      #define FRAME_H 50
    
      // Red zone size
      #define REDBUTTON_X FRAME_X
      #define REDBUTTON_Y FRAME_Y
      #define REDBUTTON_W (FRAME_W/2)
      #define REDBUTTON_H FRAME_H
    
      // Green zone size
      #define GREENBUTTON_X (REDBUTTON_X + REDBUTTON_W)
      #define GREENBUTTON_Y FRAME_Y
      #define GREENBUTTON_W (FRAME_W/2)
      #define GREENBUTTON_H FRAME_H
    
      #define STATUSBAR_COLOR 0x4A49
    
      #define KIT_LED_BUILTIN -1


      #define TFT_BL   27            // LED back-light control pin
      #define TFT_BACKLIGHT_ON HIGH  // Level to turn ON back-light (HIGH or LOW)

      #define TFT_MISO 12 // or SDO
      #define TFT_MOSI 13 // In some display driver board, it might be written as "SDA" or SDI
      #define TFT_SCLK 14
      #define TFT_CS   15  // Chip select control pin
      #define TFT_DC   2  // Data Command control pin (OR RS)
      #define TFT_RST  -1  // Reset pin (could connect to Arduino RESET pin)
      #define TFT_BL   27  // LED back-light

      
      #define SPI_FREQUENCY  65000000
      #define SPI_READ_FREQUENCY  20000000
      #define SPI_TOUCH_FREQUENCY  2500000  //2500000

      // #define TOUCH_CS 33     // Chip select pin (T_CS) of touch screen
      
      #define TOUCH_SDA  33
      #define TOUCH_SCL  32
      #define TOUCH_INT 21
      #define TOUCH_RST 25

      #define TOUCH_WIDTH  320
      #define TOUCH_HEIGHT 480

      // Change the width and height if required (defined in portrait mode)
      // or use the constructor to over-ride defaults
  
      #define TFT_WIDTH  320
      #define TFT_HEIGHT 480
 

      // Generic commands used by TFT_eSPI.cpp
      #define TFT_NOP     0x00
      #define TFT_SWRST   0x01

      #define TFT_INVOFF  0x20
      #define TFT_INVON   0x21

      #define TFT_DISPOFF 0x28
      #define TFT_DISPON  0x29

      #define TFT_CASET   0x2A
      #define TFT_PASET   0x2B
      #define TFT_RAMWR   0x2C
      #define TFT_RAMRD   0x2E

      #define TFT_MADCTL  0x36
      #define TFT_MAD_MY  0x80
      #define TFT_MAD_MX  0x40
      #define TFT_MAD_MV  0x20
      #define TFT_MAD_ML  0x10
      #define TFT_MAD_BGR 0x08
      #define TFT_MAD_MH  0x10
      #define TFT_MAD_RGB 0x00

      #ifdef TFT_RGB_ORDER
        #if (TFT_RGB_ORDER == 1)
          #define TFT_MAD_COLOR_ORDER TFT_MAD_RGB
        #else
          #define TFT_MAD_COLOR_ORDER TFT_MAD_BGR
        #endif
      #else
        #define TFT_MAD_COLOR_ORDER TFT_MAD_BGR
      #endif

      // ST7796 specific commands
      #define ST7796_NOP     0x00
      #define ST7796_SWRESET 0x01
      #define ST7796_RDDID   0x04
      #define ST7796_RDDST   0x09

      #define ST7796_SLPIN   0x10
      #define ST7796_SLPOUT  0x11
      #define ST7796_PTLON   0x12
      #define ST7796_NORON   0x13

      #define ST7796_RDMODE  0x0A
      #define ST7796_RDMADCTL  0x0B
      #define ST7796_RDPIXFMT  0x0C
      #define ST7796_RDIMGFMT  0x0A
      #define ST7796_RDSELFDIAG  0x0F

      #define ST7796_INVOFF  0x20
      #define ST7796_INVON   0x21

      #define ST7796_DISPOFF 0x28
      #define ST7796_DISPON  0x29

      #define ST7796_CASET   0x2A
      #define ST7796_PASET   0x2B
      #define ST7796_RAMWR   0x2C
      #define ST7796_RAMRD   0x2E

      #define ST7796_PTLAR   0x30
      #define ST7796_VSCRDEF 0x33
      #define ST7796_MADCTL  0x36
      #define ST7796_VSCRSADD 0x37
      #define ST7796_PIXFMT  0x3A

      #define ST7796_WRDISBV  0x51
      #define ST7796_RDDISBV  0x52
      #define ST7796_WRCTRLD  0x53

      #define ST7796_FRMCTR1 0xB1
      #define ST7796_FRMCTR2 0xB2
      #define ST7796_FRMCTR3 0xB3
      #define ST7796_INVCTR  0xB4
      #define ST7796_DFUNCTR 0xB6

      #define ST7796_PWCTR1  0xC0
      #define ST7796_PWCTR2  0xC1
      #define ST7796_PWCTR3  0xC2

      #define ST7796_VMCTR1  0xC5
      #define ST7796_VMCOFF  0xC6

      #define ST7796_RDID4   0xD3

      #define ST7796_GMCTRP1 0xE0
      #define ST7796_GMCTRN1 0xE1

      #define ST7796_MADCTL_MY  0x80
      #define ST7796_MADCTL_MX  0x40
      #define ST7796_MADCTL_MV  0x20
      #define ST7796_MADCTL_ML  0x10
      #define ST7796_MADCTL_RGB 0x00
      #define ST7796_MADCTL_BGR 0x08
      #define ST7796_MADCTL_MH  0x04

      
    #endif 

  #endif
  //// END DISPLAY DEFINITIONS

  
  #if defined(MARAUDER_SUNTON35)
    #define BANNER_TIME 100
    
    #define COMMAND_PREFIX "!"
    
    // Keypad start position, key sizes and spacing
    #define KEY_X 120 // Centre of key
    #define KEY_Y 50
    #define KEY_W 320 // Width and height
    #define KEY_H 22
    #define KEY_SPACING_X 0 // X and Y gap
    #define KEY_SPACING_Y 1
    #define KEY_TEXTSIZE 1   // Font size multiplier
    #define ICON_W 22
    #define ICON_H 22
    #define BUTTON_PADDING 22
    //#define BUTTON_ARRAY_LEN 5 // TBC ALL
  #endif

  //// END MENU DEFINITIONS

  //// SD DEFINITIONS
  #if defined(USE_SD)

    
    #ifdef MARAUDER_SUNTON35
      #define SD_CS 5
    #endif

    
  #endif
  //// END SD DEFINITIONS

  //// SCREEN STUFF
  #ifndef HAS_SCREEN

    #define TFT_WHITE 0
    #define TFT_CYAN 0
    #define TFT_BLUE 0
    #define TFT_RED 0
    #define TFT_GREEN 0
    #define TFT_GREY 0
    #define TFT_GRAY 0
    #define TFT_MAGENTA 0
    #define TFT_VIOLET 0
    #define TFT_ORANGE 0
    #define TFT_YELLOW 0
    #define STANDARD_FONT_CHAR_LIMIT 60
    #define FLASH_BUTTON -1

    #include <FS.h>
    #include <functional>
    #include <LinkedList.h>
    #include "SPIFFS.h"
    #include "Assets.h"

  #endif
  //// END SCREEN STUFF

  //// MEMORY LOWER LIMIT STUFF
  // These values are in bytes
  #ifdef MARAUDER_SUNTON35)
    #define MEM_LOWER_LIM 20000
  #endif
  //// END MEMORY LOWER LIMIT STUFF

  //// NEOPIXEL STUFF  
  #ifdef HAS_NEOPIXEL_LED
    
    #if defined(MARAUDER_SUNTON35)
      #define PIN 17 // this is the pin we need for NEOPIXEL
    #endif
  
  #endif
  //// END NEOPIXEL STUFF

  //// EVIL PORTAL STUFF
  #if defined(MARAUDER_SUNTON35)
    // #define MAX_HTML_SIZE 11400
    #define MAX_HTML_SIZE 20000
  #else
    #define MAX_HTML_SIZE 20000
  #endif
  //// END EVIL PORTAL STUFF

  //// GPS STUFF
  #ifdef HAS_GPS
    #if defined(MARAUDER_SUNTON35)
      #define GPS_SERIAL_INDEX 2
      #define GPS_TX 4
      // #define GPS_RX 13
      #define GPS_RX 26
      #define mac_history_len 512 // TBC
    #endif
  #else
    #define mac_history_len 512
  #endif
  //// END GPS STUFF

  //// MARAUDER TITLE STUFF
  #if defined(MARAUDER_SUNTON35)
    #define MARAUDER_TITLE_BYTES 13578
  #else
    #define MARAUDER_TITLE_BYTES 13578
  #endif
  //// END MARAUDER TITLE STUFF

#endif
