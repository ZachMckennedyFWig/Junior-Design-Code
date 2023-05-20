#ifndef EVENT_BUTTON_H
#define EVENT_BUTTON_H

#include <Bounce2.h>
#include <Arduino.h>

using f_void_void = void(*)();

class EventButton{
    private:
        // Callbacks, the []() {} is Arcane magic with lambda functions to make an empty function that does nothing
        f_void_void click_clbk = []() {};
        f_void_void press_clbk = []() {};
        f_void_void long_press_clbk = []() {};

        int pin;
        int input_mode;
        int pressed_state;
        unsigned int long_press_time_ms; // time to detect a long press in milliseconds

        Bounce2::Button bouncer = Bounce2::Button();
        
    public:

        static const int NO_LONG_PRESS = 0;

        /**
         * @brief Class constructor
         * @param arg_pin the pin the button is connected to
         * @param arg_input_mode valid arduino input pinmode (INPUT, INPUT_PULLUP)
         * @param arg_pressed_state valid arduino pin state that the button gives when pressed (LOW, HIGH)
         * @param arg_long_press_time time in milliseconds that a long press takes to register. Set to NO_LONG_PRESS to turn off long press and click and enable the press callback)
        */
        EventButton(int arg_pin, int arg_input_mode, int arg_pressed_state, unsigned int arg_long_press_time) : pin(arg_pin), 
                                                                                                       input_mode(arg_input_mode), 
                                                                                                       pressed_state(arg_pressed_state),
                                                                                                       long_press_time_ms(arg_long_press_time) {}

        /**
         * @brief Initializer method for the button, call in setup
        */
        void init();

        /**
         * @brief Update method for the button, call as often as possible
        */
        void update(); 

        /**
         * @brief Register callback for a click event (called when the button is released)
        */
        void reg_click_clbk(f_void_void arg_click_clbk);

        /**
         * @brief Register callback for a press event (called when the button is pressed)
        */
        void reg_press_clbk(f_void_void arg_press_clbk);

        /**
         * @brief Register callback for a long press event 
         *        (called when the button is pressed for longer than long_press_time_s)
        */
        void reg_long_press_clbk(f_void_void arg_long_press_clbk);
};

#endif