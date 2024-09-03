
# MUD Game

This is a simple text-based MUD (Multi-User Dungeon) game developed in C++. The game allows players to explore different rooms, interact with objects and furniture, manage their inventory, and save/load their game state.

## Features

- **Room Navigation**: Move between rooms using commands like `go north`, `go south`, or using shortcuts (`n`, `s`, `e`, `w`).
- **Object Interaction**: Examine furniture and take objects to add them to your inventory.
- **Inventory Management**: View, add, and remove items from your inventory.
- **Save/Load Game State**: Save your game progress, including your current room, inventory, and room states, and load it later.

## Requirements

- **C++11** or higher

## Compilation

To compile the game, navigate to the project directory and use the following command:

```bash
g++ -std=c++11 -o adventure src/main.cpp src/core/Room.cpp src/core/Player.cpp src/objects/Object.cpp src/furniture/Furniture.cpp src/utils/utils.cpp src/utils/Config.cpp
```

This will generate an executable named `adventure`.

## Running the Game

To start the game, run the following command:

```bash
./adventure
```

## Commands

Once the game is running, you can use the following commands:

- `look`: Describe the current room, listing furniture, objects, and exits.
- `go <direction>`: Move to another room in the specified direction (e.g., `go north`).
- Shortcuts: Use `n` (north), `s` (south), `e` (east), `w` (west) for quick movement.
- `examine <furniture|object>`: Examine furniture or an object in the room.
- `take <object>`: Take an object and add it to your inventory.
- `inventory`: Show your current inventory.
- `save`: Save the current game state.
- `load`: Load the previously saved game state.
- `quit`: Exit the game.

## Save and Load Game State

The game supports saving and loading your progress. The saved game state includes:

- Player's name
- Current room
- Inventory
- Room states (objects and furniture in each room)

To save your progress, use the `save` command. The game state is stored in a file named `savegame.txt` in the same directory as the executable. You can load this state later with the `load` command.

## File Structure

- `src/main.cpp`: The main game loop and command processing.
- `src/core/Room.hpp/cpp`: Handles room descriptions, exits, and objects in each room.
- `src/core/Player.hpp/cpp`: Manages the player's inventory and interactions with objects.
- `src/objects/Object.hpp/cpp`: Represents objects that can be interacted with or taken.
- `src/furniture/Furniture.hpp/cpp`: Represents furniture that can be examined but not taken.
- `src/utils/utils.hpp/cpp`: Utility functions for saving and loading the game state.
- `src/utils/Config.hpp/cpp`: Configuration settings for the game.

## License

This project is licensed under the MIT License.

## Contribution

Feel free to fork this repository, make your own changes, and submit pull requests. Your contributions are welcome!
