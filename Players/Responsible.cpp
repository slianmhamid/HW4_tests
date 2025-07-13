#include "Player.h"
#include "Responsible.h"

Responsible::Responsible(const std::string& type) : CharacterType(type) {}

int Responsible::applyPotionsMerchantEffect(Player& player) const {
    int potionCounter = 0;

    while (player.getCoins() >= 5 && player.getHealthPoints() < player.getMaxHP()) {
        player.setCoins(player.getCoins() - 5);
        player.heal(10);
        potionCounter++;
    }
    return potionCounter;
}