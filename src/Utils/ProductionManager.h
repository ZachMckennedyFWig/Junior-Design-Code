#ifndef PRODUCTION_MANAGER_H
#define PRODUCTION_MANAGER_H

class ProductionManager
{
private:
    int num_bottles;
    int num_bottles_remaining;
    int cycles_remaining;

    /**
     * bottle_map is an unsigned char whose bits corresponde to the presense of a bottle at each of the 8 positions around the machine
     * The stations are represented using the binary bits starting with the bottle handler at the MOST signifigant bit
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
     * binary Representation: 0b 0 0 0 0 0 0 0 0
     *              Stations:    1 2 3 4 5 6 7 8
     *
     * Ex: Bottles at the bottle handler and the pill filler would be 0b10100000
    */
    unsigned char bottle_map; 

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
    ProductionManager(int arg_num_bottles, unsigned char arg_default_bottle_map);

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
     * @return unsigned char containing bottle map
    */ 
    unsigned char getBottleMap();

    /**
     * @brief Method to set a new Bottle map (At startup for example)
     * @return Nothing
    */ 
    void setBottleMap(unsigned char new_bottle_map);

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