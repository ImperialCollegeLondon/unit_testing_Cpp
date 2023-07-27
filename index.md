---
layout: lesson
root: .  # Is the only page that doesn't follow the pattern /:path/index.html
permalink: index.html  # Is the only page that doesn't follow the pattern /:path/index.html
---

This course teaches the fundamental concepts and skills required to design effective
test suites for modern C++ software.

The consequences of writing buggy software can range from the mild to the catastrophic,
but one thing remains invariant: many bugs can be discovered and fixed quickly with a
well designed and maintained suite of tests. Well tested code inspires confidence in
stakeholders, and the absence of tests is often viewed as an unacceptable liability,
particularly in scientific and engineering applications.

To ensure that your software continues to meet the increasingly stringent expectations
of users and stakeholders in a sustainable and future-proof way, we will learn to
implement modern software testing concepts, such as fixtures and parametrised testing using
the popular [GoogleTest](https://github.com/google/googletest) C++ testing framework.


## Syllabus

- Introduction and motivation for software testing.
- Writing simple unit tests.
- Automatic setup and teardown using test fixtures.
- Test ranges of inputs using parametrised tests.
- Simulate interaction with other code using test doubles.
- Some best practices to keep you out of trouble.

## Learning outcomes

After completing this workshop, you will understand:
1.	The usefulness and importance of software testing.
2.	How to write effective C++ tests using GoogleTest.
3.	How to automate test preparation and cleanup with test fixtures.
4.	How to easily test ranges of inputs with parametrised tests.
5.	How to simulate other code in tests with test doubles.

## Delivery of the course

Material will be delivered as a lecture with task following the Carpentries teaching
style.

- The instructor will walk you through the theoretical material of the course,
  demonstrating the execution of the relevant code and instructions. **You are highly encouraged to
  code along** and execute the instructions at the same time.
- Throughout the lessons, there are **yellow boxes** highlighting particularly challenging
  or important concepts.
- There are also exercises in **orange boxes**. The instructor will give you time to try
  to do them yourself before going through the solution. This is often available in a
  folded part of the orange box, so you can check it at any time.
- When doing exercises, put a green sticker in your computer whenever you are done, or a
  pink/orange one if you need support. A helper will go to you.
- For online sessions, raise your hand if you are done with the exercise and write
 any questions or problems directly into the chat, so a helper can try to solve it.

> ## Prerequisites
>
> A working knowledge of C++ programming is essential.
{: .prereq}

{% include links.md %}
