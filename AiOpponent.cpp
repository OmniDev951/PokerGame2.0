//
// Created by ochsjax000 on 1/9/2025.
//
#include "AiOpponent.h"
#include "DeckOfCards.h"
#include <ranges>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>
#include <iostream>
#include <iomanip>
#include <ostream>

using namespace std;

AiOpponent::AiOpponent() {
    moneyAI = 200;
    pairSuitCount = 0;
    pairCount = 0;
    aiHand = vector<PlayingCard> {};
    descionThisRoundAI = 0;
    inRoundAI = true;
    moneyToBetThisRoundAI = 0;
    moneyAlreadyBetThisRoundAI = 0;
    foldFactor = -10;
    matchFactor = 0;
    betFactor = 0;
    wins = 1;
    gamesPlayed = 1;
    winPercentage = 0;
}

void AiOpponent::reset() {
    double moneyNeedToPositive = 0;
    gamesPlayed += 1;
    pairSuitCount = 0;
    pairCount = 0;
    aiHand = vector<PlayingCard> {};
    descionThisRoundAI = 0;
    inRoundAI = true;
    moneyToBetThisRoundAI = 0;
    moneyAlreadyBetThisRoundAI = 0;
    moneyAI += 10;
    if (moneyAI < 0) {
        moneyNeedToPositive = -1 * (0-moneyAI);
        moneyAI += moneyNeedToPositive;
    }
}

double AiOpponent::getMoneyAI() {
    return moneyAI;
}



void AiOpponent::determineIfWinner(string winner, double pot) {
    if (winner == "AI") {
        moneyAI += pot;
        wins += 1;
    }
}



PlayingCard AiOpponent::deal(DeckOfCards &deck) {
    aiHand.push_back(deck.deal());
    return aiHand.back();
}
int AiOpponent::makeDesicion(double moneyToBet, double ante) {

    std::map<int, int> rankCount; // Count occurrences of each rank
    std::map<int, int> suitCount; // Count occurrences of each suit

    for (const auto& PlayingCard : aiHand) { // for every card in the vector for checking the hand value
        rankCount[PlayingCard.getRank()]++; // gets the rank for every card and increments the count for that rank
        suitCount[PlayingCard.getSuit()]++; // gets the suit for every card and increments the count for that suit
    }
    pairCount = 0;
    for (const auto& [rank, count] : rankCount) {
        if (count == 2) pairCount++; // Checks for pair by seeing if there are two occurences of two cards of the same rank
    }
    pairSuitCount = 0;
    for (const auto& [suit, count] : suitCount) {
        if (count == 2) pairSuitCount++;
    }

    descionThisRoundAI = 0;

    if (pairSuitCount == 1 and pairCount == 1) {
        betFactor += 4;
        matchFactor++;
        foldFactor--;
    }
    else if (pairSuitCount == 1 and pairCount == 0) {
        betFactor += 1;
        matchFactor += 3;
        foldFactor--;
    }
    else if (pairSuitCount == 0 and pairCount == 1) {
        betFactor += 1;
        matchFactor += 2;
        foldFactor--;
    }
    else if (pairSuitCount == 0 and pairCount == 0) {
        betFactor -= 2;
        matchFactor -= 1;
        foldFactor += 3;
    }

    if (moneyToBet >= 50 and  pairSuitCount == 1 and pairCount == 1) {
        betFactor += 1;
        matchFactor += 2;
        foldFactor--;
    }
    else if (moneyToBet >= 50 and pairSuitCount == 1 and pairCount == 0) {
        betFactor -= 2;
        matchFactor += 2;
        foldFactor += 1;
    }
    else if (moneyToBet >= 50 and pairSuitCount == 0 and pairCount == 1) {
        betFactor -= 1;
        matchFactor += 1;
        foldFactor +=2;
    }

    else if (moneyToBet >= 50 and pairSuitCount == 0 and pairCount == 0) {
        betFactor -= 2;
        matchFactor -= 1;
        foldFactor += 3;
    }
    else if (moneyToBet >= 30 and  pairSuitCount == 1 and pairCount == 1) {
        betFactor += 2;
        matchFactor += 1;
        foldFactor--;
    }
    else if (moneyToBet >= 30 and pairSuitCount == 1 and pairCount == 0) {
        betFactor -= 1;
        matchFactor += 2;
        foldFactor += 0;
    }
    else if (moneyToBet >= 30 and pairSuitCount == 0 and pairCount == 1) {
        betFactor -= 1;
        matchFactor += 2;
        foldFactor += 1;
    }
    else if (moneyToBet >= 30 and pairSuitCount == 0 and pairCount == 0) {
        betFactor -= 2;
        matchFactor += 1;
        foldFactor += 2;
    }
    else if (moneyToBet == 0 and pairSuitCount == 1 and pairCount == 1) {
        betFactor += 2;
        matchFactor += 1;
        foldFactor -= 2;
    }
    else if (moneyToBet == 0 and pairSuitCount == 1 and pairCount == 0) {
        betFactor += 1;
        matchFactor += 2;
        foldFactor--;
    }
    else if (moneyToBet == 0 and pairSuitCount == 0 and pairCount == 1) {
        betFactor -= 1;
        matchFactor += 1;
        foldFactor--;
    }
    else if (moneyToBet == 0 and pairSuitCount == 0 and pairCount == 0) {
        betFactor -= 2;
        matchFactor += 1;
        foldFactor += 1;
    }

    if (betFactor > matchFactor and betFactor > foldFactor) {
        this->bet(ante);
        descionThisRoundAI = 1;
        return descionThisRoundAI;
    }
    else if (matchFactor > betFactor and matchFactor > foldFactor) {
        this->match(ante);
        descionThisRoundAI = 2;
        return descionThisRoundAI;
    }
    else if (foldFactor > matchFactor and foldFactor > betFactor) {
        this->fold();
        descionThisRoundAI = 3;
        return descionThisRoundAI;
    }

}



