# John 2.0: Konsolowy system operacyjny na Arduino Mega z graficznym interfejsem

Witaj w **John 2.0**, ewolucji konsolowego systemu operacyjnego dla **Arduino Mega**! John 2.0 wprowadza graficzny interfejs użytkownika, zachowując jednocześnie swoje konsolowe korzenie.

## :sparkles:  Funkcjonalność:

* **Ekran graficzny:** Wyświetla menu, aplikacje i informacje na ekranie TFT o rozdzielczości 240x320 (lub innej, jeśli jest obsługiwana).
* **Nawigacja strzałkami:**  Użyj klawiszy strzałek do poruszania się po menu i zaznaczania aplikacji. 
* **Wybór aplikacji:**  Zaznaczona aplikacja jest podświetlona niebieską ramką.
* **Uruchamianie aplikacji:** Naciśnij klawisz `#`, aby uruchomić zaznaczoną aplikację.
* **Powrót do menu głównego:** Naciśnij jednocześnie `#` i `*`, aby wrócić do menu głównego.
* **Przewijanie:** Przewijaj zawartość ekranu za pomocą przycisku `*`:
    * :point_down:  Pojedyncze kliknięcie: Przewiń w dół o 2 linie.
    * :arrow_up: Przytrzymanie: Przewiń w górę o 1 linię na sekundę.
* **Włączanie/wyłączanie:** 
    * :arrow_right: Przytrzymaj przycisk `#` przez 5 sekund, aby włączyć lub wyłączyć urządzenie.
    * :arrow_left: Przytrzymanie `#` podczas wyłączonego urządzenia go włączy.
* **Wbudowana aplikacja "Ustawienia":** Dostępna za pomocą klawisza `0`, pozwala na:
    * Konfigurację przypisania klawiszy funkcyjnych.
    * Przypisywanie aplikacji Lua do przycisków.
    * Dostęp do ustawień aplikacji Lua (jeśli są dostępne).
* **Rozbudowane możliwości Lua:** John 2.0 oferuje nowe funkcje Lua do obsługi grafiki, interakcji z użytkownikiem i innych funkcji specyficznych dla systemu.
* **Wielo-plikowe aplikacje Lua:** Aplikacje Lua mogą teraz składać się z wielu plików Lua umieszczonych w osobnym folderze, co ułatwia organizację kodu.

## :electric_plug: Wymagany sprzęt:

* Arduino Mega 2560
* Ekran TFT 2.8" 240x320 SPI (z kontrolerem ILI9341 lub ST7789V)
* Klawiatura membranowa 4x4 (z klawiszami strzałek)
* Karta SD
* Moduł ładowania baterii Li-Ion TP4056 (opcjonalnie)
* Bateria Li-Ion 3.7V (opcjonalnie)
* Przetwornica napięcia (opcjonalnie, w zależności od wymagań ekranu i klawiatury)
* Rezystory, kondensatory, przewody połączeniowe (zgodnie ze schematem połączeń)

## :computer: Instalacja i konfiguracja:

1. **Zainstaluj Arduino IDE:**  Pobierz i zainstaluj Arduino IDE z [https://www.arduino.cc/en/software](https://www.arduino.cc/en/software).
2. **Zainstaluj biblioteki:**  Zainstaluj biblioteki **Lua**, **SD**, **Adafruit_GFX**, **Adafruit_ILI9341** (lub odpowiednią bibliotekę dla Twojego ekranu), **Keypad**, **EEPROM** i **LowPower** w Arduino IDE. Możesz to zrobić za pomocą Menedżera Bibliotek w IDE (Sketch -> Include Library -> Manage Libraries...).
3. **Podłącz sprzęt:** Połącz Arduino Mega, ekran TFT, klawiaturę i czytnik kart SD zgodnie z dostarczonym schematem połączeń.
4. **Skonfiguruj piny:** W pliku `logic_main.cpp` dostosuj piny klawiatury (`rowPins` i `colPins`) oraz ekranu TFT (`TFT_CS`, `TFT_DC`, `TFT_RST`) do swojego połączenia.
5. **Wgraj kod:** Skopiuj kod z plików `main.cpp`, `logic_lua.cpp`, `logic_lua.h`, `logic_main.cpp`, `logic_main.h`, `ui.cpp`, `ui.h`, `Lua_compiler.cpp` i `Lua_compiler.h` do Arduino IDE i wgraj go na Arduino Mega.

## :pencil2: Tworzenie aplikacji w Lua:

1. **Stwórz folder dla swojej aplikacji w katalogu `/app` na karcie SD.**  Nazwa folderu będzie nazwą Twojej aplikacji.
2. **Stwórz plik `main.lua` wewnątrz folderu aplikacji.**  To będzie główny plik Twojej aplikacji.
3. **Dodaj opcjonalny plik `settings.lua` do folderu aplikacji, jeśli chcesz zdefiniować ustawienia aplikacji.**
4. **Napisz kod Lua w plikach `main.lua` i `settings.lua` (jeśli jest używany).**  Możesz korzystać z funkcji standardowej biblioteki Lua oraz funkcji udostępnionych przez John 2.0.
5. **Uruchom John 2.0:**  Po włączeniu urządzenia, John 2.0 automatycznie skompiluje wszystkie aplikacje Lua z folderu `/app` i wyświetli je w menu głównym.

## :information_source: Dodatkowe informacje:

* John 2.0 został zaprojektowany tak, aby był łatwy w użyciu i rozszerzalny.
* Możesz tworzyć własne aplikacje Lua, aby dodawać nowe funkcje i dostosowywać system do swoich potrzeb.
* Kod źródłowy Johna 2.0 jest otwarty, więc możesz go modyfikować i ulepszać.

**Mamy nadzieję, że spodoba Ci się korzystanie z Johna 2.0!**
