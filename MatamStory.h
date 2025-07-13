#pragma once

#include <iostream>

#include <vector>
#include <set>
#include <deque>
#include <vector>
#include <memory>


#include "Utilities.h"
#include "Players/Player.h"
#include "Events/Event.h"
#include "Events/Encounter.h"

using std::shared_ptr;
using std::string;
using std::vector;


struct CompareTwoPlayers {
      bool operator()(const shared_ptr<Player>& player1, const shared_ptr<Player>& player2) const {
            return *player1 > *player2;
      }
};


class MatamStory {

public:

      /**
       * Constructor of MatamStory class
       *
       * @param eventsStream - events input stream (file)
       * @param playersStream - players input stream (file)
       *
       * @return - MatamStory object with the given events and players
       *
      */
      MatamStory(std::istream& eventsStream, std::istream& playersStream);

      /**
       * Plays the entire game
       *
       * @return - void
      */
      void play();

      void getPlayersReady(std::istream& playersStream);
      shared_ptr<CharacterRole> getCharacterRoleReady(const string& role);
      shared_ptr<CharacterType> getCharacterTypeReady(const string& type);
      bool areLettersApartOfTheAlphabet(const string& word);

      void getEventsReady(std::deque<string> &strings);
      std::shared_ptr<Encounter> getEncounterReady(const std::string& event);
      void dequeFromStream(std::istream &stream, std::deque<std::string> &strings);
      shared_ptr<Event> getNonPackReady(const string& event);
      shared_ptr<Pack> getPackReady(const std::deque<std::string> &deque,int &index);
      bool areAllPlayersDead() const;

private:
      vector<shared_ptr<Event>> events;
      vector<shared_ptr<Player>> players;
      shared_ptr<Player> gameWinner;
      unsigned int m_turnIndex;


      /**
       * Playes a single turn for a player
       *
       * @param player - the player to play the turn for
       *
       * @return - void
      */
      void playTurn(Player& player);

      /**
       * Plays a single round of the game
       *
       * @return - void
      */
      void playRound();

      /**
       * Checks if the game is over
       *
       * @return - true if the game is over, false otherwise
      */
      bool isGameOver() const;
};