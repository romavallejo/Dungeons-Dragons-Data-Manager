#include "Catalogue.h"

//FUNCTION THAT LOADS MONSTERS FROM CSV TO BINARY TREE
bool Catalogue::loadFromCSV(std::string fileName) {
    std::fstream file(fileName);
        if (!file.is_open())
            return false;
    std::string line, cell;
    if (!std::getline(file, line)) {} //skip header
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        int control = 0, num, error = 0;
        float numF;
        Monster tmp;
        while(std::getline(ss, cell, ',')) {
            control++;
            switch(control) {
                case 1:
                    if (cell.empty()) {
                        error++;
                        break;
                    }
                    tmp.setName(cell);
                    break;
                case 2:
                    if (!isValidFloat(cell)) {
                        error++;
                        break;
                    }
                    numF = stof(cell);
                    tmp.setCR(num);
                    break;
                case 3:
                    if (cell.empty()) {
                        error++;
                        break;
                    }
                    tmp.setType(cell);
                    break;
                case 4:
                    if (cell.empty()) {
                        error++;
                        break;
                    }
                    tmp.setSize(cell);
                    break;
                case 5:
                    if (!isValidInt(cell)) {
                        error++;
                        break;
                    }
                    num = stoi(cell);
                    tmp.setAC(num);
                    break;
                case 6:
                    if (!isValidInt(cell)) {
                        error++;
                        break;
                    }
                    num = stoi(cell);
                    tmp.setHP(num);
                    break;
                case 7:
                    if (cell.empty()) {
                        error++;
                        break;
                    }
                    tmp.setAlign(cell);
                    break;
            }
            if (error > 0) {
                return false;
            }
            monsterCatalogue.insert(tmp);
        }
    }
    return true;
}

//FUNCTION THAT RETURNS RANDOM MONSTER FROM CATALOGUE
Monster Catalogue::randomMonsterFromCatalogue() {
    return *monsterCatalogue.randomKey();
}

//FUNCTIONs THAT CHECK IF IT CAN BE CONVERTED TO NUM/FLOAT
bool Catalogue::isValidInt(std::string& str) {
    if (str.empty()) return false;
    for(int i = 0; i < str.length(); i++)
        if (!isdigit(str[i]))
            return false;
    return true;
}
bool Catalogue::isValidFloat(std::string& str) {
    if (str.empty()) return false;
    int dot = 0;
    if (isdigit(str[0]) || str[0] == '-')
        for(int i = 1; i < str.length(); i++)
            if (!isdigit(str[i])) {
                if (str[i] == '.')
                    dot++;
                else return false;
            }
    if (dot > 1)
        return false;
    return true;
}