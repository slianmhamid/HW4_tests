
#pragma once
#include "../Players/Player.h"

#include <string>
using std::string;

class Event {
protected:
    std::string eventName;
public:
    /**
     * Gets the description of the event
     *
     * @return - the description of the event
    */
    virtual string getDescription() const = 0;
    Event(const string &name):eventName(name){}
    virtual ~Event() = default;
    virtual int applyEffect(Player &player) = 0;
    virtual string eventEffectResult(Player &player,int effect) const = 0;
    string getEventName() const{
        return eventName;
    }
};