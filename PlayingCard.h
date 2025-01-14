//
// Created by ochsjax000 on 11/21/2024.
//

#ifndef PLAYINGCARD_H
#define PLAYINGCARD_H
#pragma once
#include <string>
using namespace std;
#endif //PLAYINGCARD_H
class PlayingCard {
private:
    int rank;
    int suit;
    const static string BRAND;
public:
    PlayingCard();
    PlayingCard(int, int);
    int getRank() const;
    int getSuit() const;
    string getColor() const;
    bool getFace() const;
    void setRank(int);
    void setSuit(int);
    string stringify() const;
    static string getBrand();
    bool operator==(const PlayingCard &) const;
    bool operator!=(const PlayingCard &) const;
    bool operator<(const PlayingCard &) const;
    bool operator>(const PlayingCard &) const;
    bool operator<=(const PlayingCard &) const;
    bool operator>=(const PlayingCard &) const;


};
