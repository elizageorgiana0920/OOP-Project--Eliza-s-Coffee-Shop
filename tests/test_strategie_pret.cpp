#include <gtest/gtest.h>
#include "StrategiePret.h"

// Test 1: Standard pricing
TEST(StrategiePretTest, StandardPrice) {
    StrategieStandard strategie;

    EXPECT_FLOAT_EQ(strategie.calculeazaPret(100.0f), 100.0f);
}

// Test 2: Happy Hour applies a 20% discount
TEST(StrategiePretTest, HappyHourDiscount) {
    StrategieHappyHour strategie;

    EXPECT_FLOAT_EQ(strategie.calculeazaPret(100.0f), 80.0f);
}

// Test 3: Weekend applies a 10% surcharge
TEST(StrategiePretTest, WeekendSurcharge) {
    StrategieWeekend strategie;

    EXPECT_NEAR(strategie.calculeazaPret(100.0f), 110.0f, 0.001f);
}

// Test 4: Happy Hour with food price modifier
TEST(StrategiePretTest, HappyHourWithModifier) {
    StrategieHappyHour strategie;

    // 100 * 1.5 * 0.8 = 120
    EXPECT_FLOAT_EQ(
        strategie.calculeazaPret(100.0f, 1.5f),
        120.0f
    );
}

// Test 5: A zero-price product stays free
TEST(StrategiePretTest, ZeroPrice) {
    StrategieWeekend strategie;

    EXPECT_FLOAT_EQ(strategie.calculeazaPret(0.0f), 0.0f);
}
