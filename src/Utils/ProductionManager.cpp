#include "Utils/ProductionManager.h"

ProductionManager::ProductionManager(int arg_num_bottles, bool bot_map[NUM_BOTTLE_SLOTS]) : num_bottles(arg_num_bottles), 
                                                                                            num_bottles_remaining(0), 
                                                                                            cycles_remaining(0),
                                                                                            bottle_map{ bot_map[0],
                                                                                                        bot_map[1],
                                                                                                        bot_map[2],
                                                                                                        bot_map[3],
                                                                                                        bot_map[4],
                                                                                                        bot_map[5],
                                                                                                        bot_map[6],
                                                                                                        bot_map[7]} {

}

ProductionManager::~ProductionManager() {}

int ProductionManager::getCyclesRemaining() {
    return cycles_remaining;
}

void ProductionManager::flagCycleComplete(bool new_bottle_incoming) {
    advanceBottleMap(new_bottle_incoming);

    // If there was not a bottle in position 8 but now there is, decrement the bottles remaining counter
    // If there was a bottle in position 8 and there still is a bottle in position 8, decrement the remainder counter
    // If there is no bottle in position 8 do not decrement the remaining counter
    // TLDR: If there is a bottle in position 8 and there are still bottles to be done, decrement the remaining bottle counter
    if(num_bottles_remaining > 0 && getBottleMap(8)) {
        num_bottles_remaining--;
    }

    // If there are cycles remaining decrement cycle counter
    if(cycles_remaining > 0) {
        cycles_remaining--;
    }
}
int ProductionManager::getBottleMap(int position) {
    return bottle_map[position-1];
}

void ProductionManager::setBottleMap(bool new_bottle_map[8]) {
    for(int i = 0; i < NUM_BOTTLE_SLOTS; i++ ) {
        bottle_map[i] = new_bottle_map[i];
    }
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
    // For each slot in the array take slot - 1 and put it in slot
    // do this until slot 2
    // If new bottle, insert 1 in slot 1(arr0), else insert 0
    for(int i = NUM_BOTTLE_SLOTS-1; i > 0; i--) {
        bottle_map[i] = bottle_map[i-1];
    }
    if(with_new_bottle) {
        bottle_map[0] = 1;
    }
    else {
        bottle_map[0] = 0;
    }
}

int ProductionManager::emptySlots() {
    int count = 0;  // Initialise count variable
    
    for(int i = 0; i < NUM_BOTTLE_SLOTS; i++) {
        if(!bottle_map[i]){
            count++;
        }
    }

    return count;
}