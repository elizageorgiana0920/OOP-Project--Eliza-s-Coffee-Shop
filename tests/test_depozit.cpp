
#include <gtest/gtest.h>
#include "Depozit.h"
#include <string>

// TEST 1: A new warehouse should be empty
TEST(DepozitTest, InitiallyEmpty) {
    Depozit<int> depozit;

    EXPECT_TRUE(depozit.esteGol());
    EXPECT_TRUE(depozit.getElemente().empty());
}

// TEST 2: Adding an element updates the warehouse
TEST(DepozitTest, AddElement) {
    Depozit<int> depozit;

    depozit.adauga(10);

    EXPECT_FALSE(depozit.esteGol());
    ASSERT_EQ(depozit.getElemente().size(), 1u);
    EXPECT_EQ(depozit.getElemente()[0], 10);
}

// TEST 3: Elements preserve insertion order
TEST(DepozitTest, InsertionOrder) {
    Depozit<int> depozit;

    depozit.adauga(10);
    depozit.adauga(20);
    depozit.adauga(30);

    ASSERT_EQ(depozit.getElemente().size(), 3u);

    EXPECT_EQ(depozit.getElemente()[0], 10);
    EXPECT_EQ(depozit.getElemente()[1], 20);
    EXPECT_EQ(depozit.getElemente()[2], 30);
}

// TEST 4: Clearing removes all elements
TEST(DepozitTest, ClearWarehouse) {
    Depozit<int> depozit;

    depozit.adauga(10);
    depozit.adauga(20);

    depozit.stergeToate();

    EXPECT_TRUE(depozit.esteGol());
    EXPECT_EQ(depozit.getElemente().size(), 0u);
}

// TEST 5: Clearing an already empty warehouse
TEST(DepozitTest, ClearEmptyWarehouse) {
    Depozit<int> depozit;

    depozit.stergeToate();

    EXPECT_TRUE(depozit.esteGol());
}

// TEST 6: Template works with std::string
TEST(DepozitTest, StringTemplate) {
    Depozit<std::string> depozit;

    depozit.adauga("Coffee");
    depozit.adauga("Milk");

    ASSERT_EQ(depozit.getElemente().size(), 2u);

    EXPECT_EQ(depozit.getElemente()[0], "Coffee");
    EXPECT_EQ(depozit.getElemente()[1], "Milk");
}
