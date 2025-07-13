#pragma once

#include "CharacterRole.h"

class  Magician : public CharacterRole {
public:
    Magician(const std::string& role);
    virtual ~Magician() = default;

    int applySolarEclipseEffect(Player& player) override;
};
