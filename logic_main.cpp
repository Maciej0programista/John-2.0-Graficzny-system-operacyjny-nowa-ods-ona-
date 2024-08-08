#include "logic_main.h"
#include <LiquidCrystal.h>
#include "logic_lua.h"
#include <Keypad.h>
#include <EEPROM.h>
#include "ui.h"

// Inicjalizacja ekranu LCD (zastąp piny jeśli to konieczne)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Konfiguracja klawiatury
const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; // Podłączenie pinów wierszy - dostosuj do swojego układu
byte colPins[COLS] = {5, 4, 3, 2}; // Podłączenie pinów kolumn - dostosuj do swojego układu
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// Zmienna do przechowywania stanu włączenia/wyłączenia
bool isOn = false;

// Zmienna do przechowywania czasu ostatniego wciśnięcia przycisku #
unsigned long lastHashPressTime = 0;

// Zmienna do przechowywania czasu ostatniego wciśnięcia przycisku *
unsigned long lastStarPressTime = 0;

// Pozycja kursora na ekranie (dla nawigacji)
int cursorX = 0;
int cursorY = 0;

// Maksymalna ilość aplikacji w rzędzie
const int maxAppsPerRow = 2;

// Maksymalna ilość aplikacji
const int maxApps = 9; 

bool inSettings = false;

// Funkcja do obsługi klawiatury
char readKeypad() {
  char key = keypad.getKey();
  if (key) {
    return key;
  } else {
    return NO_KEY;
  }
}

void setupMainLogic() {
  lcd.begin(16, 2);
  setupUI();
  // Ekran powitalny
  tft.fillScreen(ILI9341_BLACK);
  drawText(50, 80, "Welcome to", ILI9341_WHITE, 2);
  drawText(30, 100, "John 2.0", ILI9341_WHITE, 2);
  delay(3000);
  tft.fillScreen(ILI9341_BLACK);

  // Sprawdzenie, czy to pierwsze uruchomienie
  if (EEPROM.read(0) == 0) {
    // Ustaw flagę pierwszego uruchomienia
    EEPROM.write(0, 1);

    // Tworzenie folderu "app" na karcie SD
    if (createAppFolder()) {
      tft.fillScreen(ILI9341_BLACK);
      drawText(40, 80, "Folder /app", ILI9341_WHITE, 2);
      drawText(10, 100, "utworzony", ILI9341_WHITE, 2);
      delay(3000);
    } else {
      tft.fillScreen(ILI9341_BLACK);
      drawText(10, 80, "Błąd tworzenia", ILI9341_WHITE, 2);
      drawText(10, 100, "folderu /app", ILI9341_WHITE, 2);
      delay(3000);
    }
  } else {
    Serial.println("Folder /app już istnieje.");
  }

  isOn = true;
  installLuaApps();
  redrawMainMenu();
}

void loopMainLogic() {
  // Odczytywanie danych z klawiatury
  char keyPressed = readKeypad();

  // Obsługa przycisku # (włączanie/wyłączanie)
  if (keyPressed == '#') {
    if (millis() - lastHashPressTime > 5000) {
      // Przytrzymanie przycisku # przez 5 sekund
      isOn = !isOn;
      if (isOn) {
        tft.fillScreen(ILI9341_BLACK);
        drawText(50, 80, "John 2.0", ILI9341_WHITE, 2);
        installLuaApps();
        delay(2000);
        redrawMainMenu();
      } else {
        tft.fillScreen(ILI9341_BLACK);
        drawText(50, 80, "Wylaczanie...", ILI9341_WHITE, 2);
        delay(1000);
        // Przejdź w tryb uśpienia
        LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
      }
    }
  } else {
    lastHashPressTime = millis();
  }

  if (isOn) {
    if (inSettings) {
      handleSettingsInput(keyPressed);
    } else {
      handleMainMenuInput(keyPressed);
    }
  }
}

void handleMainMenuInput(char keyPressed) {
  switch (keyPressed) {
    case 'A': // Strzałka w górę
      cursorY = (cursorY - 1 + (maxApps / maxAppsPerRow)) % (maxApps / maxAppsPerRow);
      redrawMainMenu();
      break;
    case 'B': // Strzałka w dół
      cursorY = (cursorY + 1) % (maxApps / maxAppsPerRow);
      redrawMainMenu();
      break;
    case 'D': // Strzałka w prawo
      cursorX = (cursorX + 1) % maxAppsPerRow;
      redrawMainMenu();
      break;
    case 'C': // Strzałka w lewo
      cursorX = (cursorX - 1 + maxAppsPerRow) % maxAppsPerRow;
      redrawMainMenu();
      break;
    case '#': // Enter
      int selectedApp = cursorY * maxAppsPerRow + cursorX + 1;
      if (selectedApp == 10) {
        inSettings = true;
        redrawSettingsMenu();
      } else if (selectedApp <= maxApps) {
        openLuaScript(String("app") + selectedApp);
      }
      break;
    case '*': // Scroll down / Page Up
      if (millis() - lastStarPressTime < 500) {
        // Pojedyncze kliknięcie: Scroll down o 2 linie
        cursorY = (cursorY + 2) % (maxApps / maxAppsPerRow);
      } else if (millis() - lastStarPressTime > 1000) {
        // Przytrzymanie: Scroll up o 1 linię na sekundę
        cursorY = (cursorY - 1 + (maxApps / maxAppsPerRow)) % (maxApps / maxAppsPerRow);
      }
      redrawMainMenu();
      break;
  }
  lastStarPressTime = millis();
}

void handleSettingsInput(char keyPressed) {
  // Dodaj obsługę inputu w menu ustawień
  // ...
  if (keyPressed == 'C' && digitalRead(keypad.getColPin(3)) == LOW) { // # + * (wciśnięte jednocześnie)
    inSettings = false;
    redrawMainMenu();
  }
}

void redrawMainMenu() {
  tft.fillScreen(ILI9341_BLACK);

  for (int i = 0; i < maxApps; i++) {
    int row = i / maxAppsPerRow;
    int col = i % maxAppsPerRow;
    int x = 10 + col * 115;
    int y = 10 + row * 40;
    if (row == cursorY && col == cursorX) {
      drawFrame(x, y, 100, 30, ILI9341_BLUE);
    } else {
      drawFrame(x, y, 100, 30, ILI9341_WHITE);
    }
    drawText(x + 10, y + 8, String("App ") + (i + 1), ILI9341_WHITE, 2);
  }

  // Rysuj ramkę Ustawienia tylko gdy kursor jest na ostatnim rzędzie
  if (cursorY == (maxApps - 1) / maxAppsPerRow) { 
    if (cursorX == 0) {
      drawFrame(10, 130, 100, 30, ILI9341_BLUE);
    } else {
      drawFrame(10, 130, 100, 30, ILI9341_WHITE);
    }
    drawText(20, 138, "Ustawienia", ILI9341_WHITE, 2);
  }
}

void redrawSettingsMenu() {
  tft.fillScreen(ILI9341_BLACK);
  // Dodaj rysowanie menu ustawień
  // ...
}
