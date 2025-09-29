#include <TinyWireM.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &TinyWireM, OLED_RESET);

// Pinos
#define BTN_HOUR 3   // PB3 - pino físico 2
#define BTN_MIN 4    // PB4 - pino físico 3
#define ALARM_OUT 1  // PB1 - pino físico 6

// Variáveis de tempo
unsigned long lastButtonCheck = 0;
unsigned long lastSecond = 0;
int currentHour = 0;
int currentMinute = 0;
int alarmHour = 6;
int alarmMinute = 30;
bool alarmTriggered = false;

void setup() {
  // Inicializa I2C e display
  TinyWireM.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  // Configura pinos
  pinMode(BTN_HOUR, INPUT_PULLUP);
  pinMode(BTN_MIN, INPUT_PULLUP);
  pinMode(ALARM_OUT, OUTPUT);
  digitalWrite(ALARM_OUT, LOW);
}

void loop() {
  unsigned long now = millis();

  // Atualiza tempo a cada minuto
  if (now - lastSecond >= 60000) { // 60000 ms = 1 minuto
    lastSecond = now;
    currentMinute++;
    if (currentMinute >= 60) {
      currentMinute = 0;
      currentHour = (currentHour + 1) % 24;
    }
  }

  // Verifica botões a cada 200ms
  if (now - lastButtonCheck >= 200) {
    lastButtonCheck = now;

    if (!digitalRead(BTN_HOUR)) {
      alarmHour = (alarmHour + 1) % 24;
    }
    if (!digitalRead(BTN_MIN)) {
      alarmMinute = (alarmMinute + 1) % 60;
    }
  }

  // Verifica alarme
  if (currentHour == alarmHour && currentMinute == alarmMinute && !alarmTriggered) {
    alarmTriggered = true;
    digitalWrite(ALARM_OUT, HIGH); // Ativa saída
  }

  // Atualiza display
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Hora: ");
  display.print(currentHour);
  display.print(":");
  if (currentMinute < 10) display.print("0");
  display.print(currentMinute);

  display.setCursor(0, 16);
  display.print("Alarme: ");
  display.print(alarmHour);
  display.print(":");
  if (alarmMinute < 10) display.print("0");
  display.print(alarmMinute);

  display.display();
}
