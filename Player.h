#pragma once
#include "DobleLinkedList.h"
#include "Monster.H"
#include "Entity.h"

class Player : public Entity{
public:
    bool addDefeatedMonster(Monster mstr); 
    void displayDefeatedMonsters();
private:
    DobleLinkedList<Monster> defeatedMonsters;
};