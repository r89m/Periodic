#include <Arduino.h>
#include <unity.h>

#include "periodic.h"

using namespace fakeit;



bool myCallback1(unsigned long attempt) {
    #include <iostream>
    std::cout << "my callback called: " << attempt << std::endl;
    return true;
}

void mySimpleCallback() {
    std::cout << "Simple callback called" << std::endl;
}


void test_periodicCalls(void) {


    When(Method(ArduinoFake(), loop)).Return();
    When(Method(ArduinoFake(), millis)).Return(350, 601, 705);
    When(OverloadedMethod(ArduinoFake(), random, long(long, long))).Return(17, 18, 19, 20);

    // Periodic periodic1(myCallback1, 300);
    // Periodic periodic1(myCallback1, NoBackoff(300));
    
    auto periodic1 = Periodic(myCallback1, ExponentialBackoff(300, 5000));
    auto periodic2 = Periodic(mySimpleCallback, 800);
    // PeriodicMicros<LinearBackoff> pemicros(myCallback1, LinearBackoff(100, 500));
    // Nothing happens
    #  include<iostream>
    periodic1.loop();
    periodic1.loop();
    // periodic1.loop();

    // TODO: Simulate callback periodicly failing and check that the correct delays are used.

    // unsigned long initialDelay1 = 100;
    // NoBackoff backoff1;
    // TEST_ASSERT_EQUAL(100, backoff1.getWaitDuration(initialDelay1, 0));
    // TEST_ASSERT_EQUAL(100, backoff1.getWaitDuration(initialDelay1, 1));
    // TEST_ASSERT_EQUAL(100, backoff1.getWaitDuration(initialDelay1, 2));
    // TEST_ASSERT_EQUAL(100, backoff1.getWaitDuration(initialDelay1, 3));
    // TEST_ASSERT_EQUAL(100, backoff1.getWaitDuration(initialDelay1, 4));
    // TEST_ASSERT_EQUAL(100, backoff1.getWaitDuration(initialDelay1, 5));
    // TEST_ASSERT_EQUAL(100, backoff1.getWaitDuration(initialDelay1, 6));
    // TEST_ASSERT_EQUAL(100, backoff1.getWaitDuration(initialDelay1, 7));
    // TEST_ASSERT_EQUAL(100, backoff1.getWaitDuration(initialDelay1, 93826));
    // TEST_ASSERT_EQUAL(100, backoff1.getWaitDuration(initialDelay1, 10483729202847292));

    // unsigned long initialDelay2 = 100;
    // LinearBackoff backoff2(600);
    // TEST_ASSERT_EQUAL(100, backoff2.getWaitDuration(initialDelay2, 0));
    // TEST_ASSERT_EQUAL(200, backoff2.getWaitDuration(initialDelay2, 1));
    // TEST_ASSERT_EQUAL(300, backoff2.getWaitDuration(initialDelay2, 2));
    // TEST_ASSERT_EQUAL(400, backoff2.getWaitDuration(initialDelay2, 3));
    // TEST_ASSERT_EQUAL(500, backoff2.getWaitDuration(initialDelay2, 4));
    // TEST_ASSERT_EQUAL(600, backoff2.getWaitDuration(initialDelay2, 5));
    // TEST_ASSERT_EQUAL(600, backoff2.getWaitDuration(initialDelay2, 6));
    // TEST_ASSERT_EQUAL(600, backoff2.getWaitDuration(initialDelay2, 7));
    // TEST_ASSERT_EQUAL(600, backoff2.getWaitDuration(initialDelay2, 93826));
    // TEST_ASSERT_EQUAL(600, backoff2.getWaitDuration(initialDelay2, 10483729202847292));

    // unsigned long initialDelay3 = 100;
    // ExponentialBackoff backoff3(30000);
    // TEST_ASSERT_EQUAL(100, backoff3.getWaitDuration(initialDelay3, 0));
    // TEST_ASSERT_EQUAL(200, backoff3.getWaitDuration(initialDelay3, 1));
    // TEST_ASSERT_EQUAL(400, backoff3.getWaitDuration(initialDelay3, 2));
    // TEST_ASSERT_EQUAL(800, backoff3.getWaitDuration(initialDelay3, 3));
    // TEST_ASSERT_EQUAL(1600, backoff3.getWaitDuration(initialDelay3, 4));
    // TEST_ASSERT_EQUAL(3200, backoff3.getWaitDuration(initialDelay3, 5));
    // TEST_ASSERT_EQUAL(6400, backoff3.getWaitDuration(initialDelay3, 6));
    // TEST_ASSERT_EQUAL(12800, backoff3.getWaitDuration(initialDelay3, 7));
    // TEST_ASSERT_EQUAL(25600, backoff3.getWaitDuration(initialDelay3, 8));
    // TEST_ASSERT_EQUAL(30000, backoff3.getWaitDuration(initialDelay3, 9));
    // TEST_ASSERT_EQUAL(30000, backoff3.getWaitDuration(initialDelay3, 93826));
    // TEST_ASSERT_EQUAL(30000, backoff3.getWaitDuration(initialDelay3, 10483729202847292));
}

