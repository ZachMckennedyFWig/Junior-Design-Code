#include "Peripherals/EventButton.h"

void EventButton::init() {
    bouncer.attach(pin, input_mode);
    bouncer.interval(5);
    bouncer.setPressedState(pressed_state);
}

void EventButton::update() {
    bouncer.update();

    if(long_press_time_ms) {
        if(bouncer.released() && bouncer.previousDuration() < long_press_time_ms) {
            click_clbk();
        }

        if(bouncer.isPressed() && bouncer.currentDuration() > long_press_time_ms) {
            long_press_clbk();
        }
    }
    else {
        if(bouncer.pressed()) {
            press_clbk();
        }
    }  
}

void EventButton::reg_click_clbk(f_void_void arg_click_clbk) {
    click_clbk = arg_click_clbk;
}

void EventButton::reg_press_clbk(f_void_void arg_press_clbk) {
    press_clbk = arg_press_clbk;
}

void EventButton::reg_long_press_clbk(f_void_void arg_long_press_clbk) {
    long_press_clbk = arg_long_press_clbk;
}