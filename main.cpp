#include <iostream>

#include<string>
#include "GameLoop.h"
#include "Player.h"
using namespace std;
int main() {
    GameLoop game;
    bool wantToPlayStill = false;
    string WantToPlayStillinput = "";
    cout << "Want to play texas hold em' partner, 'yes', 'no'" << endl;
    cin >> WantToPlayStillinput;
    if (WantToPlayStillinput == "yes") {
        wantToPlayStill = true;
    }
    else if (WantToPlayStillinput == "no") {
        wantToPlayStill = false;
    }
    while (wantToPlayStill == true) {
        game.gameLoop();
        cout << "Want to keep playing, 'yes', 'no'" << endl;
        WantToPlayStillinput = "";
        cin >> WantToPlayStillinput;
        if (WantToPlayStillinput == "yes") {
            wantToPlayStill = true;
        }
        else if (WantToPlayStillinput == "no") {
            cout << "Well it was fun playing partner" << endl;
            double printedEarnigs = game.getEarnings();
            cout << "You made " << printedEarnigs << "dollars!!!" << endl;
            if (printedEarnigs >= 100) {
                cout << "Stopping here seems like a mistake but whatever you say partner..." << endl;
            }
            else if (printedEarnigs >= 50) {
                cout << "I honestly don't know why you would stop here, you're really getting into a grove..." << endl;
            }
            else if (printedEarnigs < 30) {
                cout << "I guess I can see why would would quit..." << endl;
            }
            else if (printedEarnigs < 0) {
                cout << "Yeesh stopping was a good idea..." << endl;
            }
            wantToPlayStill = false;
        }
    }


    return 0;
}




// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.