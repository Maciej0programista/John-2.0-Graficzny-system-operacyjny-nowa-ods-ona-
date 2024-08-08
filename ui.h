#ifndef UI_H
#define UI_H

#include <Adafruit_GFX.h>   // Core graphics library
#include <Adafruit_ILI9341.h> // Hardware-specific library

void setupUI();
void drawFrame(int x, int y, int w, int h, uint16_t color);
void drawText(int x, int y, const char* text, uint16_t color, uint8_t size);
// Deklaracje innych funkcji do rysowania UI

#endif
