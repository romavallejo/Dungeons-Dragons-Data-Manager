#pragma once
#include <iostream>
#include <string>
#include "Graph.h"
#include "Monster.h"
#include "Room.h"
#include "DobleLinkedList.h"

class Dungeon {
public:
    //DESTRUCTOR THAT ENSURES THAT PATH IS DELETED IF IT EXISTS
    ~Dungeon() {
        if (path) {
            delete path;
            path = nullptr;
        }
    }
    unsigned int getSize();
    bool createDungeon(std::string fileName);
    bool addRoom(unsigned int id, Monster mstr); 
    void displayRooms(); 

    bool tracePath(unsigned int start, unsigned int end);
    bool moveInPath();
    Room* currentRoomInPath();
    void displayPath();
private: 
    Graph<Room> dungeon;
    
    DobleLinkedList<unsigned int>* path = nullptr;
    DobleLinkedList<unsigned int>::iterator i = nullptr;
};