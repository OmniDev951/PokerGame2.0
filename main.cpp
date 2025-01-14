#include <iostream>

#include<string>
#include "GameLoop.h"
#include "Player.h"
using namespace std;
int main() {
    GameLoop game;
    game.gameLoop();
    cout << "Round one..." << endl;
    game.gameLoop();
    cout << "Good job your code worked!!!" << endl;
    return 0;
}



// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.