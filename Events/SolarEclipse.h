#pragma once
#include "SpecialEvents.h"

class SolarEclipse : public SpecialEvents{
public:
    SolarEclipse() ;
    int applyEffect(Player &player) override;
    string eventEffectResult(Player &player,int effect) const override;
};

SolarEclipse::SolarEclipse():SpecialEvents("SolarEclipse") {}

int SolarEclipse::applyEffect(Player &player){
    return player.getCharacterRole()->applySolarEclipseEffect(player);
}

string SolarEclipse::eventEffectResult(Player &player,int effect) const{
    return getSolarEclipseMessage(player,effect);
}