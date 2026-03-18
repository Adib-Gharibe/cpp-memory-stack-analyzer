# C++ Memory and Stack Analyzer

This project analyzes memory usage, recursion depth, and system resource limits in C++ on Linux systems.

The program measures CPU usage, heap allocation behavior, and recursion stack growth using Linux system calls such as `getrusage` and `getrlimit`.

---

## Features

- Prints system stack and heap limits
- Analyzes heap memory allocation
- Measures recursion depth
- Tracks CPU user time and system time
- Detects heap allocation limits
- Exports runtime measurements for further analysis

The program generates the following files:

- `gnuMem.txt` – data from the heap allocation experiment
- `gnuRec.txt` – data from the recursion experiment

---

## Technologies

- C++
- Linux system calls
- `getrusage`
- `getrlimit`
- file output using `ofstream`

---

## Experiments

The program performs several experiments to analyze memory behavior.

### Heap Memory Experiment

The function `funcMem()` dynamically allocates memory on the heap and measures CPU usage during the allocation process.

This experiment shows how user CPU time and system CPU time evolve as memory allocation increases.

### Recursion Experiment

The function `funcRec()` recursively calls itself and allocates stack memory during each recursion step.

This demonstrates how recursion depth affects CPU time and stack usage.

### Automatic Heap Test

The program automatically increases heap allocation until a `bad_alloc` exception occurs.

This helps determine the practical heap memory limit of the system.

### Automatic Stack Test

The program recursively calls a function until a stack overflow occurs, estimating the maximum recursion depth.

---

## Compile

Compile the program using g++:

```bash
g++ -std=c++17 main.cpp -o analyzer
