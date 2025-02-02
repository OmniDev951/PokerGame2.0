//
// Created by ochsjax000 on 12/16/2024.
//

#ifndef GAMELOOP_H
#define GAMELOOP_H
#include "GameLoop.h"
#include "Player.h"
#include "AIOpponent.h"
#include <string>
#include <vector>
using namespace std;



class GameLoop {
private:
    AiOpponent num1;
    Player player;
    DeckOfCards deck;
    vector<PlayingCard> communityCards;
    bool isBettingRound;
    double pot;
    double ante;
    double initialAnte;
    int AIhandvalue;
    bool isBettingRoundOneFin;
    string winner;
    int handValue;
    int handValuePlayer;
    bool isRoundOneFin;
    bool isAiFin;
    bool isPlayerFin;
public:
    GameLoop();
    void gameLoop();
    void setUpRound();
    void bettingRound1();
    void bettingRound2();
    PlayingCard revealCommunityCards();
    string determineWinner();
    string strFlop();
    string strTurn();
    string strRiver();
    double getAnte();
    double getInitialAnte();
    double getEarnings();
};



#endif //GAMELOOP_H





