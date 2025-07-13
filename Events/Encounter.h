#pragma once
#include "Event.h"

#include <vector>
#include <memory>

using namespace std;

class Encounter : public Event {
protected:
    int encounterCombatPower;
    int encounterLoot;
    int encounterDamage;

public:
    Encounter(const string &name, int combatPower, int loot, int damage);

    int getLoot() const;

    int getDamage() const;

    int getCombatPower() const;

    string getDescription() const override;

    int applyEffect(Player &player) override;

    string eventEffectResult(Player &player, int effect) const override;
};

class Snail : public Encounter {
public:
    Snail();
};

class Slime : public Encounter {
public:
    Slime();
};

class Balrog : public Encounter {
public:
    Balrog();

    int applyEffect(Player &player) override;
};

class Pack : public Encounter {
    int packSize;
    int countBalrogs;
    std::vector<std::shared_ptr<Encounter> > pack;

public:
    Pack(vector<shared_ptr<Encounter> > encounters);

    string getDescription() const override;

    int applyEffect(Player &player) override;

    const vector<std::shared_ptr<Encounter> > &getEncounters() const;
};