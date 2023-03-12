#ifndef HANDLER_RECURSE_H
#define HANDLER_RECURSE_H

class SubsysHandler {
public:
    SubsysHandler();
    ~SubsysHandler();

    // Update templates
    void update();

    template<typename Subsystem>
    void update(Subsystem& subsystem); // The key here is to pass by reference

    template<typename First, typename... Subsystem>
    void update(First& first_sub, Subsystem&... subsystems); // Again very important to pass by reference

    // Check Complete Templates
    void isComplete();

    template<typename Subsystem>
    bool isComplete(Subsystem& subsystem);

    template<typename First, typename... Subsystem>
    bool isComplete(First& first_sub, Subsystem&... subsystems);

    //Trigger Templates
    void trigger();

    template<typename Subsystem>
    void trigger(Subsystem& subsystem); 

    template<typename First, typename... Subsystem>
    void trigger(First& first_sub, Subsystem&... subsystems); 

    //Init Templates
    bool init();

    template<typename Subsystem>
    bool init(Subsystem& subsystem); 

    template<typename First, typename... Subsystem>
    bool init(First& first_sub, Subsystem&... subsystems); 
};

SubsysHandler::SubsysHandler(){}

SubsysHandler::~SubsysHandler(){}

void SubsysHandler::update() {} // do nothing if the function is called w/o arguments

template<typename Subsystem>
void SubsysHandler::update(Subsystem& subsystem) {
  subsystem.update();   // update the passed subsystem
}

template<typename First, typename... Subsystem>
void SubsysHandler::update(First& first_sub, Subsystem&... subsystems) {
  update(first_sub);      // call single argument overload on first subststem
  update(subsystems...);  // unpack rest of variable pack, figuring out how 
}

void SubsysHandler::isComplete() {}

template<typename Subsystem>
bool SubsysHandler::isComplete(Subsystem& subsystem) {
  return subsystem.completed;
}

template<typename First, typename... Subsystem>
bool SubsysHandler::isComplete(First& first_sub, Subsystem&... subsystems) {
  bool complete = true;
  complete = complete && isComplete(first_sub);
  complete = complete && isComplete(subsystems...);
  return complete;
}

void SubsysHandler::trigger() {}

template<typename Subsystem>
void SubsysHandler::trigger(Subsystem& subsystem) {
  subsystem.trigger();
}

template<typename First, typename... Subsystem>
void SubsysHandler::trigger(First& first_sub, Subsystem&... subsystems) {
  trigger(first_sub);
  trigger(subsystems...);
}

bool SubsysHandler::init() {}

template<typename Subsystem>
bool SubsysHandler::init(Subsystem& subsystem) {
  return subsystem.init();
}

template<typename First, typename... Subsystem>
bool SubsysHandler::init(First& first_sub, Subsystem&... subsystems) {
  bool success = true;
  success = success && init(first_sub);
  success = success && init(subsystems...);
  return success;
}

#endif