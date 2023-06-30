---
title: "Introduction to testing"
teaching: TBC
exercises: TBC
questions:
- "Why are some of best practices that should be followed while writing unit tests?"
objectives:
- "Understand some of the best practices for writing unit tests."
keypoints:
- "Unit tests should be isolated"
- "Unit tests should be repeatable"
- "Unit tests should be readable"
- "Unit tests should have one assertion per test"
---

## 1. Best Practices for writing unit tests
Below, we share some of the best practices that should be followed while writing unit tests. The suggestions below are geneal in nature and apply to all testting frameworks and not just C++. Some of the suggestions are from the book [Modern C++ programming with Test-Driven-Development](`https://www.amazon.co.uk/Modern-Programming-Test-Driven-Development-Better/dp/1937785483`) by *Jeff Langr*. We have also used some suggestions that came out from a simple Google search and those have not been explicity cited.

1. **Test Organization and Naming Conventions**:
    - Organize tests into logical groups using test suites and test case names that reflect the functionality or components being tested.
    - Use descriptive and meaningful names for test methods that clearly indicate the scenario or behavior being tested.
    - Follow a consistent naming convention for test methods, such as prefixing them with "Test" or using a "should" or "can" style of naming.

2. **Keep Tests Focused and Isolated**:

    - Ensure that each test case focuses on a single behavior or scenario, testing one aspect of your code at a time.
    - Avoid writing tests that depend on the state or side effects of other tests. Each test case should be independent and self-contained.
    - Use test fixtures to encapsulate common setup and teardown logic, promoting code reusability and reducing code duplication.
    - In general follow the rule **ONE ASSERT PER TEST** as much as possible.

3. **Write Clear and Readable Tests**:
    - Use comments to explain the purpose and expected behavior of each test case, especially when dealing with complex or edge cases. A comment would enhance the readability of the test.
    - Break down complex test scenarios into smaller, manageable assertions. Each assertion should test a single condition.

4. **Choose Appropriate Assertions**:
    - Select the most appropriate assertion macros provided by Google Test that closely match the behavior being tested.
    - Use specific assertions (e.g., ASSERT_EQ, ASSERT_TRUE, ASSERT_FALSE) instead of general assertions (e.g., ASSERT or EXPECT) to improve test failure diagnosis.

5. **Test Coverage and Code Review**:
    - Aim for high code coverage by ensuring that the tests exercise different code paths, including error handling, edge cases, and boundary conditions.
    - Regularly review your test suite to identify gaps in test coverage and update it accordingly. Periodically review and remove redundant or obsolete tests.
    - Use code coverage analysis tools to measure the effectiveness of your tests and identify areas that need additional testing.

6. **Maintain Test Independence**:
    - Avoid sharing mutable state between tests. Each test case should start with a clean and consistent state to ensure test independence.
    - Reset any modified state or resources in the test teardown phase to leave the environment in a predictable state for subsequent tests.
    - Be cautious when using global variables or static state in tests, as they can introduce unwanted dependencies and make tests more fragile.

7. **Mocking and Test Doubles**:
    - Use mocking frameworks, such as Google Mock, to create test doubles (mock objects) for dependencies that need to be isolated or controlled during testing.

8. **Continuous Integration and Test Execution**:
    - Integrate your unit tests into your continuous integration (CI) process to ensure that tests are automatically executed with each code change.
    - Aim for fast and deterministic tests by minimizing external dependencies, reducing I/O operations, and avoiding non-deterministic behaviors.

9. **Test Failure Investigation**:
    - When a test fails, investigate and diagnose the failure by examining the failure message, log output, and any relevant debug information.

10. **Ensure Repeatability**:
    - Ensure that the unit tests produce the same results when run at different times, different machines etc.
### Summary

In this chapter, we described some of the best practices that should be followed while writing unit tests.

{% include links.md %}
 