#pragma once
#include "Entity.h"
#include <iostream>

class Monster : public Entity{
public:
    // OVERLOADING OPERATORS TAKING NAME AS THE COMPARISON ATTRIBUTE FOR MONSTERS
    bool operator>(Monster& m) {
        return this->getName() < m.getName();
    }  
    bool operator<(Monster& m) {
        return this->getName() > m.getName();
    }
    bool operator==(Monster& m) {
        return this->getName() == m.getName();
    }
    bool operator<=(Monster& m) {
        return this->getName() <= m.getName();
    }
    friend std::ostream& operator<<(std::ostream& os, Monster& m) {
        os << m.getName();
        return os;
    }
};