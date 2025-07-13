#include "Player.h"
#include "RiskTaking.h"

RiskTaking::RiskTaking(const std::string& type) : CharacterType(type) {}

int RiskTaking::applyPotionsMerchantEffect(Player& player) const {

    if (player.getCoins() >= 5 && player.getHealthPoints() < 50) {
        player.setCoins(player.getCoins() - 5);
        player.heal(10);
        return 1;
    }
    return 0;
}
