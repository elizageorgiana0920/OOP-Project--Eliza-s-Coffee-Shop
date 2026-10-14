
#include <gtest/gtest.h>
#include "Ingredient.h"
#include "Exceptii.h"

// TEST 1: Default constructor initializes correctly
TEST(IngredientTest, DefaultConstructor) {
    Ingredient ingredient;

    EXPECT_EQ(ingredient.getNume(), "");
    EXPECT_EQ(ingredient.getStoc(), 0);
    EXPECT_FLOAT_EQ(ingredient.getPret(), 0.0f);
    EXPECT_FALSE(ingredient.getVegan());
    EXPECT_FALSE(ingredient.esteInStoc());
}

// TEST 2: Parameterized constructor stores values
TEST(IngredientTest, ParameterizedConstructor) {
    Ingredient lapte("Lapte", 10, 5.0f,
                     false, true, false, 60.0f);

    EXPECT_EQ(lapte.getNume(), "Lapte");
    EXPECT_EQ(lapte.getStoc(), 10);
    EXPECT_FLOAT_EQ(lapte.getPret(), 5.0f);
    EXPECT_FALSE(lapte.getVegan());
    EXPECT_TRUE(lapte.getFaraZahar());
    EXPECT_FALSE(lapte.getFaraLactoza());
    EXPECT_FLOAT_EQ(lapte.getKcal(), 60.0f);
}

// TEST 3: Consuming stock decreases quantity by one
TEST(IngredientTest, ConsumeStock) {
    Ingredient cafea("Cafea", 10, 3.0f,
                      true, true, true, 5.0f);

    cafea.consumaStoc();

    EXPECT_EQ(cafea.getStoc(), 9);
}

// TEST 4: Consuming zero stock throws custom exception
TEST(IngredientTest, InsufficientStockThrowsException) {
    Ingredient cafea("Cafea", 0, 3.0f,
                      true, true, true, 5.0f);

    EXPECT_THROW(
        cafea.consumaStoc(),
        StocInsuficientException
    );

    EXPECT_EQ(cafea.getStoc(), 0);
}

// TEST 5: Restocking increases available stock
TEST(IngredientTest, RestockIngredient) {
    Ingredient cafea("Cafea", 10, 3.0f,
                      true, true, true, 5.0f);

    cafea.reaprovizionare(5);

    EXPECT_EQ(cafea.getStoc(), 15);
}

// TEST 6: Negative restocking is ignored
TEST(IngredientTest, NegativeRestock) {
    Ingredient cafea("Cafea", 10, 3.0f,
                      true, true, true, 5.0f);

    cafea.reaprovizionare(-5);

    EXPECT_EQ(cafea.getStoc(), 10);
}

// TEST 7: Low stock alert activates below five
TEST(IngredientTest, LowStockAlert) {
    Ingredient cafea("Cafea", 4, 3.0f,
                      true, true, true, 5.0f);

    EXPECT_TRUE(cafea.atentieStocMic());
}

// TEST 8: Five items do not trigger low stock alert
TEST(IngredientTest, StockBoundaryValue) {
    Ingredient cafea("Cafea", 5, 3.0f,
                      true, true, true, 5.0f);

    EXPECT_FALSE(cafea.atentieStocMic());
}

// TEST 9: Stock availability at zero
TEST(IngredientTest, OutOfStock) {
    Ingredient cafea("Cafea", 0, 3.0f,
                      true, true, true, 5.0f);

    EXPECT_FALSE(cafea.esteInStoc());
}

// TEST 10: Consume last item, then exception
TEST(IngredientTest, ConsumeLastItem) {
    Ingredient cafea("Cafea", 1, 3.0f,
                      true, true, true, 5.0f);

    cafea.consumaStoc();

    EXPECT_EQ(cafea.getStoc(), 0);
    EXPECT_FALSE(cafea.esteInStoc());

    EXPECT_THROW(
        cafea.consumaStoc(),
        StocInsuficientException
    );

    EXPECT_EQ(cafea.getStoc(), 0);
}
