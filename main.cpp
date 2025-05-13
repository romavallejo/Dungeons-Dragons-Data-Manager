/*Rodrigo Martínez Vallejo A00573055*/
#include <iostream>
#include <string>
#include <ctime>
#include "Dungeon.h"
#include "Catalogue.h"

using namespace std;

int main() {
    Dungeon   dng;
    Catalogue catalogue;
    unsigned int start, end;
    srand(time(0));

    //LOADING OF CSV INTO CATALOGUE
    string file = "monsters.csv";
    if (!catalogue.loadFromCSV(file)) {
        cout << "Error in the cration of the catalogue" << endl; 
        return 0;
    } 

    //READS GRAPH TO CREATE DUNGEON
    cout << "***Creating dungeon***" << endl;
    if (!dng.createDungeon("dungeon.txt")) {
        cout << "Error in the creation of the dugeon" << endl;
        return 0;
    }

    //FILLS DUNGEON WITH MONSTERS
    for (unsigned int i = 0; i < dng.getSize(); i++) {
        if (!dng.addRoom(i, catalogue.randomMonsterFromCatalogue())) {
            cout << "Something when terribly wrong when creating a room... I suggest running" << i+1 << endl;
            return 0;
        }
    }

    //DISPLAYING ROOMS
    cout << "¿What hides in the rooms?" << endl;
    dng.displayRooms();
    
    //ASKING PLAYER TO CHOSE A START ROOM AND DESTINATION
    cout << "\nThe time has come for you to choose a path..." << endl;
    do {
        cout << "¿Where will your adventre start? ";
        cin >> start;
        cout << "¿Where will it end? ";
        cin >> end;
    } while (end > dng.getSize() || start > dng.getSize() || start == end );
    
    
    //CREATING THE PATH
    if(!dng.tracePath(start, end)) {
        cout << "There is no path that will take you from " << start << " to " << end << endl;
        return 0;
    }
    
    
    //DISPLAYING PATH
    dng.displayPath();
    do {
        switch(rand() % 10) {
            case 0:
                cout << "--> You step into a shadowy room cloaked in layers of dust. The faint glow of moonlight reveals writing etched into the grime. In the room, there is a " << *dng.currentRoomInPath() << endl;
                break;
            case 1:
                cout << "--> Entering a dimly lit room, the air feels heavy with age, and a fine layer of dust coats every surface. Amid the gloom, faint writing glimmers faintly. In the room, there is a " << *dng.currentRoomInPath() << endl;
                break;
            case 2:
                cout << "--> As you step into the room, a cloud of dust rises, swirling in the dim, stale air. Shadows loom large, and faint inscriptions on the walls catch your eye. In the room, there is a" << *dng.currentRoomInPath() << endl;
                break;
            case 3:
                cout << "--> The room is shrouded in an eerie stillness, dust clinging to every corner. Through the overwhelming darkness, faint markings emerge on the walls. In the room, there is a " << *dng.currentRoomInPath() << endl;
                break;
            case 4:
                cout << "--> You cross the threshold into a forsaken room, the weight of years past hanging in the dust-filled air. The oppressive dark swallows most of the space, but faint letters glimmer in the shadows. In the room, there is a " << *dng.currentRoomInPath() << endl;
                break;
            case 5:
                cout << "--> The air grows colder as you enter the room, the floor creaking beneath your weight. Dust motes dance in the faint light, revealing faded symbols on the walls. In the room, there is a " << *dng.currentRoomInPath() << endl;
                break;
            case 6:
                cout << "--> You push open a heavy door, and the smell of mildew fills your senses. The dim light barely reaches the far corners, where shadows seem to move. In the room, there is a " << *dng.currentRoomInPath() << endl;
                break;
            case 7:
                cout << "--> The room feels alive with a quiet tension, as if the walls themselves are watching. Layers of dust cover the floor, and broken furniture lies scattered. In the room, there is a " << *dng.currentRoomInPath() << endl;
                break;
            case 8:
                cout << "--> A low hum fills the air as you enter, the faint light casting distorted reflections on cracked mirrors along the walls. In the room, there is a " << *dng.currentRoomInPath() << endl;
                break;
            case 9:
                cout << "--> The room is cloaked in utter silence, broken only by the faint sound of dripping water. The darkness is oppressive, but you can just make out faint claw marks etched into the floor. In the room, there is a " << *dng.currentRoomInPath() << endl;
                break;
        }
        
    } while (dng.moveInPath());

    return 0;
}