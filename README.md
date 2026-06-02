# Tetris

## Overview

Tetris is a desktop implementation of the classic puzzle game developed in C++ using the MVC (Model–View–Controller) architectural pattern.

The project was created as an educational software engineering project with a focus on:

* Object-Oriented Programming (OOP)
* SOLID principles
* MVC architecture
* UML modeling
* Static code analysis
* Modern C++20

---

## Features

### Gameplay

* Classic Tetris mechanics
* Piece rotation
* Hard drop
* Hold system
* Next piece queue
* Line clearing
* Score calculation
* Level progression
* Game timer
* High score tracking
* Statistics collection
* Configurable settings

### Technical Features

* MVC architecture
* Modular project structure
* UML documentation
* Clang-Tidy support
* Cppcheck support
* Clang-Format support

---

## Project Structure

```text
src/
├── model/
│   ├── board/
│   ├── tetromino/
│   ├── game/
│   ├── queue/
│   ├── hold/
│   ├── score/
│   ├── level/
│   ├── statistics/
│   ├── highscore/
│   ├── settings/
│   ├── rules/
│   ├── random/
│   ├── timer/
│   └── types/
│
├── view/
│
├── controller/
│
├── state/
│
├── services/
│
└── interfaces/
```

---

## Architecture

The application follows the MVC pattern.

### Model

Responsible for:

* game logic
* game rules
* score calculation
* level progression
* statistics
* persistence

### View

Responsible for:

* rendering
* menus
* animations
* user interface

### Controller

Responsible for:

* processing user input
* coordinating Model and View
* managing game states

---

## UML Documentation

Documentation is located in the `docs` directory:

* UML_Class_Diagram.puml
* Package_Diagram.puml
* Dependency_Graph.puml

These files can be opened using PlantUML.

---

## Build Requirements

Required software:

* CMake 3.20+
* C++20 compatible compiler
* Clang-Format (optional)
* Clang-Tidy (optional)
* Cppcheck (optional)

Recommended compilers:

* GCC 13+
* Clang 16+
* MSVC 2022

---

## Build Instructions

### Configure

```bash
cmake -B build
```

### Build

```bash
cmake --build build
```

### Run

```bash
./build/Tetris
```

---

## Static Analysis

### Clang-Format

```bash
./scripts/format.sh
```

### Clang-Tidy

```bash
./scripts/run-clang-tidy.sh
```

### Cppcheck

```bash
./scripts/run-cppcheck.sh
```

---

## Design Principles

The project follows:

* SOLID principles
* Single Responsibility Principle
* Dependency Inversion Principle
* Encapsulation
* Separation of Concerns

---

## Author

Educational project developed as part of a software engineering and object-oriented programming course.
