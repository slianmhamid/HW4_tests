#include "Player.h"
#include "CharacterRole.h"

CharacterRole::CharacterRole(const std::string& roleName) : role(roleName){}

std::string CharacterRole::getRoleName() const {
    return role;
}

int CharacterRole::getMaxHP() const {
    return 10;
}

int CharacterRole::getCoins() const {
    return 100;
}

int CharacterRole::getCombatPower(const Player& player) const {
    return player.getForce() + player.getLevel();
}

int CharacterRole::applySolarEclipseEffect(Player& player) {
    if (player.getForce() > 0) {
        player.setForce(player.getForce() - 1);
        return -1;
    }
    return 0;
}

int CharacterRole::handleEncounterEffect(Player& player, int combatPower, int loot, int damage) const {
    if (player.getCombatPower() > combatPower) {
        player.addLoot(loot);
        player.levelUp();
        return 1;
    }else {
        player.damage(damage);
        return 0;
    }
}