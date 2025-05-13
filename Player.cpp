#include "Player.h"

//FUNCTION THAT ADDS A MONSTER TO DELEATED MONSTERS LIST
bool Player::addDefeatedMonster(Monster mstr) {
    return defeatedMonsters.addInOrder(mstr);
}

//FUNCTION THAT DSIPLAYS MONSTERS IN DEFEATED MONSTERS
void Player::displayDefeatedMonsters() {
    defeatedMonsters.display();
}