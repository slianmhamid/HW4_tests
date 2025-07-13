#include "Archer.h"
#include "CharacterRole.h"

Archer::Archer(const std::string& role) : CharacterRole(role) {}

int Archer::getCoins() const {
    return 20;
}
