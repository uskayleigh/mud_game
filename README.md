
# Simple Text-Based Adventure Game

This is a simple text-based adventure game written in C++. The game allows a player to navigate between rooms, interact with objects and furniture, manage an inventory, and save/load their game state.

## Features

- **Room Navigation**: Move between different rooms using commands like `go north`, `go south`, etc., or using shortcuts `n`, `s`, `e`, `w`.
- **Object Interaction**: Examine furniture and take objects to add to your inventory.
- **Inventory Management**: View, add, and remove items from your inventory.
- **Save/Load Game State**: Save your game progress, including your current room, inventory, and room states, and load it later.

## Requirements

- C++11 or higher

## Compilation

To compile the game, use the following command:

```bash
g++ -std=c++11 -o adventure main.cpp Room.cpp Object.cpp Furniture.cpp Player.cpp utils.cpp
```

This will generate an executable named `adventure`.

## Running the Game

To run the game, use the following command:

```bash
./adventure
```

## Commands

Once the game is running, you can use the following commands:

- `look`: Describe the current room, listing furniture, objects, and exits.
- `go <direction>`: Move to another room in the specified direction (e.g., `go north`).
- Shortcuts: `n` (north), `s` (south), `e` (east), `w` (west) for quick movement.
- `examine <furniture|object>`: Examine furniture or an object in the room.
- `take <object>`: Take an object and add it to your inventory.
- `inventory`: Show the current inventory.
- `save`: Save the current game state.
- `quit`: Save the game and exit.

## Save and Load Game State

The game automatically loads the last saved state when it starts. The game state includes:

- Player's name
- Current room
- Inventory
- Room states (objects in each room)

To save your progress, use the `save` command. The game state is stored in a file named `game_state.txt` in the same directory as the executable.

## File Structure

- `main.cpp`: The main game loop and command processing.
- `Room.hpp/cpp`: Handles room descriptions, exits, and objects in each room.
- `Player.hpp/cpp`: Manages the player's inventory and interactions with objects.
- `Object.hpp/cpp`: Represents objects that can be interacted with or taken.
- `Furniture.hpp/cpp`: Represents furniture that can be examined but not taken.
- `utils.hpp/cpp`: Utility functions for saving and loading the game state.

## License

This project is open source and available under the MIT License.
