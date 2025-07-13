#pragma once

#include "CharacterRole.h"

class Warrior : public CharacterRole {
public:
    Warrior(const std::string& role);
    virtual ~Warrior() = default;

    int getMaxHP() const override;
    int getCombatPower(const Player& player) const override;
    int handleEncounterEffect(Player& player, int combatPower, int loot, int damage) const override;
};