int AiOpponent::evaluateHandAI(const std::vector<PlayingCard>& hand, const std::vector<PlayingCard>& communityCards) { // function for evaluating the value of the hand
    // Combine hand and community cards
    std::vector<PlayingCard> cards = hand; // makes a vector of PlayingCard that starts with by adding the players cards
    cards.insert(cards.end(), communityCards.begin(), communityCards.end()); // adds the community cards

    if (cards.size() < 5) { // checks the size of the vector to see if it is greater than 5
        return 0; // Not enough cards to evaluate
    }

    // Helper maps
    std::map<int, int> rankCount; // Count occurrences of each rank
    std::map<int, int> suitCount; // Count occurrences of each suit

    for (const auto& PlayingCard : cards) { // for every card in the vector for checking the hand value
        rankCount[PlayingCard.getRank()]++; // gets the rank for every card and increments the count for that rank
        suitCount[PlayingCard.getSuit()]++; // gets the suit for every card and increments the count for that suit
    }

    // Check for Flush (5 cards of the same suit)
    bool isFlush = false;
    for (const auto& [suit, count] : suitCount) { // for all the cards in the vector check for the amount of that suit
        if (count >= 5) { // if the amount of cards of the same suit is equal to or greater than 5
            isFlush = true; // sets isFlush to true
            break; // breaks off program
        }
    }

    // Check for Straight
    std::vector<int> sortedRanks; // creates an empty vector for sorting by rank in numerical order
    for (const auto& [rank, count] : rankCount) { // for loop so it adds all the cards
        sortedRanks.push_back(rank); // adds them here
    }
    std::sort(sortedRanks.begin(), sortedRanks.end()); // sorts by rank

    int straightCount = 0; // sets a value for seeing how many straights there are aka 6,5
    bool isStraight = false; // sets a bool to see if it is a straight and sets it to false
    for (size_t i = 0; i < sortedRanks.size(); ++i) { // for loop going through the whole vector
        if (i > 0 && sortedRanks[i] == sortedRanks[i - 1] + 1) { // goes through the sorted vector checking for ranks
            straightCount++; // increments the straight count for every straight in the vector
        } else if (i > 0 && sortedRanks[i] != sortedRanks[i - 1]) {
            straightCount = 1; // sets straight count to one
        }
        if (straightCount >= 5) { // checks to see if the amount of two card straights add up to 5 cards the minimum for a straight
            isStraight = true; // sets isStraight to true
            break; // stops the program
        }
    }

    // Check for Four of a Kind, Full House, Three of a Kind, Two Pair, One Pair
    int fourCount = 0, threeCount = 0, pairCount = 0;
    for (const auto& [rank, count] : rankCount) {
        if (count == 4) fourCount++; // Checks for four count by seeing if the count of a certain ranks is equal to 4 total
        if (count == 3) threeCount++; // Checks for three count by seeing if the count of a certain ranks is equal to 3 total
        if (count == 2) pairCount++; // Checks for pair by seeing if there are two occurences of two cards of the same rank
    }

    // Determine the best hand value
    if (isStraight && isFlush) {
        return 8; // Straight Flush
    } else if (fourCount > 0) {
        return 7; // Four of a Kind
    } else if (threeCount > 0 && pairCount > 0) {
        return 6; // Full House
    } else if (isFlush) {
        return 5; // Flush
    } else if (isStraight) {
        return 4; // Straight
    } else if (threeCount > 0) {
        return 3; // Three of a Kind
    } else if (pairCount >= 2) {
        return 2; // Two Pair
    } else if (pairCount == 1) {
        return 1; // One Pair
    } else {
        return 0; // High Card
    }
}

