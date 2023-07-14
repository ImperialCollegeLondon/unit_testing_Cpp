#include <iostream>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

template <class GenericHorse>
bool isAliveAtEndOfDay(int steps, double carbs, GenericHorse *animal)
{
    double spent_carbs{animal->walk(steps)};
    if (spent_carbs > carbs)
    {
        animal->die();
        return false;
    }
    animal->eat(carbs - spent_carbs);
    return true;
};

class MockHorse
{
public:
    MOCK_METHOD(double, walk, (int));
    MOCK_METHOD(void, eat, (double));
    MOCK_METHOD(void, die, ());
};

TEST(IsAliveTest, Lives)
{
    MockHorse animal = MockHorse();
    int steps{400};
    double carbs{2000.0};
    double consumed{500.0};

    EXPECT_CALL(animal, walk(steps)).Times(1).WillOnce(::testing::Return(consumed));
    EXPECT_CALL(animal, eat(carbs - consumed)).Times(1);
    EXPECT_CALL(animal, die()).Times(0);
    ASSERT_TRUE(isAliveAtEndOfDay<MockHorse>(steps, carbs, &animal));
};

TEST(IsAliveTest, Dies)
{
    MockHorse animal = MockHorse();
    int steps{400};
    double carbs{2000.0};
    double consumed{5000.0};

    EXPECT_CALL(animal, walk(steps)).Times(1).WillOnce(::testing::Return(consumed));
    EXPECT_CALL(animal, eat(carbs - consumed)).Times(0);
    EXPECT_CALL(animal, die()).Times(1);
    ASSERT_FALSE(isAliveAtEndOfDay<MockHorse>(steps, carbs, &animal));
};
