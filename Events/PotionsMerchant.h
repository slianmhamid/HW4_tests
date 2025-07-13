#pragma once
#include "SpecialEvents.h"

class PotionsMerchant: public SpecialEvents{
public:
    PotionsMerchant();
    int applyEffect(Player &player) override;
    string eventEffectResult(Player &player,int effect) const override;
};

PotionsMerchant::PotionsMerchant():SpecialEvents("PotionsMerchant") {}

int PotionsMerchant::applyEffect(Player &player){
    return player.getCharacterType()->applyPotionsMerchantEffect(player);
}

string PotionsMerchant::eventEffectResult(Player &player,int effect) const{
    return getPotionsPurchaseMessage(player,effect);
}