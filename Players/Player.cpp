#include "Player.h"
#include <algorithm>

static const int MAX_LEVEL = 10;

Player::Player(const string& name,
      std::shared_ptr<CharacterRole> role,
      std::shared_ptr<CharacterType> type) :
      playerName(name),
      playerLevel(1),
      playerForce(5),
      playerCurrentHP(role->getMaxHP()),
      playerMaxHP(role->getMaxHP()),
      playerCoins(role->getCoins()),
      aliveOrDead(true),
      playerRole(std::move (role)),
      playerType(std::move (type)) {}

string Player::getName() const {
      return playerName;
}
int Player::getLevel() const {
      return playerLevel;
}
int Player::getForce() const {
      return playerForce;
}
int Player::getHealthPoints() const {
      return playerCurrentHP;
}
int Player::getMaxHP() const {
      return playerMaxHP;
}
int Player::getCoins() const {
      return playerCoins;
}
string Player::getDescription() const {
      return playerName + ", " + getRoleName() +
            " with " + getTypeName() + " character" +
            " (level" + std:: to_string(playerLevel) +
            ", force" + std::to_string(playerForce) + ")";
}


string Player::getRoleName() const {
      return playerRole->getRoleName();
}
string Player::getTypeName() const {
      return playerType->getTypeName();
}
std::shared_ptr<CharacterRole> Player::getCharacterRole() const {
      return playerRole;
}
std::shared_ptr<CharacterType> Player::getCharacterType() const {
      return playerType;
}


int Player::getCombatPower() const {
      return playerRole->getCombatPower(*this);
}
void Player::levelUp() {
      playerLevel++;
}
void Player::heal(int health) {
      playerCurrentHP = std::min(playerCurrentHP + health, playerMaxHP);
}
void Player::damage(int damage) {
      playerCurrentHP = std::max(0, playerCurrentHP - damage);
}
void Player::addLoot(int loot) {
      playerCoins += loot;
}
void Player::setForce(int force) {
      playerForce = force;
}
void Player::setCoins(int coins) {
      playerCoins = coins;
}


bool Player::canPlayerPlay() const {
      return aliveOrDead;
}
void Player::setLifeStatus() {
      aliveOrDead = false;
}
bool Player::hasPlayerReachedMaxLevel() const {
      return playerLevel == MAX_LEVEL;
}


bool Player::operator>(const Player& source) const {
      if (playerLevel != source.playerLevel) {
            return playerLevel > source.playerLevel;
      }
      if (playerCoins != source.playerCoins) {
            return playerCoins > source.playerCoins;
      }
      return playerName < source.playerName;
}

int Player::handleEncounterEffect(int combatPower, int loot, int damage) {
      return playerRole->handleEncounterEffect(*this, combatPower, loot, damage);
}
