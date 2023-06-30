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

Sooner or later you will face a piece of code that is not straight forward to write a test for. It might be because it calls a function that requests some data from a piece of hardware. Or because it needs to access a database that it is not available in the testing environment. Or simply because it triggers a complex and time consuming computation process that is only suited to run in a supercomputer. Whatever the reason, you will be in trouble. Moreover, you might want to test if some intermediate result of the calculation, and not just the final output, is a valid one.

There is one possible solution: replace the problematic function by another one that, for the purposes of the test, behaves in a similar manner but without the problematic functionality of the original one. These replacements are called **test doubles**.

### Test doubles

Test doubles are artificial replacements of functions or objects that prevent - or make more difficult - to test a particular part of the code. Depending exactly of what these replacements do, and also on the programming language, they receive different names. From the [Wikipedia], we have:

- **Test stub**: used for providing the tested code with "indirect input", i.e canned answers so that the code can keep running.
- **Mock object**: used for verifying "indirect output" of the tested code, by first defining the expectations before the tested code is executed.
- **Test spy**: used for verifying "indirect output" of the tested code, by asserting the expectations afterwards, without having defined the expectations before the tested code is executed.
- **Fake object**: used as a simpler implementation, e.g. using an in-memory database in the tests instead of doing real database access.
- **Dummy object**: used when a parameter is needed for the tested method but without actually needing to use the parameter.

Which type of test double to use will depend on the specific code you want to test and what the double is meant to replace. Functions are often replaced with stubs or fakes while objects of more complex classes with multiple methods or attributes require more elaborate mocks.

Now, the complexity becomes how to use them!

[Wikipedia]: https://en.wikipedia.org/wiki/Test_double

### Dependency injection

Consider the following function that normalizes an array according to some definition of norm (ignore whether this is the most performing approach or not):

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

Well, you cannot. `calculate_norm` is hardcoded in the definition of `normalize` so replacing it for another function is not possible, specially if we consider that `normalize` will be defined in a particular file within your code and you are testing it somewhere else.

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
{: .callout}

## Introducing Google Mock

TBC

## Test doubles in action

In this section we present a few exercises with their solutions of using test doubles to enable the testing of untestable code. In all cases, we assume that dependency injection is enabled, one way or another.

Keep in mind that there are often multiple ways of using test doubles for a particular problem, so you might come up with a different solution for the exercises below.

> ## Test `normalize_v2`
>
> Write a test using the Google Tests tools described in previous chapters to check that `normalize` behaves as it should.
>
> > ## Solution
> >
> > In this case, a simple stub will solve our problem. Let's define or fake function as:
> >
> > ```cpp
> > double norm_stub(int array[])
> > {
> >     return 10.0;
> > }
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
> >     }
> > }
> > ```
> >
> > Here we have used a specific array for the test, but we could have explored a larger space of options and edge cases using parametric testing, as described in a previous episode. The test written this way, with a stub for the norm, lets you test only what `normalize_v2` is doing - i.e. a true unit test -, without influence from the process of calculating the norm.
> {: .solution}
{: .challenge}


## Summary

TBC

{% include links.md %}
