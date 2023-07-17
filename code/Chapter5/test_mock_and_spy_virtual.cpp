#include <iostream>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

class Animal
{
public:
    virtual ~Animal() = default;
    virtual double walk(int steps) = 0;
    virtual void eat(double carbs) = 0;
    virtual void die() = 0;
};

bool isAliveAtEndOfDay(int steps, double carbs, Animal *animal)
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

class MockAnimal : public Animal
{
public:
    MOCK_METHOD(double, walk, (int), (override));
    MOCK_METHOD(void, eat, (double), (override));
    MOCK_METHOD(void, die, (), (override));
};

TEST(IsAliveTestVirtual, Lives)
{
    MockAnimal animal;
    int steps{400};
    double carbs{2000.0};
    double consumed{500.0};

    EXPECT_CALL(animal, walk(steps)).Times(1).WillOnce(::testing::Return(consumed));
    EXPECT_CALL(animal, eat(carbs - consumed)).Times(1);
    EXPECT_CALL(animal, die()).Times(0);
    ASSERT_TRUE(isAliveAtEndOfDay(steps, carbs, &animal));
};

TEST(IsAliveTestVirtual, Dies)
{
    MockAnimal animal;
    int steps{400};
    double carbs{2000.0};
    double consumed{5000.0};

    EXPECT_CALL(animal, walk(steps)).Times(1).WillOnce(::testing::Return(consumed));
    EXPECT_CALL(animal, eat(carbs - consumed)).Times(0);
    EXPECT_CALL(animal, die()).Times(1);
    ASSERT_FALSE(isAliveAtEndOfDay(steps, carbs, &animal));
};
