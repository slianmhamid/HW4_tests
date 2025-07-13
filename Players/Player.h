#pragma once

#include <string>
#include <memory>

#include "CharacterRole.h"
#include "CharacterType.h"

using std::string;

class Player {
public:
    Player(const string& name,
          std::shared_ptr<CharacterRole> role,
          std::shared_ptr<CharacterType> type);

    virtual ~Player() = default;
    Player(const Player&) = default;
    Player& operator=(const Player& source) = default;

    string getName() const;
    int getLevel() const;
    int getForce() const;
    int getHealthPoints() const;
    int getMaxHP() const;
    int getCoins() const;
    string getDescription() const;

    string getRoleName() const;
    string getTypeName() const;
    std::shared_ptr<CharacterRole> getCharacterRole() const;
    std::shared_ptr<CharacterType> getCharacterType() const;

    int getCombatPower() const;
    void levelUp();
    void heal(int health);
    void damage(int damage);
    void addLoot(int loot);
    void setForce(int force);
    void setCoins(int coins);

    void setLifeStatus();
    bool canPlayerPlay() const;
    bool hasPlayerReachedMaxLevel() const;

    bool operator>(const Player& source) const;
    int handleEncounterEffect(int combatPower, int loot, int damage);

private:
    string playerName;
    int playerLevel;
    int playerForce;
    int playerCurrentHP;
    int playerMaxHP;
    int playerCoins;
    bool aliveOrDead;

    std::shared_ptr<CharacterRole> playerRole;
    std::shared_ptr<CharacterType> playerType;

};