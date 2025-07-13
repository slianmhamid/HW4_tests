#include <iostream>
#include <fstream>
#include <string>

#include "MatamStory.h"

#include "Events/Encounter.h"
#include "Events/SolarEclipse.h"
#include "Events/PotionsMerchant.h"

#include "Players/Archer.h"
#include "Players/Warrior.h"
#include "Players/Magician.h"
#include "Players/RiskTaking.h"
#include "Players/Responsible.h"


static const int MIN_LEN_NAME = 3;
static const int MAX_LEN_NAME = 15;
static const int MIN_NUM_PLAYERS = 2;
static const int MAX_NUM_PLAYERS = 6;


MatamStory::MatamStory(std::istream& eventsStream, std::istream& playersStream) {
      std::deque<std::string> temp;
      dequeFromStream(eventsStream,temp);

      /*===== Open and read events file =====*/

      getEventsReady(temp);

      /*===== Open and Read players file =====*/

      getPlayersReady(playersStream);

      gameWinner = nullptr;
      this->m_turnIndex = 1;
}

void MatamStory::getPlayersReady(std::istream& playersStream) {
      shared_ptr<CharacterRole> role;
      shared_ptr<CharacterType> type;
      string playerName, playerRole, playerType;

      while (playersStream >> playerName) {
            if (playerName.length() < MIN_LEN_NAME || playerName.length() > MAX_LEN_NAME) {
                  throw std::runtime_error("Invalid Players File");
            }
            if (!areLettersApartOfTheAlphabet(playerName)) {
                  throw std::runtime_error("Invalid Players File");
            }
            if (!(playersStream >> playerRole >> playerType)) {
                  throw std::runtime_error("Invalid Players File");
            }
            try {
                  role = std::move(getCharacterRoleReady(playerRole));
                  type = std::move(getCharacterTypeReady(playerType));
                  players.push_back(std::make_shared<Player>(Player(playerName, role, type)));

            }catch (...) {
                  throw std::runtime_error("Invalid Players File");
            }

            if (players.size() < MIN_NUM_PLAYERS || players.size() > MAX_NUM_PLAYERS) {
                  throw std::runtime_error("Invalid Players File");
            }
      }
}

shared_ptr<CharacterRole> MatamStory::getCharacterRoleReady(const string& role) {
      if (role == "Warrior") {
            return std::make_shared<Warrior>(Warrior(role));
      }else if (role == "Archer") {
            return std::make_shared<Archer>(Archer(role));
      }else if (role == "Magician") {
            return std::make_shared<Magician>(Magician(role));
      }else {
            throw std::runtime_error("Invalid Players File");
      }
}

shared_ptr<CharacterType> MatamStory::getCharacterTypeReady(const string& type) {
      if (type == "Responsible") {
            return std::make_shared<Responsible>(Responsible(type));
      }else if (type == "RiskTaking") {
            return std::make_shared<RiskTaking>(RiskTaking(type));
      }else {
            throw std::runtime_error("Invalid Players File");
      }
}

void MatamStory::getEventsReady(std::deque<string> &strings) {
      for(int index = 0; index < static_cast<int>(strings.size()); ++index){
            if(strings[index] != "Pack"){
                  events.push_back(getNonPackReady(strings[index]));
            } else{
                  events.push_back(getPackReady(strings,index));
                  index--;
            }
      }
      if (events.size() < 2) {
            throw std::runtime_error("Invalid Events File");
      }
}
std::shared_ptr<Encounter> MatamStory::getEncounterReady(const std::string& event) {
      if (event == "Snail") {
            return std::make_shared<Snail>();
      }
      if (event == "Slime") {
            return std::make_shared<Slime>();
      }
      if (event == "Balrog") {
            return std::make_shared<Balrog>();
      }
      throw std::runtime_error("Invalid Events File");
}

void MatamStory::dequeFromStream(std::istream& stream, std::deque<std::string>& deque) {
      std::string word;
      while (stream >> word) {
            deque.push_back(word);
      }
}

shared_ptr<Event> MatamStory::getNonPackReady(const string& event) {
      if(event == "Snail"){
            return std::make_shared<Snail>(Snail());
      }
      if(event == "Slime"){
            return std::make_shared<Slime>(Slime());
      }
      if(event == "Balrog"){
            return std::make_shared<Balrog>(Balrog());
      }
      if(event == "SolarEclipse"){
            return std::make_shared<SolarEclipse>(SolarEclipse());
      }
      if(event == "PotionsMerchant"){
            return std::make_shared<PotionsMerchant>(PotionsMerchant());
      }
      throw std::runtime_error("Invalid Events File");
}

