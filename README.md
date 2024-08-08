# John 2.0: Konsolowy system operacyjny na Arduino Mega z graficznym interfejsem

Witaj w **John 2.0**, ewolucji konsolowego systemu operacyjnego dla **Arduino Mega**! John 2.0 wprowadza graficzny interfejs użytkownika, zachowując jednocześnie swoje konsolowe korzenie.  Zapomnij o numerowaniu aplikacji – teraz nawigujesz strzałkami i wybierasz to, co chcesz uruchomić, za pomocą wyraźnej, niebieskiej ramki!

## :sparkles: Funkcjonalność:

* **Intuicyjny interfejs graficzny:**  
    * Wyświetla menu aplikacji z czytelnymi nazwami.
    * Zaznaczona aplikacja jest podświetlona **niebieską ramką**.
    * Nawigacja za pomocą klawiszy strzałek.
* **Uruchamianie aplikacji:**  Naciśnij klawisz `#`, aby uruchomić zaznaczoną aplikację.
* **Szybki powrót:** Naciśnij jednocześnie `#` i `*`, aby wrócić do menu głównego z dowolnego miejsca.
* **Wygodne przewijanie:**  Przeglądaj długie listy za pomocą przycisku `*`:
    * :point_down:  Pojedyncze kliknięcie: Przewiń w dół.
    * :arrow_up: Przytrzymanie: Przewiń w górę.
* **Włączanie/wyłączanie:** 
    * :arrow_right: Przytrzymaj przycisk `#` przez 5 sekund, aby włączyć urządzenie.
    * :arrow_left: Przytrzymanie `#` podczas wyłączonego urządzenia go włączy.
* **Wbudowana aplikacja "Ustawienia" (klawisz `0`):** 
    * Konfiguracja przypisania klawiszy funkcyjnych.
    * Przypisywanie aplikacji Lua do przycisków dla szybkiego dostępu.
    * Dostęp do ustawień aplikacji Lua (jeśli są dostępne).
* **Rozbudowane możliwości Lua:** John 2.0 oferuje nowe funkcje Lua do:
    * Wyświetlania tekstu i prostych elementów graficznych na ekranie.
    * Odczytywania danych z klawiatury.
    * Zarządzania plikami na karcie SD.
    * **I wiele więcej!** Ogranicza Cię tylko Twoja wyobraźnia!
* **Wielo-plikowe aplikacje Lua:**  Organizuj kod swoich aplikacji w wielu plikach Lua, a John 2.0 automatycznie skompiluje je w jedną całość.

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
2. **Zainstaluj biblioteki:**  Zainstaluj następujące biblioteki w Arduino IDE:
    * **Lua**
    * **SD**
    * **Adafruit_GFX**
    * **Adafruit_ILI9341** (lub odpowiednią bibliotekę dla Twojego ekranu)
    * **Keypad**
    * **EEPROM**
    * **LowPower**
    Możesz to zrobić za pomocą Menedżera Bibliotek w IDE (Sketch -> Include Library -> Manage Libraries...).
3. **Podłącz sprzęt:** Połącz Arduino Mega, ekran TFT, klawiaturę i czytnik kart SD zgodnie z dostarczonym schematem połączeń.
4. **Skonfiguruj piny:** W pliku `logic_main.cpp` dostosuj piny klawiatury (`rowPins` i `colPins`) oraz ekranu TFT (`TFT_CS`, `TFT_DC`, `TFT_RST`) do swojego połączenia.
5. **Wgraj kod:** Skopiuj kod z plików projektu do Arduino IDE i wgraj go na Arduino Mega.

## :pencil2: Tworzenie aplikacji w Lua:

1. **Stwórz folder dla swojej aplikacji w katalogu `/app` na karcie SD.**  Nazwa folderu będzie nazwą Twojej aplikacji.
2. **Stwórz plik `main.lua` wewnątrz folderu aplikacji.**  To będzie główny plik Twojej aplikacji.
3. **(Opcjonalnie) Dodaj plik `settings.lua` do folderu aplikacji, jeśli chcesz zdefiniować ustawienia aplikacji.**
4. **Napisz kod Lua w plikach `main.lua` i `settings.lua` (jeśli jest używany).**  Możesz korzystać z:
    * **Funkcji standardowej biblioteki Lua:** [https://www.lua.org/manual/5.4/](https://www.lua.org/manual/5.4/)
    * **Funkcji udostępnionych przez John 2.0:** 
        * `print(tekst)`:  Wyświetla tekst na ekranie.
        * `drawPixel(x, y, kolor)`:  Rysuje piksel na ekranie.
        * `drawLine(x1, y1, x2, y2, kolor)`: Rysuje linię na ekranie.
        * `drawRect(x, y, szerokość, wysokość, kolor)`: Rysuje prostokąt na ekranie.
        * `getKey()`:  Odczytuje wciśnięty klawisz na klawiaturze.
        * `readFile(nazwa_pliku)`:  Odczytuje zawartość pliku z karty SD.
        * `writeFile(nazwa_pliku, dane)`: Zapisuje dane do pliku na karcie SD.
5. **Uruchom John 2.0:**  Po włączeniu urządzenia, John 2.0 automatycznie skompiluje wszystkie aplikacje Lua z folderu `/app` i wyświetli je w menu głównym.

## :blue_book: Przykładowe aplikacje Lua:

**1. Hello World (app1/main.lua):**

```lua
print("Witaj w świecie Johna 2.0!")
