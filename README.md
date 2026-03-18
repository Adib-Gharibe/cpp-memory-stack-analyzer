# C++ Memory and Stack Analyzer

This project analyzes memory usage, recursion depth, and system resource limits in C++.

It demonstrates how heap allocation, recursion, and system resource monitoring behave during program execution.

## Features

- Prints stack and heap system limits
- Tests dynamic heap memory allocation
- Measures recursion depth
- Tracks CPU time usage
- Exports runtime data for analysis

## Technologies

- C++
- Linux system calls
- getrusage
- getrlimit
- file output using ofstream

## Compile

```bash
g++ -std=c++17 main.cpp -o analyzer
```

## Run

```bash
./analyzer
```

## Learning Goals

- Understanding stack vs heap memory
- Measuring resource usage in C++
- Experimenting with recursion limits
- Analyzing system resource behavior
