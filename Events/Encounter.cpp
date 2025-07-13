#include "Encounter.h"
#include "Utilities.h"

#include <string>
using std::string;

Encounter::Encounter(const string &name,int encounterCombatPower,
    int encounterLoot,int encounterDamage):Event(name),
    encounterCombatPower(encounterCombatPower),encounterLoot(encounterLoot),
    encounterDamage(encounterDamage){}

int Encounter::getCombatPower() const {
    return encounterCombatPower;
}

int Encounter::getLoot() const {
    return encounterLoot;
}

int Encounter::getDamage() const {
    return encounterDamage;
}

string Encounter::getDescription() const {
    return eventName + " (power " + to_string(encounterCombatPower) + ", loot " +
        to_string(encounterLoot) + ", damage " + to_string(encounterDamage)+")";
}

Snail::Snail():Encounter("Snail",5,2,10){}

Slime::Slime():Encounter("Slime",12,5,25){}

Balrog::Balrog():Encounter("Balrog",15,100,9001){}

int Balrog::applyEffect(Player &player){
    int effect = player.handleEncounterEffect(encounterCombatPower,encounterLoot,encounterDamage);
    encounterCombatPower+=2;
    if (effect == 0) {
        return 1;
    }
    return 0;
}

Pack::Pack(std::vector<std::shared_ptr<Encounter>> encounters)
: Encounter("Pack", 0, 0, 0),
  packSize(0),countBalrogs(0),pack(std::move(encounters)) {
    for (auto cit = this->pack.cbegin(); cit != this->pack.cend(); ++cit) {
        encounterCombatPower += (*cit)->getCombatPower();
        encounterDamage += (*cit)->getDamage();
        encounterLoot += (*cit)->getLoot();
        packSize++;
        if ((*cit)->getEventName() == "Balrog") {
            countBalrogs++;
        }
    }
}

string Pack::getDescription() const {
    return "Pack of "+std::to_string(packSize) +" members (power " +
        std::to_string(encounterCombatPower) +", loot "+
        std::to_string(encounterLoot) +", damage "+std::to_string(encounterDamage)+")";
}

int Encounter::applyEffect(Player &player) {
    int effect = player.handleEncounterEffect(encounterCombatPower,encounterLoot,encounterDamage);
    if (effect == 0) {
        return 1;
    }
    return 0;
}

string Encounter::eventEffectResult(Player &player,int effect) const {
    if(effect == 0){
        return getEncounterWonMessage(player,this->encounterDamage);
    }

    return getEncounterLostMessage(player, this->encounterLoot);
}

int Pack::applyEffect(Player &player) {
    int effect = player.handleEncounterEffect(encounterCombatPower,encounterLoot,encounterDamage);
    encounterCombatPower += (2 * countBalrogs);
    if (effect == 0) {
        return 1;
    }
    return 0;
}

const std::vector<std::shared_ptr<Encounter>>& Pack::getEncounters() const {
    return pack;
}