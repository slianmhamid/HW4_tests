#pragma once
#include "Event.h"
#include "Utilities.h"


class SpecialEvents : public Event{
public:
    SpecialEvents(const string& name);
    string getDescription() const override;
    virtual ~SpecialEvents() = default;
};