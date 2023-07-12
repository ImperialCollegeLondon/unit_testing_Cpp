---
title: "Tests doubles and dependency injection"
teaching: TBC
exercises: TBC
questions:
- "TBC"
objectives:
- "TBC"
keypoints:
- "TBC"
---

## Testing untestable code

Sooner or later you will face a piece of code that is not straightforward to write a test for. It might be because it calls a function that requests some data from a piece of hardware, or because it needs to access a database that is not available in the testing environment, or simply because it triggers a complex and time consuming computation process that is only suited to run in a supercomputer. Whatever the reason, you have a problem. Moreover, you might want to test if some intermediate result in the calculation is valid, and not just the final output.

There is one possible solution: replace the problematic function by another one that, for the purposes of the test, behaves in a similar manner but without the problematic functionality of the original one. These replacements are called **test doubles**.

### Test doubles

Test doubles are artificial replacements of functions or objects that prevent - or hinder - testing a particular part of the code. Depending on what these replacements do, and also on the programming language, they receive different names. From the [Wikipedia], we have:

- **Test stub**: used for providing the tested code with "indirect input", i.e. canned answers so that the code can keep running.
- **Mock object**: used for verifying "indirect output" of the tested code, by first defining the expectations before the tested code is executed.
- **Test spy**: used for verifying "indirect output" of the tested code, by asserting the expectations afterwards, without having defined the expectations before the tested code is executed.
- **Fake object**: used as a simpler implementation, e.g. using an in-memory database in the tests instead of doing real database access.
- **Dummy object**: used when a parameter is needed for the tested method, but when we don't actually need to use the parameter.

Which type of test double to use will depend on the specific code you want to test and what the double is meant to replace. Functions are often replaced with stubs or fakes, while objects of complex classes with multiple methods or attributes require more elaborate mocks.

Now, the complexity becomes how to use them!

[Wikipedia]: https://en.wikipedia.org/wiki/Test_double

### Dependency injection

Consider the following function that normalizes an array according to some definition of norm (ignore whether this is the most performant approach or not):

```cpp
void normalize_v1(int array[], int length)
{
    double norm{calculate_norm(array)};

    for (int i{0}; i < length; ++i)
    {
        array[i] /= norm;
    }
}
```

You need to test it, but you do not want to have to calculate the norm along the way. How would you tell the `normalize` function to use a test double for `calculate_norm` and not the real one?

Well, you cannot. `calculate_norm` is hardcoded in the definition of `normalize` so replacing it for another function is not possible, especially if we consider that `normalize` will be defined in a particular file within your code, but you are testing it somewhere else.

Now consider the following alternative version of the function `normalize`:

```cpp
void normalize_v2(
    int array[],
    int length,
    std::function<double(int[])> func = calculate_norm
    )
{
    double norm{func(array)};

    for (int i{0}; i < length; ++i)
    {
        array[i] /= norm;
    }
}
```

Compared with the first version, this `normalize` function does exactly the same thing and can be invoked in exactly the same way but, in addition, you can optionally control what specific function is used to calculate the norm. In particular, you can provide a test double that replaces the default `calculate_norm`.

