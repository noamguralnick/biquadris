#include "player.h"
#include "display.h"
#include "generator.h"
#include <iostream> 
#include <string>
#include <vector> 
#include <utility>
#include <cmath>


Player::Player(bool isTurn, DisplayOurs *d, int level, int hiscore, int currScore): 
    d{d}, isTurn{isTurn}, level{level}, hiscore{hiscore}, currScore{currScore} {
}

void Player::changeturn(bool turn){
    this->isTurn = turn;
    if (isTurn) {
        isTurn = false;
    } else {
        isTurn = true;
    }
}

int Player::currentScore(int newPoints){
    if (newPoints != 0){
    int addedScore = pow((level + newPoints),2);
    currScore += addedScore;
    d->currScore = currScore;
    }
    highscore();
    return currScore;
}

int Player::highscore(){
    if (currScore > hiscore){
        hiscore = currScore;
    }
    d->hiScore = hiscore;
    return hiscore;
}
void Player::levelup(){
    if (level < 4){
        level += 1;
        d->level += 1;
    }
}
void Player::leveldown(){
    if (level > 0){
        level -= 1;
        d->level -= 1;
    }
}
