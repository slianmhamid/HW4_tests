#pragma once

#include <string>

class Player;

class CharacterRole {
public:
    CharacterRole(const std::string& roleName);
    virtual ~CharacterRole() = default;

    virtual std::string getRoleName() const;

    virtual int getMaxHP() const;
    virtual int getCoins() const;

    virtual int applySolarEclipseEffect(Player& player);
    virtual int getCombatPower(const Player& player) const;
    virtual int handleEncounterEffect(Player& player, int combatPower, int loot, int damage) const;
private:
    std::string role;
};
