// C// Created by ochsjax000 on 12/16/2024.

#include "GameLoop.h"
#include "Player.h"
#include "AiOpponent.h"
#include "DeckOfCards.h"
#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

//  for GameLoop
GameLoop::GameLoop() {
    communityCards = vector<PlayingCard>{};
    pot = 0;
    ante = 0;
    isBettingRound = false;
    initialAnte = 0;
    AIhandvalue = 0;
    isBettingRoundOneFin = false;
    winner = "";
}

void GameLoop::gameLoop() {
    this->setUpRound();
    this->bettingRound1();
    this->revealCommunityCards();
    player.setMoneyAlreadyBetThisRound();
    num1.setMoneyAlreadyBetThisRoundAI();
    AIhandvalue = num1.evaluateHandAI(communityCards, num1.getHand());
    num1.setHandValue(AIhandvalue);
    this->bettingRound2();
    this->determineWinner();
    cout << "==============================" << endl;
    cout << "And the winner is......" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << winner << "!!!!!!!!!" << endl;
    cout << "==============================" << endl;
    player.determineIfWinner(winner, pot);
    num1.determineIfWinner(winner, pot);
    communityCards = vector<PlayingCard> {};
    pot = 0;
    ante = 0;
    isBettingRound = false;
    isBettingRoundOneFin = false;
    initialAnte = 0;
    winner = "";
    AIhandvalue = 0;
    player.reset();
    num1.reset();
}





void GameLoop::setUpRound() {
    deck.shuffle();
    num1.deal(deck);
    num1.deal(deck);
    player.enterRound();
    if (player.getinRound() == true) {
        for (int i = 0; i < 2; i++) {
            player.deal(deck);
        }
        cout << "==============================\n";
        cout << "         Player's Hand        \n";
        cout << "==============================\n";
        cout << player.str() << endl;
    }
    cout << "==============================\n";
    cout << "     Setting Up the Ante      \n";
    cout << "==============================\n";
    cout << "What would you like the ante to be at least when you start every betting round: " << endl;
    cin >> initialAnte;
}

PlayingCard GameLoop::revealCommunityCards() {
    if (player.getinRound() == true) {
        communityCards.push_back(deck.deal());
        communityCards.push_back(deck.deal());
        communityCards.push_back(deck.deal());
        cout << this->strFlop() << endl;
        communityCards.push_back(deck.deal());
        cout << this->strTurn() << endl;
        communityCards.push_back(deck.deal());
        cout << this->strRiver();
        return communityCards.back();
    } else {
        communityCards.push_back(deck.deal());
        communityCards.push_back(deck.deal());
        communityCards.push_back(deck.deal());
        communityCards.push_back(deck.deal());
        communityCards.push_back(deck.deal());
        return communityCards.back();
    }
}

string GameLoop::strFlop() {
    string strOut = "==============================\n";
    strOut += "         Flop Cards           \n";
    strOut += "==============================\n";
    this_thread::sleep_for(chrono::seconds(1));
    for (int i = 0; i < communityCards.size(); i++) {
        strOut += (communityCards.at(i).stringify() + "\n");
        this_thread::sleep_for(chrono::seconds(1));
    }
    return strOut;
}

string GameLoop::strTurn() {
    string strOut = "==============================\n";
    strOut += "         Turn Card            \n";
    strOut += "==============================\n";
    this_thread::sleep_for(chrono::seconds(1));
    for (int i = 3; i < communityCards.size(); i++) {
        strOut += (communityCards.at(i).stringify() + "\n");
        this_thread::sleep_for(chrono::seconds(1));
    }
    return strOut;
}

string GameLoop::strRiver() {
    string strOut = "==============================\n";
    strOut += "         River Card           \n";
    strOut += "==============================\n";
    this_thread::sleep_for(chrono::seconds(1));
    for (int i = 4; i < communityCards.size(); i++) {
        strOut += (communityCards.at(i).stringify() + "\n");
        this_thread::sleep_for(chrono::seconds(1));
    }
    return strOut;
}



