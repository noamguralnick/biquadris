#ifndef PLAYER_H
#define PLAYER_H
#include "display.h"
#include <vector>
#include <utility>

class Player {
    /*bool isTurn;
    int level;
    int hiscore;
    int currScore;*/


    public:
    DisplayOurs *d;
    bool isTurn;
    int level;
    int hiscore;
    int currScore;
    Player(bool isTurn, DisplayOurs *d, int level = 1, int hiscore = 0, int currScore = 0);

    void changeturn(bool isTurn); //called from main, handles change turn command
    int currentScore(int newPoints); //current score for the player
    int highscore(); //highscore until program terminates
    void levelup(); //called from main, handles level up command
    void leveldown(); //called from main, handes level down command
    friend class DisplayOurs;
};


#endif 

