#include <Arduino.h>
#include <periodic.h>

bool connectionCallback(unsigned long attempt);
auto connectionAttemptPeriodic = Periodic(connectionCallback, ExponentialBackoff(500, 5000));
// auto connectionAttemptPeriodic = Periodic(connectionCallback, LinearBackoff(500, 5000));     Try using a Linear Backoff strategy
// auto connectionAttemptPeriodic = Periodic(connectionCallback, ExponentialBackoff(500, 5000, 75));     Try adding Jitter to reduce load on the server

void setup() {
    Serial.begin(115200);
}

void loop() {
    connectionAttemptPeriodic.loop();
}

uint32 lastCallTime = 0;
bool connectionCallback(unsigned long attempt) {

    Serial.print("Atttempting to connect to server. Attempt #");
    Serial.println(attempt);
    uint32_t millisNow = millis();
    Serial.print("Time since last call: ");
    Serial.println(millisNow - lastCallTime);
    lastCallTime = millisNow;

    // Fail approximate 70% of the time
    if (random(10) < 7) {
        Serial.println("Oh dear, failed!");
        return false;
    }
    Serial.println("Congratulations, it succeeded");
    Serial.println();
    return true;
}