void test_periodicCallsWithJitter() {
//     // Mock the random values returned as jitter
//     When(OverloadedMethod(ArduinoFake(), random, long(long, long))).Return(17, -13, -9, 4, 7, -14, 12, 8, 14, -17);
//     unsigned long initialDelay1 = 100;
//     NoBackoff backoff1(25);
//     TEST_ASSERT_EQUAL(117, backoff1.getWaitDuration(initialDelay1, 0));
//     TEST_ASSERT_EQUAL(87, backoff1.getWaitDuration(initialDelay1, 1));
//     TEST_ASSERT_EQUAL(91, backoff1.getWaitDuration(initialDelay1, 2));
//     TEST_ASSERT_EQUAL(104, backoff1.getWaitDuration(initialDelay1, 3));
//     TEST_ASSERT_EQUAL(107, backoff1.getWaitDuration(initialDelay1, 4));
//     TEST_ASSERT_EQUAL(86, backoff1.getWaitDuration(initialDelay1, 5));
//     TEST_ASSERT_EQUAL(112, backoff1.getWaitDuration(initialDelay1, 6));
//     TEST_ASSERT_EQUAL(108, backoff1.getWaitDuration(initialDelay1, 7));
//     TEST_ASSERT_EQUAL(114, backoff1.getWaitDuration(initialDelay1, 93826));
//     TEST_ASSERT_EQUAL(83, backoff1.getWaitDuration(initialDelay1, 10483729202847292));

//     // Mock the random values returned as jitter
//     When(OverloadedMethod(ArduinoFake(), random, long(long, long))).Return(87, -43, -92, 14, 71, -40, 92, 28, 40, -37);
//     unsigned long initialDelay2 = 100;
//     LinearBackoff backoff2(600, 100);
//     TEST_ASSERT_EQUAL(187, backoff2.getWaitDuration(initialDelay2, 0));
//     TEST_ASSERT_EQUAL(157, backoff2.getWaitDuration(initialDelay2, 1));
//     TEST_ASSERT_EQUAL(208, backoff2.getWaitDuration(initialDelay2, 2));
//     TEST_ASSERT_EQUAL(414, backoff2.getWaitDuration(initialDelay2, 3));
//     TEST_ASSERT_EQUAL(571, backoff2.getWaitDuration(initialDelay2, 4));
//     TEST_ASSERT_EQUAL(560, backoff2.getWaitDuration(initialDelay2, 5));
//     TEST_ASSERT_EQUAL(692, backoff2.getWaitDuration(initialDelay2, 6));
//     TEST_ASSERT_EQUAL(628, backoff2.getWaitDuration(initialDelay2, 7));
//     TEST_ASSERT_EQUAL(640, backoff2.getWaitDuration(initialDelay2, 93826));
//     TEST_ASSERT_EQUAL(563, backoff2.getWaitDuration(initialDelay2, 10483729202847292));

//     // Mock the random values returned as jitter
//     When(OverloadedMethod(ArduinoFake(), random, long(long, long))).Return(-187, 243, -292, 314, 271, -140, 92, 238, -140, -37, 82, 172);
//     unsigned long initialDelay3 = 100;
//     ExponentialBackoff backoff3(30000, 400);
//     TEST_ASSERT_EQUAL(-87, backoff3.getWaitDuration(initialDelay3, 0)); // Whilst not ideal, this doesn't actually matter as, functionally, the behaviour is the same - a wait of 0 is performed
//     TEST_ASSERT_EQUAL(443, backoff3.getWaitDuration(initialDelay3, 1));
//     TEST_ASSERT_EQUAL(108, backoff3.getWaitDuration(initialDelay3, 2));
//     TEST_ASSERT_EQUAL(1114, backoff3.getWaitDuration(initialDelay3, 3));
//     TEST_ASSERT_EQUAL(1871, backoff3.getWaitDuration(initialDelay3, 4));
//     TEST_ASSERT_EQUAL(3060, backoff3.getWaitDuration(initialDelay3, 5));
//     TEST_ASSERT_EQUAL(6492, backoff3.getWaitDuration(initialDelay3, 6));
//     TEST_ASSERT_EQUAL(13038, backoff3.getWaitDuration(initialDelay3, 7));
//     TEST_ASSERT_EQUAL(25460, backoff3.getWaitDuration(initialDelay3, 8));
//     TEST_ASSERT_EQUAL(29963, backoff3.getWaitDuration(initialDelay3, 9));
//     TEST_ASSERT_EQUAL(30082, backoff3.getWaitDuration(initialDelay3, 93826));
//     TEST_ASSERT_EQUAL(30172, backoff3.getWaitDuration(initialDelay3, 10483729202847292));
}

int main(int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(test_periodicCalls);
    RUN_TEST(test_periodicCallsWithJitter);

    return UNITY_END();
}