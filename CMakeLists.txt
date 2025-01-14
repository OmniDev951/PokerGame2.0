cmake_minimum_required(VERSION 3.30)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled main.cpp
        PlayingCard.cpp
        PlayingCard.h
        DeckOfCards.cpp
        DeckOfCards.h
        Player.cpp
        Player.h
        AIPlayer.cpp
        AIPlayer.h
        GameLoop.cpp
        GameLoop.h
        AiOpponent.cpp
        AiOpponent.h)
