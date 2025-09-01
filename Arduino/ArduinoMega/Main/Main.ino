#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal.h>
#include "Decrypt.h" // Убедитесь, что библиотека Decrypt доступна

Decrypt decrypt;

// Настройки для LCD дисплея
const int rs = 22, en = 24, d4 = 26, d5 = 28, d6 = 30, d7 = 32;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Настройка клавиатуры
const byte ROWS = 4; 
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {53, 51, 49, 47};
byte colPins[COLS] = {45, 43, 41};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// Переменные
String array[2];
const int maxStringLength = 48; // Максимальная длина строки
String code = ""; // Код, введенный пользователем
bool state = false; // Состояние для ожидания ввода кода
String ecpCode = ""; // Расшифрованный код
const int openpin = 8; // Пин для управления замком
String key = ""; // Ключ для расшифровки

void setup() {
  pinMode(openpin, OUTPUT);
  lcd.begin(16, 2);
  Wire.begin(8); // Установите адрес вашего устройства I2C
  Wire.onReceive(receiveEvent); // Регистрация обработчика событий
  Serial.begin(9600);
  Serial.println("I'm ready");
  lcd.clear();
  lcd.print("I'm ready");
}

void loop() {
  // Ожидание ввода кода с клавиатуры
  while(state) {
    char keyInput = keypad.getKey();
    if(keyInput) {
      if (String(keyInput) == "#") { // Проверка кода
        Serial.println("You pressed #");
        Serial.println(code);
        if(ecpCode == code) {
          Serial.println("Code accepted");
          lcd.clear();
          lcd.print("Accepted");

          digitalWrite(openpin, HIGH); // Открыть замок
          delay(5000);
          digitalWrite(openpin, LOW); // Закрыть замок

          lcd.clear();
          Serial.println("LCD cleared");
        } else {
          Serial.println("Incorrect code");
          lcd.clear();
          lcd.print("Not correct code");
          delay(2000);
          lcd.clear();
        }
        code = ""; // Сбросить код
        state = false; // Выход из состояния ожидания
      } else if(String(keyInput) == "*") { // Удалить последний символ
        if(code != "") {
          code.remove(code.length() - 1);
          Serial.println(code);
          lcd.clear();
          lcd.print(code);
        }
      } else {
        code += String(keyInput); // Добавление символа к коду
        Serial.println(code);
        lcd.clear();
        lcd.print(code);
      }
    }
  }
}

// Обработка получения данных через I2C
void receiveEvent() {
  int i = 0;
  char buffer[maxStringLength];
  memset(buffer, 0, sizeof(buffer)); // Обнуление буфера

  while (Wire.available()) {
    char c = Wire.read(); // Чтение байта
    if (c == '\n') { // Если получен символ новой строки
      array[i] = String(buffer); // Сохранение полученной строки
      Serial.print("Received data: ");
      Serial.println(array[i]);
      i++;
      memset(buffer, 0, sizeof(buffer)); // Обнуление буфера для следующей строки
    } else {
      strncat(buffer, &c, 1); // Добавление байта в буфер
    }
  }

  // Обработка полученных данных
  if(array[0] == "key") {
    key = array[1]; // Сохранение ключа
  }

  if(array[0] == "code") {
    String encrycode = array[1]; // Получение зашифрованного кода
    Serial.println(encrycode);
    ecpCode = decrypt.decrypting(key, encrycode); // Расшифровка кода
    Serial.println(ecpCode);
    state = true; // Вход в состояние ожидания ввода кода
  }
}
