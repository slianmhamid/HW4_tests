#pragma once

#include <string>

class Player;

class CharacterType {
public:
    CharacterType(const std::string& typeName) : type(typeName) {}
    virtual ~CharacterType() = default;

    std::string getTypeName() const {
        return type;
    }
    virtual int applyPotionsMerchantEffect(Player& player) const = 0;

private:
    std::string type;
};
