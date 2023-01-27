#include <Arduino.h>
#include <unity.h>

#include "backoff.h"

using namespace fakeit;

void setUp(void) { ArduinoFakeReset(); }

void tearDown(void) {
    // clean stuff up here
}

void test_waitDurations(void) {
    NoBackoff backoff1(100);
    TEST_ASSERT_EQUAL(100, backoff1.getWaitDuration(0));
    TEST_ASSERT_EQUAL(100, backoff1.getWaitDuration(1));
    TEST_ASSERT_EQUAL(100, backoff1.getWaitDuration(2));
    TEST_ASSERT_EQUAL(100, backoff1.getWaitDuration(3));
    TEST_ASSERT_EQUAL(100, backoff1.getWaitDuration(4));
    TEST_ASSERT_EQUAL(100, backoff1.getWaitDuration(5));
    TEST_ASSERT_EQUAL(100, backoff1.getWaitDuration(6));
    TEST_ASSERT_EQUAL(100, backoff1.getWaitDuration(7));
    TEST_ASSERT_EQUAL(100, backoff1.getWaitDuration(93826));
    TEST_ASSERT_EQUAL(100, backoff1.getWaitDuration(10483729202847292));

    LinearBackoff backoff2(100, 600);
    TEST_ASSERT_EQUAL(100, backoff2.getWaitDuration(0));
    TEST_ASSERT_EQUAL(200, backoff2.getWaitDuration(1));
    TEST_ASSERT_EQUAL(300, backoff2.getWaitDuration(2));
    TEST_ASSERT_EQUAL(400, backoff2.getWaitDuration(3));
    TEST_ASSERT_EQUAL(500, backoff2.getWaitDuration(4));
    TEST_ASSERT_EQUAL(600, backoff2.getWaitDuration(5));
    TEST_ASSERT_EQUAL(600, backoff2.getWaitDuration(6));
    TEST_ASSERT_EQUAL(600, backoff2.getWaitDuration(7));
    TEST_ASSERT_EQUAL(600, backoff2.getWaitDuration(93826));
    TEST_ASSERT_EQUAL(600, backoff2.getWaitDuration(10483729202847292));

    ExponentialBackoff backoff3(100, 30000);
    TEST_ASSERT_EQUAL(100, backoff3.getWaitDuration(0));
    TEST_ASSERT_EQUAL(200, backoff3.getWaitDuration(1));
    TEST_ASSERT_EQUAL(400, backoff3.getWaitDuration(2));
    TEST_ASSERT_EQUAL(800, backoff3.getWaitDuration(3));
    TEST_ASSERT_EQUAL(1600, backoff3.getWaitDuration(4));
    TEST_ASSERT_EQUAL(3200, backoff3.getWaitDuration(5));
    TEST_ASSERT_EQUAL(6400, backoff3.getWaitDuration(6));
    TEST_ASSERT_EQUAL(12800, backoff3.getWaitDuration(7));
    TEST_ASSERT_EQUAL(25600, backoff3.getWaitDuration(8));
    TEST_ASSERT_EQUAL(30000, backoff3.getWaitDuration(9));
    TEST_ASSERT_EQUAL(30000, backoff3.getWaitDuration(93826));
    TEST_ASSERT_EQUAL(30000, backoff3.getWaitDuration(10483729202847292));
}

void test_waitDurationsWithJitter() {
    // Mock the random values returned as jitter
    When(OverloadedMethod(ArduinoFake(), random, long(long, long))).Return(17, -13, -9, 4, 7, -14, 12, 8, 14, -17);
    NoBackoff backoff1(100, 25);
    TEST_ASSERT_EQUAL(117, backoff1.getWaitDuration(0));
    TEST_ASSERT_EQUAL(87, backoff1.getWaitDuration(1));
    TEST_ASSERT_EQUAL(91, backoff1.getWaitDuration(2));
    TEST_ASSERT_EQUAL(104, backoff1.getWaitDuration(3));
    TEST_ASSERT_EQUAL(107, backoff1.getWaitDuration(4));
    TEST_ASSERT_EQUAL(86, backoff1.getWaitDuration(5));
    TEST_ASSERT_EQUAL(112, backoff1.getWaitDuration(6));
    TEST_ASSERT_EQUAL(108, backoff1.getWaitDuration(7));
    TEST_ASSERT_EQUAL(114, backoff1.getWaitDuration(93826));
    TEST_ASSERT_EQUAL(83, backoff1.getWaitDuration(10483729202847292));

    // Mock the random values returned as jitter
    When(OverloadedMethod(ArduinoFake(), random, long(long, long))).Return(87, -43, -92, 14, 71, -40, 92, 28, 40, -37);
    LinearBackoff backoff2(100, 600, 100);
    TEST_ASSERT_EQUAL(187, backoff2.getWaitDuration(0));
    TEST_ASSERT_EQUAL(157, backoff2.getWaitDuration(1));
    TEST_ASSERT_EQUAL(208, backoff2.getWaitDuration(2));
    TEST_ASSERT_EQUAL(414, backoff2.getWaitDuration(3));
    TEST_ASSERT_EQUAL(571, backoff2.getWaitDuration(4));
    TEST_ASSERT_EQUAL(560, backoff2.getWaitDuration(5));
    TEST_ASSERT_EQUAL(692, backoff2.getWaitDuration(6));
    TEST_ASSERT_EQUAL(628, backoff2.getWaitDuration(7));
    TEST_ASSERT_EQUAL(640, backoff2.getWaitDuration(93826));
    TEST_ASSERT_EQUAL(563, backoff2.getWaitDuration(10483729202847292));

    // Mock the random values returned as jitter
    When(OverloadedMethod(ArduinoFake(), random, long(long, long))).Return(-187, 243, -292, 314, 271, -140, 92, 238, -140, -37, 82, 172);
    ExponentialBackoff backoff3(100, 30000, 400);
    TEST_ASSERT_EQUAL(0, backoff3.getWaitDuration(0));
    TEST_ASSERT_EQUAL(443, backoff3.getWaitDuration(1));
    TEST_ASSERT_EQUAL(108, backoff3.getWaitDuration(2));
    TEST_ASSERT_EQUAL(1114, backoff3.getWaitDuration(3));
    TEST_ASSERT_EQUAL(1871, backoff3.getWaitDuration(4));
    TEST_ASSERT_EQUAL(3060, backoff3.getWaitDuration(5));
    TEST_ASSERT_EQUAL(6492, backoff3.getWaitDuration(6));
    TEST_ASSERT_EQUAL(13038, backoff3.getWaitDuration(7));
    TEST_ASSERT_EQUAL(25460, backoff3.getWaitDuration(8));
    TEST_ASSERT_EQUAL(29963, backoff3.getWaitDuration(9));
    TEST_ASSERT_EQUAL(30082, backoff3.getWaitDuration(93826));
    TEST_ASSERT_EQUAL(30172, backoff3.getWaitDuration(10483729202847292));
}

int main(int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(test_waitDurations);
    RUN_TEST(test_waitDurationsWithJitter);

    return UNITY_END();
}