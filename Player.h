//
// Created by ochsjax000 on 12/6/2024.
//

// Included libraries and files
#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "DeckOfCards.h"
using namespace std;


// Player class
class Player {
private: // Private data members for the player class
    vector<PlayingCard> hand;
    double money; // a double for the amount of money the player has
    double moneyAlreadyBetThisRound; // the amount of money the player has already bet this round
    bool inRound; // Boolean for if the player is still in this round
    string decisionThisRound; // the string decision for what the player will do "match, bet, or fold"
    double moneyToBet; // the amount of money the player is going to bet
    int handValue; // the integer value for the players hand

public: // Public methods for the player
    Player(); // Constructor
    bool enterRound(); // method for asking the player If they want to play that round
    bool foldRound(); // method for the player folding out of the round
    double bet(); // method for the player betting in that betting round
    double match(double ante); // method for the player matching the ante and only that
    void matchBetFold(double ante); // asks the player what their decision this betting round is
    vector<PlayingCard> getHand (); // returns the players hand
    string str(); // prints the players hand
    vector<PlayingCard> rearrangeHand(); // rearranges the players hand randomly
    PlayingCard deal(DeckOfCards& deck); // deals a card to the players hand
    bool getinRound(); // returns if the players is in the round
    double getMoneyToBet(); // gets the amount of money the player is going to bet
    double getMoneyAlreadyBetThisRound(); // gets the amount of money the player has already bet
    int evaluateHand(const std::vector<PlayingCard>& hand, const std::vector<PlayingCard>& communityCards); // evaluates the value of the players hand
    double setMoneyAlreadyBetThisRound();
    string getDecisionThisRound();
    void setInRound(bool l);
};

#endif PLAYER_H






