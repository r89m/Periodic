#include <Arduino.h>
#include <periodic.h>

const int LED_PIN_1 = D7;
const int LED_PIN_2 = D6;

void blinkCallback1();
void blinkCallback2();
auto blinkTimer1 = Periodic(blinkCallback1, 500);
auto blinkTimer2 = Periodic(blinkCallback2, 750);

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN_1, OUTPUT);
    pinMode(LED_PIN_2, OUTPUT);
}

void loop() {
    blinkTimer1.loop();
    blinkTimer2.loop();
}

uint32_t blinkLed(uint8_t ledPin, uint32_t ledLastCallTime) {
    uint32_t millisNow = millis();
    Serial.print("Changing LED ");
    Serial.print(ledPin);
    Serial.println(" state after ");
    Serial.print(millisNow - ledLastCallTime);
    Serial.println("ms");

    digitalWrite(ledPin, !digitalRead(ledPin));

    return millisNow;
}

uint32 lastCallTime1 = 0;
uint32 lastCallTime2 = 0;
void blinkCallback1() {
    lastCallTime1 = blinkLed(LED_PIN_1, lastCallTime2);
}

void blinkCallback2() {
    lastCallTime2 = blinkLed(LED_PIN_2, lastCallTime2);
}