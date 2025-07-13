#include "Player.h"
#include "Warrior.h"
#include "CharacterRole.h"

Warrior::Warrior(const std::string& role) : CharacterRole(role) {}

int Warrior::getMaxHP() const {
    return 150;
}

int Warrior::getCombatPower(const Player& player) const {
    return player.getForce() * 2 + player.getLevel();
}

int Warrior::handleEncounterEffect(Player& player, int combatPower, int loot, int damage) const {
    if (player.getCombatPower() > combatPower) {
        player.addLoot(loot);
        player.damage(10);
        player.levelUp();
        return 1;
    }else {
        player.damage(damage);
        return 0;
    }
}
