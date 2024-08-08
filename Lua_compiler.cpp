#include "Lua_compiler.h"
#include <SD.h>

bool compileLuaApp(const char* appFolder, const char* outputFilename) {
  // 1. Otwórz folder aplikacji
  File appDir = SD.open(appFolder);
  if (!appDir) {
    Serial.print("Błąd: Nie można otworzyć folderu aplikacji: ");
    Serial.println(appFolder);
    return false;
  }

  // 2. Utwórz plik wyjściowy
  File outputFile = SD.open(outputFilename, FILE_WRITE);
  if (!outputFile) {
    Serial.print("Błąd: Nie można utworzyć pliku wyjściowego: ");
    Serial.println(outputFilename);
    appDir.close();
    return false;
  }

  // 3. Przeczytaj i skopiuj zawartość plików Lua do pliku wyjściowego
  while (true) {
    File entry = appDir.openNextFile();
    if (!entry) {
      // Brak więcej plików
      break;
    }
    if (entry.isDirectory()) {
      // Pomiń foldery
      continue;
    }
    if (entry.name().endsWith(".lua")) {
      Serial.print("Kompilowanie pliku: ");
      Serial.println(entry.name());
      // Skopiuj zawartość pliku do pliku wyjściowego
      while (entry.available()) {
        outputFile.write(entry.read());
      }
    }
    entry.close();
  }

  // 4. Zamknij pliki
  appDir.close();
  outputFile.close();

  Serial.print("Aplikacja Lua ");
  Serial.print(appFolder);
  Serial.print(" skompilowana do pliku ");
  Serial.println(outputFilename);
  return true;
}
