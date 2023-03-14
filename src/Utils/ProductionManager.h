#ifndef PRODUCTION_MANAGER_H
#define PRODUCTION_MANAGER_H

#define NUM_BOTTLE_SLOTS 8

class ProductionManager
{
private:
    int num_bottles;
    int num_bottles_remaining;
    int cycles_remaining;

    /**
     * bottle_map is an 8 index booleen array whose contents correspond to the presense of a bottle at each of the 8 positions around the machine
     * The stations are represented using the array positions starting with the bottle handler at index 0
     * 
     * ============ Station Map ============
     *          (As seen from top)
     * 
     *                  4 
     *     Pill ---> 3      5 <--- Capper
     *             2          6    
     *   Bottle ---> 1      7 <--- Closer
     *                  8
     * 
     * Array Index: 0 1 2 3 4 5 6 7 
     *    Stations: 1 2 3 4 5 6 7 8
     *
     * Ex: Bottles at the bottle handler and the pill filler would be [1,0,1,0,0,0,0,0]
    */
    bool bottle_map[8]; 

    /**
     * @brief method to advance the bottle map
    */ 
    void advanceBottleMap(bool with_new_bottle = true);

    /**
     * @brief method to count the number of empty slots in the rotary table
     * @returns the number of empty slots
    */
    int emptySlots();

public:
    /**
     * @brief Class constructor
    */ 
    ProductionManager(int arg_num_bottles, bool bot_map[NUM_BOTTLE_SLOTS]);

    /**
     * @brief Class destructor
    */ 
    ~ProductionManager();


    /**
     * @brief Method to get the remaining cycles in the production run
     * @return int number of cycles or -1 for infinite
    */ 
    int getCyclesRemaining();

    /**
     * @brief Method to let the manager know that a cycle has completed
     * @return Nothing
    */ 
    void flagCycleComplete(bool new_bottle_incoming = true);

    /**
     * @brief Method to get a the current bottle_map
     * @param position what position you would like to recieve info about (1 to 8)
     * @return int containing status of the bottle map at that positon
    */ 
    int getBottleMap(int position);

    /**
     * @brief Method to set a new Bottle map (At startup for example)
     * @param new_bottle_map an 8 element bool array of the desired bottle map
     * @return Nothing
    */ 
    void setBottleMap(bool new_bottle_map[8]);

    /**
     * @brief method get the remaining number of bottles in this production cycle
     * @return int number of bottles or -1 for infinite
    */ 
    int getBottlesRemaining();
    
     /**
     * @brief method set the number of bottles to produce in a production cycle
     * (won't update until the current production cycle stops and a new one starts)
     * @param arg_num_bottles the new number of bottles
     * @returns Nothing
    */ 
    void setBottleNum(int arg_num_bottles);

    /**
     * @brief method to start production (starts the machine and spits out num_bottles)
     * @return Nothing
    */ 
    void startProduction();

    /**
     * @brief method to stop production (stops after the current cycle)
     * @return Nothing
    */ 
    void stopProduction();

};






#endif