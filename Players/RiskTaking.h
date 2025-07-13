#pragma once

#include "Player.h"
#include "CharacterType.h"

class RiskTaking : public CharacterType {
public:
    RiskTaking(const string& type);
    int applyPotionsMerchantEffect(Player& player) const override;
};