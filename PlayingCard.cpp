//
// Created by ochsjax000 on 11/21/2024.
//

#include "PlayingCard.h"
#include <string>
using namespace std;

const string PlayingCard::BRAND = "Bicycle";

PlayingCard::PlayingCard() {
    rank = 14;
    suit = 0;
}

PlayingCard::PlayingCard(int r, int s) {
    rank = r;
    suit = s;
}
int PlayingCard::getRank() const {
    return rank;
}
int PlayingCard::getSuit() const {
    return suit;
}
void PlayingCard::setRank(int r) {
    rank = r;
}
void PlayingCard::setSuit(int s) {
    suit = s;
}
string PlayingCard::getColor() const {
    if (suit == 0 || suit == 3) {
        return "Black";
    }
    else {
        return "Red";
    }
}
bool PlayingCard::getFace() const {
    return rank > 10;
}
string PlayingCard::stringify() const {
    string ranks[] = {"null", "Ace", "2", "3",
        "4", "5", "6", "7", "8", "9", "10",
        "Jack", "Queen", "King", "Ace"};
    string suits[] = {"Clubs",
        "Hearts", "Diamonds", "Spades",};
    return ranks[rank] + " of " + suits[suit];
}
string PlayingCard::getBrand() {
    return BRAND;
}
bool PlayingCard::operator==(const PlayingCard &other) const {
    return rank == other.getRank();
}
bool PlayingCard::operator!=(const PlayingCard &other) const {
    return rank != other.getRank();
}
bool PlayingCard::operator<(const PlayingCard &other) const {
    return rank < other.getRank();
}
bool PlayingCard::operator>(const PlayingCard &other) const {
    return rank > other.getRank();
}
bool PlayingCard::operator<=(const PlayingCard &other) const {
    return rank <= other.getRank();
}
bool PlayingCard::operator>=(const PlayingCard &other) const {
    return rank >= other.getRank();
}