int AiOpponent::makeDesicionsRound2(double MoneyToBet, double ante) {
    this->getHandValue();
    if (handValueAI == 8) {
        betFactor += 8;
        matchFactor += 2;
        foldFactor -= 6;
    }
    else if (handValueAI == 7) {
        betFactor += 7;
        matchFactor += 2;
        foldFactor -= 5;
    }
    else if (handValueAI == 6) {
        betFactor += 6;
        matchFactor += 2;
        foldFactor -= 4;
    }
    else if (handValueAI == 5) {
        betFactor += 3;
        matchFactor += 2;
        foldFactor -= 3;
    }
    else if (handValueAI == 4) {
        betFactor += 2;
        matchFactor += 2;
        foldFactor--;
    }
    else if (handValueAI == 3) {
        betFactor += 1;
        matchFactor += 3;
        foldFactor += 1;
    }
    else if (handValueAI == 2) {
        betFactor -= 1;
        matchFactor += 4;
        foldFactor += 2;
    }
    else if (handValueAI == 1) {
        betFactor -= 2;
        matchFactor += 3;
        foldFactor += 3;
    }
    else if (handValueAI == 0) {
        betFactor -= 3;
        matchFactor -= 3;
        foldFactor += 5;
    }


    if (betFactor > matchFactor and betFactor > foldFactor) {
        this->bet(ante);
        descionThisRoundAI = 1;
        return descionThisRoundAI;
    }
    else if (matchFactor > betFactor and matchFactor > foldFactor) {
        this->match(ante);
        descionThisRoundAI = 2;
        return descionThisRoundAI;
    }
    else if (foldFactor > matchFactor and foldFactor > betFactor) {
        this->fold();
        descionThisRoundAI = 3;
        return descionThisRoundAI;
    }

}
vector<PlayingCard> AiOpponent::getHand() {
    return aiHand;
}
int AiOpponent::getHandValue() {
    return handValueAI;
}
int AiOpponent::setHandValue(int AIhandValue) {
    handValueAI = AIhandValue;
    return handValueAI;
}
bool AiOpponent::getInRoundAI() {
    return inRoundAI;
}
double AiOpponent::bet(double ante) {
    int howMuchToBetPair = this->getPairCount();
    int howMuchToBetSuit = this->getPairSuitCount();
    if ( howMuchToBetSuit == 1 and howMuchToBetPair == 1) {
        moneyToBetThisRoundAI = 50 + ante;
    }
    else if (howMuchToBetSuit == 1 and howMuchToBetPair == 0) {
        moneyToBetThisRoundAI = 40 + ante;
    }
    else if (howMuchToBetSuit == 0 and howMuchToBetPair == 1) {
        moneyToBetThisRoundAI = 30 + ante;
    }
    else if (howMuchToBetSuit == 0 and moneyToBetThisRoundAI == 0) {
        moneyToBetThisRoundAI = 20 + ante;
    }
    moneyAlreadyBetThisRoundAI = moneyAlreadyBetThisRoundAI + moneyToBetThisRoundAI;
    return moneyToBetThisRoundAI;
}
int AiOpponent::getPairSuitCount() {
    return pairSuitCount;
}
int AiOpponent::getPairCount() {
    return pairCount;
}
double AiOpponent::getMoneyAlreadyBetThisRoundAI() {
    return moneyAlreadyBetThisRoundAI;
}
double AiOpponent::getMoneyToBetThisRoundAI() {
    return moneyToBetThisRoundAI;
}
int AiOpponent::getDescionThisRoundAI() {
    return descionThisRoundAI;
}
void AiOpponent::setInRoundAI(bool r) {
    inRoundAI = r;
}
double AiOpponent::match(double ante) {
    double moneyNeededMatch = ante - moneyAlreadyBetThisRoundAI;
    moneyAI -= moneyNeededMatch;
    moneyAlreadyBetThisRoundAI += moneyNeededMatch;
    return moneyAlreadyBetThisRoundAI;
}

bool AiOpponent::fold() {
    inRoundAI = false;
    return inRoundAI;
}
void AiOpponent::setMoneyAlreadyBetThisRoundAI() {
    moneyAlreadyBetThisRoundAI = 0;
}
void AiOpponent::adjust(string winner, vector<PlayingCard> communityCards, int handValuePlayer) {

    handValueAI = this->evaluateHandAI(vector<PlayingCard> (aiHand),vector<PlayingCard> (communityCards));
    if (handValueAI > handValuePlayer and winner == "AI") {
        if (descionThisRoundAI == 1) {
            betFactor += 2;
        }
        else if (descionThisRoundAI == 2) {
            matchFactor += 2;
        }
    }
    else if (handValueAI > handValuePlayer and winner == "Player") {
        foldFactor -= 3;
        matchFactor += 3;
        betFactor += 5;
    }


    // calculate winning percentage
    winPercentage = wins / gamesPlayed;

    for (int i = 60; i < 100; i+=10){
        if (winPercentage >= i) {
            if (descionThisRoundAI == 1) {
                betFactor += 2;
                matchFactor += 1;
                foldFactor --;
            }
            else if (descionThisRoundAI == 2) {
                betFactor += 1;
                matchFactor += 2;
                foldFactor --;
            }
        }
    }
    for (int j = 60; j < 0; j-=10) {
        if (winPercentage <= j) {
            if (descionThisRoundAI == 1) {
                betFactor -= 2;
                matchFactor -= 1;
                foldFactor += 1;
            }
            else if (descionThisRoundAI == 2) {
                betFactor -= 1;
                matchFactor -= 2;
                foldFactor += 1;
            }
            else if (descionThisRoundAI == 3) {
                betFactor += 5;
                matchFactor += 4;
                foldFactor -= 5;
            }
        }
    }
}











