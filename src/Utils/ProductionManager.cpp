#include "Utils/ProductionManager.h"

ProductionManager::ProductionManager(int arg_num_bottles, unsigned char arg_default_bottle_map) : num_bottles(arg_num_bottles), 
                                                                                                  num_bottles_remaining(0), 
                                                                                                  cycles_remaining(0),
                                                                                                  bottle_map(arg_default_bottle_map) {

}

ProductionManager::~ProductionManager() {}

/*
int getCyclesRemaining();
void flagCycleComplete();
unsigned char getBottleMap();
void setBottleMap(unsigned char new_bottle_map);
int getBottlesRemaining();
void setBottleNum(int arg_num_bottles);
void startProduction();
void startProduction();
*/

int ProductionManager::getCyclesRemaining() {
    return cycles_remaining;
}

void ProductionManager::flagCycleComplete(bool new_bottle_incoming) {
    advanceBottleMap(new_bottle_incoming);

    // If there was not a bottle in position 8 but now there is, decrement the bottles remaining counter
    // If there was a bottle in position 8 and there still is a bottle in position 8, decrement the remainder counter
    // If there is no bottle in position 8 do not decrement the remaining counter
    // TLDR: If there is a bottle in position 8 and there are still bottles to be done, decrement the remaining bottle counter
    if(num_bottles_remaining > 0 && (bottle_map & 0b00000001)) {
        num_bottles_remaining--;
    }

    // If there are cycles remaining decrement cycle counter
    if(cycles_remaining > 0) {
        cycles_remaining--;
    }
}

unsigned char ProductionManager::getBottleMap() {
    return bottle_map;
}

void ProductionManager::setBottleMap(unsigned char new_bottle_map) {
    bottle_map = new_bottle_map;
}

int ProductionManager::getBottlesRemaining() {
    return num_bottles_remaining;
}

void ProductionManager::setBottleNum(int arg_num_bottles) {
    if(arg_num_bottles != 0) {
        num_bottles = arg_num_bottles;
    }
}

void ProductionManager::stopProduction() {
    num_bottles_remaining = 0;
    cycles_remaining = 0;
}

void ProductionManager::startProduction() {
    num_bottles_remaining = num_bottles;
    if(num_bottles == -1) {
        cycles_remaining = -1;
    }
    else {
        cycles_remaining = num_bottles + emptySlots() - 1;
    }
}

void ProductionManager::advanceBottleMap(bool with_new_bottle) {
    if(with_new_bottle) {
        bottle_map = bottle_map >> 1 | 0b10000000;
    }
    else {
        bottle_map = bottle_map >> 1;
    }
}

int ProductionManager::emptySlots() {
    int count = 0;  // Initialise count variable
    unsigned char temp = bottle_map;    // create copy of bottle_map
    int i = 8;  // create iterator with starting value of 8
 
    // Iterate through all the bits
    while (i > 0) {
        // If current bit is 0
        if (~temp & 1) {
            count++;
        }

        // Shift the bits
        temp = temp >> 1;
        
        // Decrement the counter
        i--;
    }

    return count;
}