double GameLoop::getAnte() {
    return ante;
}

double GameLoop::getInitialAnte() {
    return initialAnte;
}

void GameLoop::bettingRound1() {
    ante = initialAnte;
    pot += ante;
    bool isRoundOneFin = false;
    bool isAiFin = false;
    bool isPlayerFin = false;

    while (isRoundOneFin == false) {
        isRoundOneFin = false; // Assume not finished until proven otherwise

        // AI Turn
        if (num1.getInRoundAI()) {
            while (num1.getMoneyAlreadyBetThisRoundAI() < ante) {
                num1.makeDesicion(player.getMoneyToBet(), ante);

                if (num1.getDescionThisRoundAI() == 1) { // AI bets
                    ante = num1.getMoneyToBetThisRoundAI();
                    pot += num1.getMoneyToBetThisRoundAI();
                    cout << "The ai bets..." << endl;
                    cout << "The new ante is: " << ante << endl;
                    isAiFin = true;

                    // Reset player state if their current bet is less than the new ante
                    if (player.getMoneyAlreadyBetThisRound() < ante) {
                        isPlayerFin = false;
                    }
                    break; // Exit AI's inner loop
                } else if (num1.getDescionThisRoundAI() == 2) { // AI matches
                    pot += ante;
                    cout << "The AI matches." << endl;
                    isAiFin = true;
                    break; // Exit AI's inner loop
                } else if (num1.getDescionThisRoundAI() == 3) { // AI folds
                    cout << "The AI folds." << endl;
                    isAiFin = true;
                    num1.setInRoundAI(false);
                    break; // Exit AI's inner loop
                }
            }
        } else {
            isAiFin = true; // AI not in the round anymore
        }

        // Player Turn
        if (player.getinRound()) {
            while (player.getMoneyAlreadyBetThisRound() < ante) {
                player.matchBetFold(ante);

                if (player.getDecisionThisRound() == "bet") { // Player bets
                    ante = player.getMoneyToBet();
                    pot += player.getMoneyToBet();
                    cout << "The new ante is: " << ante << endl;
                    isPlayerFin = true;

                    // Reset AI state if their current bet is less than the new ante
                    if (num1.getMoneyAlreadyBetThisRoundAI() < ante) {
                        isAiFin = false;
                    }
                    break; // Exit Player's inner loop
                } else if (player.getDecisionThisRound() == "match") { // Player matches
                    pot += ante;
                    cout << "You matched the ante." << endl;
                    isPlayerFin = true;
                    break; // Exit Player's inner loop
                } else if (player.getDecisionThisRound() == "fold") { // Player folds
                    cout << "You folded..." << endl;
                    isPlayerFin = true;
                    player.setInRound(false);
                    break; // Exit Player's inner loop
                }
            }
        } else {
            isPlayerFin = true; // Player not in the round anymore
        }

        // Check if the round is finished
        if (isAiFin == true & isPlayerFin == true) {
            cout << "Betting round done!" << endl;
            cout << "==============================\n";
            cout << "         Updated pot         \n";
            cout << "==============================\n";
            cout << "              " << pot << "          " << endl;
            break;

        }
        else {
            isRoundOneFin = false;
        }
    }
}

