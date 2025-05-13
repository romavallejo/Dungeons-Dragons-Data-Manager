#include "Dungeon.h"

//FUNCTION THAT LOADS FILE USING BUILT IN LOAD FILE FUNCTION FROM Graph.h
bool Dungeon::createDungeon(std::string fileName) {
    return dungeon.loadFile(fileName);
}

//FUNCTION THAT RETURNS SIZE FROM DUNGEON
unsigned int Dungeon::getSize() {
    return dungeon.getSize();
}

//FUNCTION THAT ADDS A NEW ROOM TO LINEAR DUNGEON
bool Dungeon::addRoom(unsigned int id, Monster mstr) {
    Room r(mstr);
    return dungeon.setVertexData(id, r);
}

//FUNCTION THAT DISPLAYS ROOMS
void Dungeon::displayRooms() {
    dungeon.display();
}

//FUNCTION THAT TRACES PATH FROM ONE VERTEX TO ANOTHER
bool Dungeon::tracePath(unsigned int start, unsigned int end) {
    if (dungeon.isEmpty())
        return false;
    if (path) {
        delete path;
        path = nullptr;
    }
    path = dungeon.breathFirstSearchPath(start, end);
    if (path->isEmpty()) {
        delete path;  
        return false;
    }
    i = path->begin();
    return true;
}

//FUNCTION THAT MOVES ITERATOR OF PATH
bool Dungeon::moveInPath() {
    ++i;
    return i != path->end();
}

//FUNCTIO NTHAT RETURNS THE ROOM IN CURRENT PATH
Room* Dungeon::currentRoomInPath() {
    return dungeon.getVertexData(*i);
}

void Dungeon::displayPath() {
    path->display();
}
