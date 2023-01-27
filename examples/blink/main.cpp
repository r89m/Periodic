#include <Arduino.h>
#include <periodic.h>

const int LED_PIN = D7;

void blinkCallback();
auto blinkTimer = Periodic(blinkCallback, 500);

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    blinkTimer.loop();
}

uint32 lastCallTime = 0;
void blinkCallback() {
    uint32_t millisNow = millis();
    Serial.println("Changing LED state after ");
    Serial.print(millisNow - lastCallTime);
    Serial.println("ms");
    lastCallTime = millisNow;

    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}