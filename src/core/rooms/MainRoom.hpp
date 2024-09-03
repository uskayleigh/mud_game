#ifndef MAINROOM_HPP
#define MAINROOM_HPP

#include "core/Room.hpp"
#include "TreasureRoom.hpp"  // Include the TreasureRoom header

class MainRoom : public Room {
public:
    MainRoom();

    // Ensure the method declaration matches the definition
    void setupExits(TreasureRoom* treasureRoom);
};

#endif // MAINROOM_HPP
