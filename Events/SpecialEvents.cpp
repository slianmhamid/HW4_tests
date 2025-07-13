
#include "SpecialEvents.h"

SpecialEvents::SpecialEvents(const string& name) : Event(name){}

string SpecialEvents::getDescription() const{
    return eventName;
}