---
title: Setup
---

To complete this course you need a computer with access to the internet. All attendees
should follow the steps below to install the necessary tools and download the exercises
*before the session*.

## Installing tools

Firstly, you need to install a C++ compiler if you do not have one already. It should
support the C++14 standard (which all modern compilers do). You also need
[CMake](https://cmake.org/), at least version 3.11.

You will need a text editor or IDE to work with the example code. For Linux and macOS
users, [Visual Studio Code] is a good option, but for Windows users we strongly
recommend that you use [Visual Studio Community], which includes a compiler, CMake and
an IDE.

Nowadays, many popular IDEs, including Visual Studio and Visual Studio Code, provide
built-in support for CMake and CTest and will automatically configure your project if a
CMakeLists.txt file is discovered in its root. For Visual Studio Code, you will need the
[CMake extension] installed.

[Visual Studio Code]: https://code.visualstudio.com/
[Visual Studio Community]: https://visualstudio.microsoft.com/vs/community/
[CMake extension]: https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools

### Windows: Installing Visual Studio Community

Windows users can [download Visual Studio Community here]. When installing it, make sure
you select the relevant options for C++ development.

[download Visual Studio Community here]: https://visualstudio.microsoft.com/vs/community/

### macOS: Installing clang and CMake

If you are developing on macOS, it is easiest to install your developer tools via
Homebrew. If you do not have Homebrew installed, please [visit the Homebrew website] and
follow the instructions to install it.

Then you can install [the clang compiler] and CMake like so:

```sh
brew install llvm cmake
```

[visit the Homebrew website]: https://brew.sh/
[the clang compiler]: https://clang.llvm.org/

### Linux: Installing gcc and CMake

If you are using Ubuntu Linux, you can install [the gcc compiler] and CMake with your
package manager:

```sh
sudo apt install build-essential cmake
```

[the gcc compiler]: https://gcc.gnu.org/

## Downloading the exercises

The exercises are available [in a GitHub repository here]. If you are familiar with git,
follow the link to the repository and clone it locally. Alternatively, [download the
zip file directly] and extract it somewhere.

[in a GitHub repository here]: https://github.com/ImperialCollegeLondon/unit_testing_Cpp_exercises
[download the zip file directly]: https://codeload.github.com/ImperialCollegeLondon/unit_testing_Cpp_exercises/zip/refs/heads/main

## Testing that your setup works

Lastly, it is very important that you check that all of these tools have been installed
correctly on your system before the session starts.

We will now check that the example code builds correctly on your machine. Start by
opening a terminal and navigating to wherever you extracted the exercise code before.
Note that if you are doing this on Windows, it is very important that you use
Developer Powershell (or Developer Command Prompt) as your terminal, otherwise you won't
be able to use CMake.

Once you have done that, you can configure the project with CMake like so:

```sh
cmake -B build
```

This will generate some files in a new folder, `build`.

Then you can build the code by running:

```sh
cmake --build build/
```

If this completes successfully, then congratulations! You have a working development
machine.

{% include links.md %}
