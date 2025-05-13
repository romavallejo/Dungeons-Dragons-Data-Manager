#pragma once
#include <string>

class Entity {
public:
        // HELPER FUNCTIONS
    std::string getName() {
        return name;
    }
    void setName(std::string el) {
        name = el;
    }
    float getCR () {
        return cr;
    }
    void setCR(float el) {
        cr = el;
    }
    std::string getType() {
        return type;
    }
    void setType(std::string el) {
        type = el;
    }
    std::string getSize() {
        return size;
    }
    void setSize(std::string el) {
        size = el; 
    }
    int getAC() {
        return ac;
    }
    void setAC(int el) {
        ac = el;
    }
    int getHP() {
        return hp;
    }
    void setHP(int el) {
        hp = el;
    }
    std::string getAlign() {
        return align;
    }
    void setAlign(std::string el) {
        align = el;
    }
private:
    std::string name, type, size, align;
    float cr;
    int ac, hp;
};