#include "ui.h"
#include <Adafruit_GFX.h>   // Core graphics library
#include <Adafruit_ILI9341.h> // Hardware-specific library

// Zastąp piny, jeśli używasz innych
#define TFT_CS    10
#define TFT_DC     9
#define TFT_RST    8 

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

void setupUI() {
  tft.begin();
  tft.setRotation(1); // Ustaw rotację ekranu, jeśli to konieczne
  tft.fillScreen(ILI9341_BLACK);
}

void drawFrame(int x, int y, int w, int h, uint16_t color) {
  tft.drawRect(x, y, w, h, color);
}

void drawText(int x, int y, const char* text, uint16_t color, uint8_t size) {
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(size);
  tft.print(text);
}
