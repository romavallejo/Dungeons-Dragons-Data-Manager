#pragma once
#include "Monster.h"
#include <iostream>

class Room {
public:
    Room() {}
    Room(Monster m) {
        monster = m;
    }
    //OVERLOADS << TO BE ABLE TO PRINT ROOMS USING OS
    friend std::ostream& operator<<(std::ostream& os, Room& r) {
        os << "In the room there is a " << r.monster.getName() << " ac: " << r.monster.getCR() << " hp: " << r.monster.getHP();
        return os;
    }
    // a room consists right now of a single monster    
    private:
        Monster monster;
};