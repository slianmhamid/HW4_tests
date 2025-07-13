#pragma once

#include "CharacterRole.h"

class Archer : public CharacterRole {
public:
    Archer(const std::string& role);
    virtual ~Archer() = default;

    int getCoins() const override;

};
