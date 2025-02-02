//
// Created by ochsjax000 on 1/9/2025.
//

#ifndef AIOPPONENT_H
#define AIOPPONENT_H
#include <vector>
#include "DeckOfCards.h"


using namespace std; // Testing pushing and commiting to gitHub



class AiOpponent {
private:
    vector<PlayingCard> aiHand;
    double moneyAI;
    double moneyAlreadyBetThisRoundAI;
    bool inRoundAI;
    int descionThisRoundAI;
    double moneyToBetThisRoundAI;
    int handValueAI;
    int foldFactor;
    int matchFactor;
    int betFactor;
    int pairSuitCount;
    int pairCount;
    int wins;
    int gamesPlayed;
    double winPercentage;
public:
    AiOpponent();
    PlayingCard deal(DeckOfCards& deck);
    int makeDesicion(double moneyToBet, double ante);
    int evaluateHandAI(const std::vector<PlayingCard>& aiHand, const std::vector<PlayingCard>& communityCards); // evaluates the value of the ai's hand
    int makeDesicionsRound2(double moneyToBet, double ante);
    vector<PlayingCard> getHand();
    int getHandValue();
    int setHandValue(int AIhandvalue);
    double bet(double ante);
    double match(double ante);
    bool fold();
    bool enterRoundAI();
    bool getInRoundAI();
    int getPairSuitCount();
    int getPairCount();
    double getMoneyAlreadyBetThisRoundAI();
    double getMoneyToBetThisRoundAI();
    int getDescionThisRoundAI();
    void setInRoundAI(bool r);
    void setMoneyAlreadyBetThisRoundAI();
    void determineIfWinner(string winner, double pot);
    void reset();
    void adjust(string winner, vector<PlayingCard> communityCards, int handValuePlayer);
    double getMoneyAI();
};



#endif //AIOPPONENT_H





