#include "MainRoom.hpp"
#include "TreasureRoom.hpp"  // Include the TreasureRoom header
#include "furniture/Container.hpp"  // Include the Container header for using Container

MainRoom::MainRoom() : Room("Main Room", "You are in a large, empty room with stone walls. There is but a single exit to the north. It is a large iron door, unrusted though yet obviously worn well down with time. There is a single, large, keyhole towards the centre.") {
    // Define objects
    Object* treasure = new Object("gold-coins", "A pile of shiny gold coins.");
    Object* goldKey = new Object("gold-key", "A golden key, it looks mighty important.");

    // Define furniture
    Container* chest = new Container("chest", "An old wooden chest with a rusty lock.");
    chest->addObject(*treasure);
    chest->addObject(*goldKey);

    // Add furniture and objects to the room
    this->addFurniture(chest);
}

void MainRoom::setupExits(TreasureRoom* treasureRoom) {
    this->addExit("north", treasureRoom);
    this->lockExit("north"); // Lock the door to the Treasure Room by default
}