void GameLoop::bettingRound2() {
    ante = initialAnte;
    pot += ante;
    bool isRoundOneFin = false;
    bool isAiFin = false;
    bool isPlayerFin = false;

    while (isRoundOneFin == false) {
        isRoundOneFin = false; // Assume not finished until proven otherwise

        // AI Turn
        if (num1.getInRoundAI()) {
            while (num1.getMoneyAlreadyBetThisRoundAI() < ante) {
                num1.makeDesicionsRound2(player.getMoneyToBet(), ante);

                if (num1.getDescionThisRoundAI() == 1) { // AI bets
                    ante = num1.getMoneyToBetThisRoundAI();
                    pot += num1.getMoneyToBetThisRoundAI();
                    cout << "The ai bets..." << endl;
                    cout << "The new ante is: " << ante << endl;
                    isAiFin = true;

                    // Reset player state if their current bet is less than the new ante
                    if (player.getMoneyAlreadyBetThisRound() < ante) {
                        isPlayerFin = false;
                    }
                    break; // Exit AI's inner loop
                } else if (num1.getDescionThisRoundAI() == 2) { // AI matches
                    pot += ante;
                    cout << "The AI matches." << endl;
                    isAiFin = true;
                    break; // Exit AI's inner loop
                } else if (num1.getDescionThisRoundAI() == 3) { // AI folds
                    cout << "The AI folds." << endl;
                    isAiFin = true;
                    num1.setInRoundAI(false);
                    break; // Exit AI's inner loop
                }
            }
        } else {
            isAiFin = true; // AI not in the round anymore
        }

        // Player Turn
        if (player.getinRound()) {
            while (player.getMoneyAlreadyBetThisRound() < ante) {
                player.matchBetFold(ante);

                if (player.getDecisionThisRound() == "bet") { // Player bets
                    ante = player.getMoneyToBet();
                    pot += player.getMoneyToBet();
                    cout << "The new ante is: " << ante << endl;
                    isPlayerFin = true;

                    // Reset AI state if their current bet is less than the new ante
                    if (num1.getMoneyAlreadyBetThisRoundAI() < ante) {
                        isAiFin = false;
                    }
                    break; // Exit Player's inner loop
                } else if (player.getDecisionThisRound() == "match") { // Player matches
                    pot += ante;
                    cout << "You matched the ante." << endl;
                    isPlayerFin = true;
                    break; // Exit Player's inner loop
                } else if (player.getDecisionThisRound() == "fold") { // Player folds
                    cout << "You folded..." << endl;
                    isPlayerFin = true;
                    player.setInRound(false);
                    break; // Exit Player's inner loop
                }
            }
        } else {
            isPlayerFin = true; // Player not in the round anymore
        }

        // Check if the round is finished
        if (isAiFin == true & isPlayerFin == true) {
            cout << "Betting round done!" << endl;
            cout << "==============================\n";
            cout << "         Updated pot         \n";
            cout << "==============================\n";
            cout << "              " << pot << "          " << endl;
            break;

        }
        else {
            isRoundOneFin = false;
        }
    }


}

string GameLoop::determineWinner() {
    int handValue = -1;
    int handValuePlayer = -1;
    bool canCompareAI = false;
    bool canComparePlayer = false;
    if (player.getinRound() == true) {
        handValuePlayer = player.evaluateHand(communityCards, player.getHand());
        cout << "==============================\n";
        cout << "       Final Hand Value       \n";
        cout << "==============================\n";
        switch (handValuePlayer) {
            case 8:
                cout << "Straight Flush" << endl;
            break;
            case 7:
                cout << "Four of a Kind" << endl;
            break;
            case 6:
                cout << "Full House" << endl;
            break;
            case 5:
                cout << "Flush" << endl;
            break;
            case 4:
                cout << "Straight" << endl;
            break;
            case 3:
                cout << "Three of a Kind" << endl;
            break;
            case 2:
                cout << "Two Pair" << endl;
            break;
            case 1:
                cout << "One Pair" << endl;
            break;
            case 0:
                cout << "High Card" << endl;
            break;
        }
    }
    if (player.getinRound () == true) {
        canComparePlayer = true;
    }

    if (num1.getInRoundAI() == true) {
        handValue = num1.getHandValue();
    }

    if (num1.getInRoundAI() == true) {
        canCompareAI = true;
    }
    if ((canComparePlayer == true) && (canCompareAI == true)) {
        if (handValue > handValuePlayer) {
            winner = "AI";
            return winner;
        }
        else if (handValue < handValuePlayer) {
            winner = "Player";
            return winner;
        }
        else if (handValue == handValuePlayer) {
            winner = "Tie";
            return winner;
        }
    }
    else if ((canComparePlayer == true) && (canCompareAI == false)) {
        winner = "Player";
        return winner;
    }
    else if ((canComparePlayer == false) && (canCompareAI == true)) {
        winner = "AI";
    }
}




















