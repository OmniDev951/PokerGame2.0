//
// Created by ochsjax000 on 12/6/2024.
//

#ifndef AIPLAYER_H
#define AIPLAYER_H
#include <vector>
#include "DeckOfCards.h"
using namespace std;



class Player {
private:
    vector<PlayingCard> hand;
    double money;
    double moneyAlreadyBetThisRound;
    bool inRound;
    string decisionThisRound;
    double moneyToBet;

public:
    Player();
    bool enterRound();
    bool foldRound();
    double bet();
    double match(double ante);
    void matchBetFold(double ante);
    vector<PlayingCard> getHand ();
    string str();
    PlayingCard deal(DeckOfCards& deck);
    bool getinRound();
    double getMoneyToBet();
    double getMoneyAlreadyBetThisRound();
};

#endif AIPLAYER_H
