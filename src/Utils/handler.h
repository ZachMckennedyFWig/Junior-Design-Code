#ifndef HANDLER_H
#define HANDLER_H

class SubsysHandler
{
private:
    /* data */
public:
    SubsysHandler();
    ~SubsysHandler();

    template<typename... Subsystems>
    void update(Subsystems&... subsystems);

    template<typename... Subsystems>
    bool ops_complete(Subsystems&... subsystems);

    template<typename... Subsystems>
    void activate(Subsystems&... subsystems);
};

SubsysHandler::SubsysHandler(){}

SubsysHandler::~SubsysHandler(){}

// Define a variadic template function that takes any number of subsystem objects and updates them
template<typename... Subsystems>
void SubsysHandler::update(Subsystems&... subsystems) {
  // Use a fold expression to execute the update method on each subsystem
  (subsystems.update(), ...);
}

// Define a variadic template function that takes any number of subsystem objects and updates them
template<typename... Subsystems>
bool SubsysHandler::ops_complete(Subsystems&... subsystems) {
  // Use a fold expression to execute the update method on each subsystem
  return (subsystems.completed && ...);
}

template<typename... Subsystems>
void SubsysHandler::activate(Subsystems&... subsystems) {
  // Use a fold expression to execute the update method on each subsystem
  (subsystems.action(), ...);
}

#endif