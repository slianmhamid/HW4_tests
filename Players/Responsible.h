#pragma once

#include "Player.h"
#include "CharacterType.h"

class Responsible : public CharacterType {
public:
    Responsible(const std::string& type);
    int applyPotionsMerchantEffect(Player& player) const override;
};