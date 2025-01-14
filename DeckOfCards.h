#pragma once
#ifndef DECK_OF_CARDS_H
#define DECK_OF_CARDS_H
#include<string>
#include<vector>
#include "PlayingCard.h"
#include<ctime>
using namespace std;

class DeckOfCards {
private:
    vector<PlayingCard> drawFrom;
    vector<PlayingCard> dealt;
public:
    DeckOfCards();
    string str() const;
    vector<PlayingCard> getDrawFrom() const;
    vector<PlayingCard> getDealt() const;
    void shuffle();
    PlayingCard deal();

};

#endif //DECK_OF_CARDS_H





