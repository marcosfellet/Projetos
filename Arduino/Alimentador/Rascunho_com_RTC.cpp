#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <RTClib.h>

#define BTN1 PB1
#define BTN2 PB4
#define ALARM_OUT PB3

Adafruit_SSD1306 display(128, 64, &Wire);
RTC_DS3231 rtc;

int alarmHour = 7, alarmMinute = 0;
bool alarmOn = true;

void setup() {
  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);
  pinMode(ALARM_OUT, OUTPUT);

  Wire.begin();
  rtc.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Só usar uma vez p/ acertar
}

void loop() {
  DateTime now = rtc.now();

  // Mostra hora
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0,0);
  display.print(now.hour());
  display.print(":");
  if (now.minute() < 10) display.print("0");
  display.print(now.minute());
  display.display();

  // Alarme
  if (alarmOn && now.hour() == alarmHour && now.minute() == alarmMinute) {
    digitalWrite(ALARM_OUT, HIGH); // Liga saída
  }

  // Botão para desligar alarme
  if (digitalRead(BTN2) == LOW) {
    digitalWrite(ALARM_OUT, LOW);
  }

  delay(500);
}