This is called [dependency injection](https://en.wikipedia.org/wiki/Dependency_injection) and its application goes well beyond testing: it helps make the code more modular and re-usable by making it less intrinsically linked to specific design choices or dependencies. In the example, we could use a different definition of norm - [and there are quite a few!](https://en.wikipedia.org/wiki/Norm_(mathematics))

> ### Dependency injection is an important design pattern
>
> Do not disregard the value of dependency injection as an approach only useful in testing. If you design your code with dependency injection in mind, it will become more flexible and powerful. Here we have presented just one way of doing dependency injection, but there are other approaches that might be more suitable to your particular case.
>
> Having said that, **enabling dependency injection in your code is essential to be able to use test doubles**, including the mocks we describe next, so make sure you fully understand what it means and how to write your code *the right way*.
{: .callout}

## Introducing Google Mock

[Google Mock], or gMock, is a framework for creating mock **classes** and using them in C++. A mock class implements the same interface as the real class (so it can be used as one), but lets you specify how it will be used and what it should do at runtime, setting expectations on these interactions.

It is worth emphasizing that gMock will let you mock **classes** and not top level functions.

The process of using gMock is, in general, always the same:

1. You [create the mocked class using the `MOCK_METHOD` macro](https://google.github.io/googletest/gmock_cook_book.html#creating-mock-classes) to mock the methods that will be used in the test.
2. When running the tests, you set the expectations of what should happen when each relevant mocked method is called [using the `EXPECT_CALL` macro](https://google.github.io/googletest/gmock_for_dummies.html#general-syntax). The expectations will be automatically checked at the end of the test.

### Mocking virtual classes

Here we give a simple example to illustrate the process, but read the gMock [Mocking Cookbook] for a more detailed description of the possibilities and the inputs these macros need. Let's assume we want to mock the following virtual class because one of its subclasses is being used in the function we want to test:

```cpp
class Animal {
  virtual ~Animal() {};
  virtual double walk(int steps);
  virtual void eat(double carbs);
  virtual void die();
};
```

The corresponding mocked class will be:

```cpp
class MockAnimal : public Animal {
  public:
    MOCK_METHOD(double, walk, (int), (override));
    MOCK_METHOD(void, eat, (double), (override));
    MOCK_METHOD(void, die, (), (override));
};
```

Now let's write a test for the following function, which finds out if an animal is dead or alive at the end of the day depending on how much food it has taken and how much it has walked.

```cpp
bool isAliveAtEndOfDay(int steps, double carbs, Animal animal) {
  double spent_carbs{animal.walk(steps)};
  if (spent_carbs > carbs) {
    animal.die();
    return false;
  }
  animal.eat(carbs - spent_carbs);
  return true;
}
```

If we were to use a real implementation of `Animal`, let's say a `Horse`, testing this function would be complicated because the result would depend on the specific metabolism of the animal, which might be quite complicated (and potentially time consuming to run). So we can use `MockAnimal` instead to check that the logic of the function is correct. A couple of tests for this would look as:

```cpp
using ::testing::Return;

TEST(IsAliveTest, Lives) {
  Animal animal = MockAnimal();
  int steps{400};
  double carbs{2000.0};
  double consumed{500.0};

  EXPECT_CALL(animal, walk(steps)).Times(1).WillOnce(Return(consumed));
  EXPECT_CALL(animal, eat(carbs-consumed)).Times(1);
  EXPECT_CALL(animal, die()).Times(0);
  ASSERT_TRUE(isAliveAtEndOfDay(steps, carbs, animal))
}

TEST(IsAliveTest, Dies) {
  Animal animal = MockAnimal();
  int steps{400};
  double carbs{2000.0};
  double consumed{5000.0};

  EXPECT_CALL(animal, walk(steps)).Times(1).WillOnce(Return(consumed));
  EXPECT_CALL(animal, eat(carbs-consumed)).Times(1);
  EXPECT_CALL(animal, die()).Times(1);
  ASSERT_FALSE(isAliveAtEndOfDay(steps, carbs, animal))
}
```

[Google Mock]: https://google.github.io/googletest/gmock_for_dummies.html
[Mocking Cookbook]: https://google.github.io/googletest/gmock_cook_book.html

### Mocking non-virtual classes

While the above situation is common enough, there will be cases when you just don't have a common virtual class to inherit from. In those cases, you can still use mocking but you will need to make your code flexible enough so your functions can accommodate unrelated classes as inputs. The way of doing this would be using templates.

Following with the above example, let's assume that now we don't have an `Animal` abstract class, but rather a concrete `Horse` class with the same interface.

```cpp
class Horse {
  public:
    ~Horse() {};
    double walk(int steps);
    void eat(double carbs);
    void die();
};
```

Mocking the above will look very similar except that we will be creating a brand new class altogether, not be inheriting from any other class, and we will omit the `override` parameter. Contrary to the case of virtual classes, here we only need to indicate the methods that will actually be used in the tests.

```cpp
class MockHorse {
  public:
    MOCK_METHOD(double, walk, (int));
    MOCK_METHOD(void, eat, (double));
    MOCK_METHOD(void, die, ());
};
```

The function we want to test is the same, except that now only accept `Horse` as input:

```cpp
bool isAliveAtEndOfDay(int steps, double carbs, Horse animal) {
  // as above
};
```

How do we test this? Well, we will need to modify our function to use templates, and indicate when the function is supposed to use a `Horse` instance and when a `MockHorse` instance. Contrary to the case of virtual classes above, this is fixed at compilation time rather than at runtime:

```cpp
template <class GenericHorse>
bool isAliveAtEndOfDay(int steps, double carbs, GenericHorse animal) {
  // as above
};
```

In production code, we will use this function as `isAliveAtEndOfDay<Horse>(..., horse_instance)` while in the tests we will call this as `isAliveAtEndOfDay<MockHorse>(..., mock_horse_instance)`.

And that's all! The construction of the tests is otherwise the same, for example:

```cpp
TEST(IsAliveTest, Lives) {
  MockHorse animal = MockHorse();
  int steps{400};
  double carbs{2000.0};
  double consumed{500.0};

  EXPECT_CALL(animal, walk(steps)).Times(1).WillOnce(Return(consumed));
  EXPECT_CALL(animal, eat(carbs-consumed)).Times(1);
  EXPECT_CALL(animal, die()).Times(0);
  ASSERT_TRUE(isAliveAtEndOfDay<MockHorse>(steps, carbs, animal))
};
```

As it can be seen, it involves more steps that the case of having a virtual class to start with, and it might require from you to modify your code in order to be able to use mocks. But, on the bright side, it might also make your code more reusable and flexible and, ultimately, powerful as it was the case when you enable dependency injection.

> ### Mocking is not always the solution
>
> In the above examples, it would have been tricky to test the logic of the function in full without mocks. However, they are not always the solution. Mocks do not work with top level functions, only with classes. Depending on the complexity of the class, setting up the mock might be too complicated and not worth it for testing the function of interest. Very often, stubs, fakes and dummies will carry you a long way before you need to use mocks.
{: .callout}

## Test doubles in action

In this section we present a few exercises with their solutions of using test doubles to enable the testing of untestable code. In all cases, we assume that dependency injection is enabled, one way or another.

Keep in mind that there are often multiple ways of using test doubles for a particular problem, so you might come up with a different solution for the exercises below.

> ## Test `normalize_v2`
>
> Write a test using the Google Tests tools described in previous chapters to check that `normalize_v2`, as defined above, behaves as it should.
>
> > ## Solution
> >
> > In this case, a simple fake will solve our problem. Let's define our fake function as:
> >
> > ```cpp
> > double norm_stub(int array[])
> > {
> >     return 10.0;
> > };
> > ```
> >
> > And then we write the test as:
> >
> > ```cpp
> > TEST(NormalizeTest, ResultCorrect) {
> >
> >     double factor{norm_stub([])};
> >     int length{3};
> >     int input[length]{1, 2, 3};
> >     int copy[length]{1, 2, 3};
> >
> >     normalize_v2(input, length, norm_stub);
> >
> >     for (int i{0}; i < length; ++i)
> >     {
> >         EXPECT_EQ(input[i] * factor, copy[i]);
> >     };
> > };
> > ```
> >
> > Here we have used a specific array for the test, but we could have explored a larger space of options and edge cases using parametric testing, as described in a previous episode. The test written this way, with a fake for the norm, lets you test only what `normalize_v2` is doing - i.e. a true unit test -, without influence from the process of calculating the norm.
> {: .solution}
{: .challenge}

> ## A second exercise
>
> TBD
>
> > ## Solution
> >
> > With its solution
> >
> {: .solution}
{: .challenge}

> ## And a third exercise
>
> TBD
>
> > ## Solution
> >
> > With its solution
> >
> {: .solution}
{: .challenge}

## Summary

Test doubles let you test your functions in isolation, decoupling them from other parts of your code or from external dependencies. There are several approaches that you can use, like stubs, fakes or mocks, but the basis for most of them to work is to write your code in such a way that is testable, using dependency injection and templates. These will make your code also more modular and reusable.

{% include links.md %}
