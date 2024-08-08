#include "command_lua.h"
#include <Adafruit_ILI9341.h>
#include "ui.h"
#include <SD.h>

// Globalna zmienna tft z ui.cpp (zakładając, że jest zadeklarowana jako extern w ui.h)
extern Adafruit_ILI9341 tft; 

void registerLuaCommands(lua_State *L) {
  // Rejestruj funkcje Lua tutaj
  lua_register(L, "print", lua_print);
  lua_register(L, "drawPixel", lua_drawPixel);
  lua_register(L, "drawLine", lua_drawLine);
  lua_register(L, "drawRect", lua_drawRect);
  lua_register(L, "getKey", lua_getKey);
  lua_register(L, "readFile", lua_readFile);
  lua_register(L, "writeFile", lua_writeFile);
}

// Funkcja print() - wyświetla tekst na ekranie
int lua_print(lua_State *L) {
  int nargs = lua_gettop(L);

  for (int i = 1; i <= nargs; i++) {
    if (lua_isstring(L, i)) {
      const char* str = lua_tostring(L, i);
      Serial.print(str);
      tft.print(str); 
    } else {
      Serial.print(lua_typename(L, lua_type(L, i)));
    }
    if (i < nargs) {
      Serial.print("\t");
      tft.print("\t"); 
    }
  }
  Serial.println();
  tft.println();
  return 0;
}

// Funkcja drawPixel() - rysuje piksel na ekranie
int lua_drawPixel(lua_State *L) {
  int nargs = lua_gettop(L);

  if (nargs != 3) {
    return luaL_error(L, "drawPixel wymaga 3 argumentów: x, y, color");
  }

  int x = luaL_checkinteger(L, 1);
  int y = luaL_checkinteger(L, 2);
  int color = luaL_checkinteger(L, 3);

  tft.drawPixel(x, y, color);
  return 0;
}

// Funkcja drawLine() - rysuje linię na ekranie
int lua_drawLine(lua_State *L) {
  int nargs = lua_gettop(L);

  if (nargs != 5) {
    return luaL_error(L, "drawLine wymaga 5 argumentów: x1, y1, x2, y2, color");
  }

  int x1 = luaL_checkinteger(L, 1);
  int y1 = luaL_checkinteger(L, 2);
  int x2 = luaL_checkinteger(L, 3);
  int y2 = luaL_checkinteger(L, 4);
  int color = luaL_checkinteger(L, 5);

  tft.drawLine(x1, y1, x2, y2, color);
  return 0;
}

// Funkcja drawRect() - rysuje prostokąt na ekranie
int lua_drawRect(lua_State *L) {
  int nargs = lua_gettop(L);

  if (nargs != 5) {
    return luaL_error(L, "drawRect wymaga 5 argumentów: x, y, szerokość, wysokość, color");
  }

  int x = luaL_checkinteger(L, 1);
  int y = luaL_checkinteger(L, 2);
  int w = luaL_checkinteger(L, 3);
  int h = luaL_checkinteger(L, 4);
  int color = luaL_checkinteger(L, 5);

  tft.drawRect(x, y, w, h, color);
  return 0;
}

// Funkcja getKey() - odczytuje wciśnięty klawisz
int lua_getKey(lua_State *L) {
  char key = readKeypad();
  if (key != NO_KEY) {
    lua_pushstring(L, String(key).c_str());
    return 1; // Zwróć 1 wartość (wciśnięty klawisz)
  } else {
    return 0; // Nic nie zostało wciśnięte
  }
}

// Funkcja readFile() - odczytuje zawartość pliku z karty SD
int lua_readFile(lua_State *L) {
  int nargs = lua_gettop(L);

  if (nargs != 1) {
    return luaL_error(L, "readFile wymaga 1 argumentu: nazwa_pliku");
  }

  const char* filename = luaL_checkstring(L, 1);
  File file = SD.open(filename, FILE_READ);

  if (!file) {
    return luaL_error(L, "Nie można otworzyć pliku: %s", filename);
  }

  size_t fileSize = file.size();
  char* buffer = new char[fileSize + 1];
  file.readBytes(buffer, fileSize);
  buffer[fileSize] = '\0';

  lua_pushstring(L, buffer);
  delete[] buffer;
  file.close();

  return 1; // Zwróć 1 wartość (zawartość pliku)
}

// Funkcja writeFile() - zapisuje dane do pliku na karcie SD
int lua_writeFile(lua_State *L) {
  int nargs = lua_gettop(L);

  if (nargs != 2) {
    return luaL_error(L, "writeFile wymaga 2 argumentów: nazwa_pliku, dane");
  }

  const char* filename = luaL_checkstring(L, 1);
  const char* data = luaL_checkstring(L, 2);

  File file = SD.open(filename, FILE_WRITE);

  if (!file) {
    return luaL_error(L, "Nie można otworzyć pliku: %s", filename);
  }

  file.print(data);
  file.close();

  return 0;
}

// ... dodaj implementacje innych funkcji Lua
