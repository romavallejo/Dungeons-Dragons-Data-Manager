#pragma once
#include "BinaryTree.h"
#include "Monster.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

class Catalogue {
public:
    bool loadFromCSV(std::string file); 
    bool catalogueIsEmpty() {
        return monsterCatalogue.isEmpty();
    }
    Monster randomMonsterFromCatalogue(); 
private:
    BinaryTree<Monster> monsterCatalogue;
    
    bool isValidInt(std::string& str);
    bool isValidFloat(std::string& str);
};