shared_ptr<Pack> MatamStory::getPackReady(const std::deque<std::string>& deque,int& index) {

      const std::string &eventString = deque[index + 1];

      for (char letter : eventString) {
            if (letter == '.') {
                  throw std::runtime_error("Invalid Events File");
            }
      }

      unsigned int packSize = std::stoi(deque[++index]);
      if (packSize < 2) {
            throw std::runtime_error("Invalid Events File");
      }

      std::vector<std::shared_ptr<Encounter>> packEncounters;
      index++;

      for (unsigned int i = 0; i < packSize; i++) {
            if (index >= static_cast<int>(deque.size())) {
                  throw std::runtime_error("Invalid Events File");
            }
            if (deque[index] == "Pack") {
                  std::shared_ptr<Pack> nestedPack = getPackReady(deque, index);
                  const auto &nestedEncounters = nestedPack->getEncounters();
                  packEncounters.insert(packEncounters.end(), nestedEncounters.begin(), nestedEncounters.end());
            } else {
                  packEncounters.push_back(getEncounterReady(deque[index]));
                  index++;
            }
      }

      return std::make_shared<Pack>(Pack(packEncounters));
}

void MatamStory::playTurn(Player& player) {
      shared_ptr<Event> currentEvent = events[(m_turnIndex - 1) % events.size()];
      printTurnDetails(m_turnIndex, player, currentEvent);
      int eventOutcome = currentEvent->applyEffect(player);
      printTurnOutcome(currentEvent->eventEffectResult(player, eventOutcome));
      /**
       * Steps to implement (there may be more, depending on your design):
       * 1. Get the next event from the events list
       * 2. Print the turn details with "printTurnDetails"
       * 3. Play the event
       * 4. Print the turn outcome with "printTurnOutcome"
      */

      m_turnIndex++;
}

void MatamStory::playRound() {

      printRoundStart();

      /*===== Play a turn for each player =====*/
      for (const shared_ptr<Player>& currentPlayer : players) {
            if (currentPlayer->canPlayerPlay()) {
                  playTurn(*currentPlayer);
                  if (currentPlayer->getHealthPoints() <= 0) {
                        currentPlayer->setLifeStatus();
                  }
            }
      }

      printRoundEnd();

      printLeaderBoardMessage();

      /*===== Print leaderboard entry for each player using "printLeaderBoardEntry" =====*/
      std::set<shared_ptr<Player>, CompareTwoPlayers> leaderBoard;
      for (const shared_ptr<Player>& currentPlayer : players) {
            leaderBoard.insert(currentPlayer);
      }

      unsigned int index = 1;
      for (const shared_ptr<Player>& currentPlayer : leaderBoard) {
            printLeaderBoardEntry(index, currentPlayer);
            index++;
      }

      gameWinner = *leaderBoard.begin();

      printBarrier();
}

bool MatamStory::isGameOver() const {
      /*===== Implement the game over condition =====*/
      if (areAllPlayersDead()) {
            return true;
      }
      return false;
}

void MatamStory::play() {
      printStartMessage();

      /*===== Print start message entry for each player using "printStartPlayerEntry" =====*/
      unsigned int index = 1;
      for (const shared_ptr<Player> &player: players) {
            printStartPlayerEntry(index, *player);
            index++;
      }

      printBarrier();

      while (!isGameOver()) {
            playRound();
      }

      printGameOver();

      /*===== Print either a "winner" message or "no winner" message =====*/
      if (areAllPlayersDead()) {
            printNoWinners();
      } else {
            //if character reached 10 ?
      }
}

// Helper Function: checks if the letters in a word are apart of the alphabet or not
bool MatamStory::areLettersApartOfTheAlphabet(const string& word) {
      for (const auto& letter : word) {
            if (!((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z'))) {
                  return false;
            }
      }
      return true;
}

bool MatamStory::areAllPlayersDead() const {
      for (const auto &player: players) {
            if (player->getHealthPoints() > 0) {
                  return false;
            }
      }
      return true;
}