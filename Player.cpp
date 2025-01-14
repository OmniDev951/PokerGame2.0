// Created by ochsjax000 on 12/6/2024

#include "Player.h"
#include "DeckOfCards.h"
#include "GameLoop.h"
#include <vector>
#include <algorithm>
#include <map>
#include <utility>
#include <iostream>
#include <iomanip>
#include <ostream>

// Constructor for a player object
Player::Player() {
    money = 200.00;
    hand = vector<PlayingCard>{};
    inRound = true;
    moneyToBet = 0;
    moneyAlreadyBetThisRound = 0;
    handValue = 0;
}

// Method for asking the player if they want to join into that round
bool Player::enterRound() {
    string enterRound = "";
    cout << "==============================\n";
    cout << "     Round Entry Decision     \n";
    cout << "==============================\n";
    cout << "Would you like to play this round?\n";
    cout << "Remember it costs $10 to play each round.\n";
    cout << "Your current total money: $" << money << "\n";

    if (money < 10) {
        cout << "\n--- Insufficient Funds ---\n";
        cout << "You can't play this round...\n";
        cout << "Remember you get $10 at the end of every round.\n";
        cout << "Better luck next round!\n";
        inRound = false;
    } else {
        cout << "\nYou have enough money to play this round!\n";
        cout << "Would you like to 'Play' or 'Sit'? " << endl;
        cin >> enterRound;

        if (enterRound == "Play") {
            cout << "\nGreat choice! Deducting $10...\n";
            money -= 10;
            inRound = true;

        } else if (enterRound == "Sit") {
            cout << "\nAlright, sitting out this round.\n";
            inRound = false;
        } else {
            cout << "\nInvalid input. Please decide next time.\n";
            inRound = false;
        }
    }

    cout << "==============================\n";
    return inRound;
}

// Method for the player to bet more money than the current ante
double Player::bet() {
    cout << "==============================\n";
    cout << "         Betting Phase        \n";
    cout << "==============================\n";
    cout << "Your total money: $" << money << "\n";
    cout << "How much would you like to bet? " << endl;
    cin >> moneyToBet;

    cout << "\n--- Placing Your Bet ---\n";
    cout << "Additional money bet: $" << moneyToBet << "\n";
    moneyAlreadyBetThisRound += moneyToBet;

    cout << "Total money bet this round: $" << moneyAlreadyBetThisRound << "\n";
    money -= moneyToBet;
    cout << "Remaining balance: $" << money << "\n";
    cout << "==============================\n";

    return moneyAlreadyBetThisRound;
}

// Logic for the player matching the ante
double Player::match(double ante) {
    string descisionToMatchString = "";
    double moneyToMatch = ante - this->getMoneyAlreadyBetThisRound();
    moneyAlreadyBetThisRound = this->getMoneyAlreadyBetThisRound();

    cout << "==============================\n";
    cout << "       Matching Phase         \n";
    cout << "==============================\n";
    cout << "Your total money: $" << money << "\n";
    cout << "You need to pay: $" << moneyToMatch << "\n";
    cout << "Would you like to match? (Enter 'match' or 'sit') \n";
    cin >> descisionToMatchString;

    if (descisionToMatchString == "sit") {
        cout << "\nSitting out this round.\n";
        this->matchBetFold(double(ante));
    } else if (descisionToMatchString == "match") {
        moneyAlreadyBetThisRound += moneyToMatch;
        cout << "\nPaying the required amount...\n";
        money -= moneyToMatch;
    } else {
        cout << "\nInvalid input.\n";
    }

    cout << "Total money bet this round: $" << moneyAlreadyBetThisRound << "\n";
    cout << "Remaining balance: $" << money << "\n";
    cout << "==============================\n";

    return moneyAlreadyBetThisRound;
}

// Logic for if the player chooses to fold
bool Player::foldRound() {
    cout << "==============================\n";
    cout << "         Folding Phase         \n";
    cout << "==============================\n";
    cout << "Fold the round!\n";
    cout << "You had already bet: $" << moneyAlreadyBetThisRound << "\n";
    cout << "Better luck next time!\n";
    inRound = false;
    cout << "==============================\n";
    return inRound;
}

// Asks the player what they want to do each betting round
void Player::matchBetFold(double ante) {
    cout << "==============================\n";
    cout << "     Match, Bet, or Fold?     \n";
    cout << "==============================\n";
    cout << "Your total money: $" << money << "\n";
    cout << "Would you like to 'match', 'bet', or 'fold'? " << endl;
    cin >> decisionThisRound;

    if (decisionThisRound == "fold") {
        this->foldRound();
    } else if (decisionThisRound == "bet") {
        this->bet();
    } else if (decisionThisRound == "match") {
        this->match(double(ante));
    } else {
        cout << "\nInvalid input.\n";
    }

    cout << "==============================\n";
}

// Prints the player's hand
string Player::str() {
    string strOut = "==============================\n";
    strOut += "         Your Hand            \n";
    strOut += "==============================\n";

    for (int i = 0; i < hand.size(); i++) {
        strOut += (hand.at(i).stringify() + "\n");
    }

    strOut += "\nI reckon that's a mighty fine hand!\n";
    strOut += "==============================\n";
    return strOut;
}

// Rearranges the player's hand randomly
vector<PlayingCard> Player::rearrangeHand() {
    vector temporaryHand = vector<PlayingCard>{};
    srand(time(0));
    int idx = 0;

    while (hand.size() > 0) {
        idx = rand() % hand.size();
        temporaryHand.push_back(hand.at(idx));
        hand.erase(hand.begin() + idx);
    }

    while (temporaryHand.size() > 0) {
        idx = rand() % temporaryHand.size();
        hand.push_back(temporaryHand.at(idx));
        temporaryHand.erase(temporaryHand.begin() + idx);
    }

    return hand;
}

// Getter for player's hand
vector<PlayingCard> Player::getHand() {
    return hand;
}

// Deals a card to the player's hand
PlayingCard Player::deal(DeckOfCards &deck) {
    hand.push_back(deck.deal());
    return hand.back();
}

// Getter for if the player is in round
bool Player::getinRound() {
    return inRound;
}

// Getter for the amount of money the player wants to bet
double Player::getMoneyToBet() {
    return moneyToBet;
}

// Getter for how much money the player has already bet this round
double Player::getMoneyAlreadyBetThisRound() {
    return moneyAlreadyBetThisRound;
}

int Player::evaluateHand(const std::vector<PlayingCard>& hand, const std::vector<PlayingCard>& communityCards) { // function for evaluating the value of the hand
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


double Player::setMoneyAlreadyBetThisRound() {
    moneyAlreadyBetThisRound = 0;
    return moneyAlreadyBetThisRound;
}

string Player::getDecisionThisRound() {
    return decisionThisRound;
}
void Player::setInRound(bool l) {
    inRound = l;
}




