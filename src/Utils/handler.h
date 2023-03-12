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
    bool isComplete(Subsystems&... subsystems);

    template<typename... Subsystems>
    void trigger(Subsystems&... subsystems);

    template<typename... Subsystems>
    bool init(Subsystems&... subsystems);
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
bool SubsysHandler::isComplete(Subsystems&... subsystems) {
  // Use a fold expression to execute the update method on each subsystem
  return (subsystems.isComplete() && ...);
}

template<typename... Subsystems>
void SubsysHandler::trigger(Subsystems&... subsystems) {
  // Use a fold expression to execute the update method on each subsystem
  (subsystems.trigger(), ...);
}

// Define a variadic template function that takes any number of subsystem objects and updates them
template<typename... Subsystems>
bool SubsysHandler::init(Subsystems&... subsystems) {
  // Use a fold expression to execute the update method on each subsystem
  return (subsystems.init() && ...);
}


#endif