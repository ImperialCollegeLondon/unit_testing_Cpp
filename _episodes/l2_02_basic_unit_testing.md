---
title: "Introduction to Unit Testing using Google Test"
teaching: TBC
exercises: TBC
questions:
- "What framework/libraries can be used for Unit Testing in C++?"
- "What is Google test library?"
- "How to write Unit Test using Google test?"
objectives:
- "Understand the basic components of a unit test"
- "Understand how to write a unit test using google test library?"
- "Understand how to compile and run the test?"
- "Understand some of the macros available in google test"
---

## Popular frameworks for testing in C++

There are a number of popular frameworks that can be used for testing in C++. A few of them are mentioned below:-

- [GoogleTest](https://google.github.io/googletest/)
- [Boost.Test](https://www.boost.org/doc/libs/1_82_0/libs/test/doc/html/index.html)
- [CppUtest](http://cpputest.github.io/)
- [Catch2](https://github.com/catchorg/Catch2)
- [UT++](https://boost-ext.github.io/ut/)
- [doctest](https://github.com/doctest/doctest)

In this course, we will focus mainly on GoogleTest.


## A brief about GoogleTest

Simply defining, GoogleTest is a testing framework developed by Google's testing technology team to develop and write C++ tests.  GoogleTest offers multiple advantages over other frameworks:-

1. **Comprehensive Features**: Google Test provides a rich set of features, including a wide range of assertion macros, test fixtures, parameterized tests, test discovery, test filtering, and powerful mocking capabilities. It offers a complete testing framework that can handle various testing scenarios.
2. **Integration with Google Test ecosystem**: Google Test integrates well with other tools and libraries in the Google Test ecosystem. For example, it can be seamlessly used with Google Mock for creating mock objects and behaviours. This integration enhances the testing capabilities and flexibility.
3. **Large and Active Community**: Google Test has a large and active community of developers. This means that there is ample support available in terms of documentation, tutorials, forums, and online resources. 
4. **Mature and Stable**: It is a mature and stable framework that has been used extensively in industry projects and open-source software. 
5. **Wide Platform Support**: Google Test supports multiple platforms, including Windows, Linux, macOS, and various compilers. It is compatible with popular development environments and build systems, making it suitable for a wide range of C++ projects.
6. **Flexible and Extensible**: Google Test provides flexibility in test organization and customization. It allows you to structure your tests using test cases and test suites. You can also define custom test fixtures and customize test execution and reporting. Additionally, Google Test can be extended with custom assertion macros and utilities to suit your specific testing needs.





