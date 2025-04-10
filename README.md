# ZOOTB – A Terminal-Based Zoo Simulation Game

![Language](https://img.shields.io/badge/Language-C++-blue.svg)  
![License](https://img.shields.io/badge/License-MIT-green.svg)  
![Platform](https://img.shields.io/badge/Platform-Unix%2Flike-lightgrey)  
![Status](https://img.shields.io/badge/Status-Playably%20Addictive-brightgreen)

**ZOOTB** is a fully terminal-based zoo management game written in modern C++. Designed with an emphasis on logic, structure, and fun, it lets you build enclosures, buy animals, and rate your zoo — all from the command line.

Whether you want to micromanage dolphins or let giraffes and lions roam, zOOP gives you full control (and a few headaches) as a zookeeper.

---

## Features

- **Dynamic Map-Based Zoo Grid**  
  Build enclosures like aquariums, forests, and savannas — each with distinct animal compatibility and rating rules.

- **Animal Purchase System**  
  Buy animals with names and types, place them in valid enclosures, and grow your zoo collection.

- **Enclosure Rating Mechanics**  
  Every enclosure has a rating system based on size, animals, and neighboring enclosures — optimized for strategy!

- **Shop with Real Costs**  
  Every action costs coins. Run out of cash? Time to rethink your animal investments.

- **Error-Proof Command Input**  
  Gracefully handles invalid inputs, EOF (`Ctrl+D`), and empty commands.

- **Terminal-Based Map Renderer**  
  ASCII-art style layout of your zoo that updates as you build, buy, and expand.

---

## Getting Started

### Requirements

- A C++17-compliant compiler (e.g. `g++`)
- Terminal (Linux/macOS recommended)

### Compilation

Use `g++` to compile all your source files:

```bash
g++ -o zootb *.cpp
```

Or use a Makefile if you’ve got one!

### Usage

Once compiled, just run:

```bash
./zootb
```

You'll be greeted with a fancy welcome message and a prompt:

```text
What do you want to do?
 >
```

Start building, buying, and rating!

---

## Commands

| Command        | Description |
|----------------|-------------|
| `map`          | Toggle the zoo map view |
| `shop`         | Show available animals and enclosure costs |
| `info`         | Show zoo stats or info on a specific field |
| `build`        | Build an enclosure: `build <type> <col> <row> <width> <height>` |
| `buy`          | Buy an animal: `buy <name> <col> <row>` |
| `rate`         | Rate all your enclosures and see total score |
| `quit`         | Exit the game |

---

## Sample Gameplay

```
Welcome to your Zoo "zOOP"!
This zoo has a size of 3 x 3!

    1   2   3
  +---+---+---+
1 |           |
  +   +   +   +
2 |           |
  +   +   +   +
3 |           |
  +---+---+---+

What do you want to do?
 > build aquarium 1 1 1 1

 > buy felix 1 1

 > rate
Individual ratings of enclosures:
- Aquarium (1/1): 7
Your zoo has an overall rating of 7!
```

---

## Technical Design Goals

- Object-oriented structure using polymorphism and inheritance
- Clean and modular class design: `Zoo`, `Shop`, `Enclosure`, `Animal`, etc.
- Memory safety via smart destructors and explicit ownership
- Robust input parsing & error handling
- Fun and functional terminal interface

---

## File Structure

```
.
├── src/
│   ├── main.cpp
│   ├── Zoo.cpp / .hpp
│   ├── Enclosure.cpp / .hpp
│   ├── Aquarium.cpp / .hpp
│   ├── Savanna.cpp / .hpp
│   ├── Forest.cpp / .hpp
│   ├── Animal.cpp / .hpp
│   ├── Command.cpp / .hpp
│   └── Shop.cpp / .hpp
└── README.md
```

---

## License

This project is open-source under the **MIT License**.

---

Crafted with love for animals, ASCII art, and absurd edge cases.  
**Keep your dolphins shaded, and your giraffes happy.**
