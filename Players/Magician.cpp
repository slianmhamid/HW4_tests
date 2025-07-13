#include "Player.h"
#include "Magician.h"
#include "CharacterRole.h"

Magician::Magician(const std::string& role) : CharacterRole(role) {}

int Magician::applySolarEclipseEffect(Player& player) {
    player.setForce(player.getForce() + 1);
    return 1;
}
