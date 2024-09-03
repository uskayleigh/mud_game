
# Simple C++ Multi-User Dungeon (MUD)

This is a basic C++ implementation of a Multi-User Dungeon (MUD). It includes a simple text-based interface where players can explore a small world consisting of interconnected rooms. Players can move between rooms, examine their surroundings, and interact with the environment.

## Features

- Multiple rooms with descriptions.
- Navigation between rooms using directional commands.
- Basic command interface with shortcuts.

## Requirements

To compile and run this project, you'll need:

- A C++ compiler (e.g., GCC, Clang, or MSVC).
- A terminal or command prompt to run the program.

## Compilation Instructions

To compile the code, navigate to the directory containing the source file (`mud.cpp`) and run the following command:

```sh
g++ -o mud mud.cpp
```

This will generate an executable named `mud`.

## Running the Program

After compiling the program, you can run it by typing:

```sh
./mud
```

## How to Play

Once the game starts, you'll be prompted to enter your name. After that, you can explore the rooms using the following commands:

- **look**: Describes the current room and lists the players present and available exits.
- **go <direction>**: Moves you to another room in the specified direction (e.g., `go north`).
- **n, s, e, w**: Shortcuts for moving north, south, east, and west, respectively.
- **quit**: Exits the game.

### Example Commands

```sh
look
go north
n
s
quit
```

## Expanding the Game

This project is designed to be a starting point for building more complex MUDs. Here are some ideas for expanding the game:

- **Add more rooms**: Create new rooms with unique descriptions and connect them to the existing rooms.
- **Implement items**: Allow players to pick up, drop, and use items found in the rooms.
- **Add NPCs**: Introduce non-player characters that can interact with the players.
- **Networking**: Extend the game to allow multiple players to connect and interact in real-time.

## License

This project is open-source and licensed under the MIT License. Feel free to use, modify, and distribute this code as you see fit.