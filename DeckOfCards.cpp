//
// Created by ochsjax000 on 12/2/2024.
//

#include "DeckOfCards.h"
#include<vector>
#include "PlayingCard.h"
#include<ctime>
#include<string>
using namespace std;

DeckOfCards::DeckOfCards() {
    for (int i = 0; i < 4; i++) {
        for (int j = 1; j < 14; j++) {
            drawFrom.push_back(PlayingCard(j, i));
        }
    }
}
string DeckOfCards::str() const {
    string strOut = "To Draw:\n";
    for (int i = 0; i < drawFrom.size(); i++) {
        strOut += (drawFrom.at(i).stringify() + "\n" );
    }
    strOut += ("\nDealt:\n");
    for (int i = 0; i < dealt.size(); i++) {
        strOut += (dealt.at(i).stringify() + "\n" );
    }
    return strOut;
}

vector<PlayingCard> DeckOfCards::getDealt() const {
    return dealt;
}

vector<PlayingCard> DeckOfCards::getDrawFrom() const {
    return drawFrom;
}

PlayingCard DeckOfCards::deal() {
    PlayingCard toDeal = drawFrom.at(drawFrom.size() - 1);
    drawFrom.pop_back();
    dealt.push_back(toDeal);
    return toDeal;
}

void DeckOfCards::shuffle() {
    srand(time(0));
    int idx = 0;
    while (drawFrom.size() > 0) {
        idx = rand() % drawFrom.size();
        dealt.push_back(drawFrom.at(idx));
        drawFrom.erase(drawFrom.begin() + idx);
    }
    while (dealt.size() > 0) {
        idx = rand() % dealt.size();
        drawFrom.push_back(dealt.at(idx));
        dealt.erase(dealt.begin() + idx);
    }
}