#include "I.h"
#include "block.h"
#include <vector>
#include <utility>
#include <iostream>

I::I(int level, int startx, int starty, int pos, char letter):
levelcreation{level}, pos{pos}, lowerleft{startx,starty}, letter{letter} {
    for(int i = 0; i < 4; ++i){coord.emplace_back(startx + i,starty);}
}

char I::getletter() {return letter;}

int I::getlevel() {return levelcreation;}

std::vector<std::pair<int,int>> I::getcoord() {return coord;}

std::vector<std::pair<int,int>> I::rotatec(std::pair<int,int> lowleft) { 
    std::vector<std::pair<int, int>> newcoord;
    int lowx = lowleft.first;
    int lowy = lowleft.second;
    if(pos == 0 || pos == 2){
        for(int i = 0; i < 4; ++i){newcoord.emplace_back(lowx, lowy + i);}
    }
    else { // CLaire is not sure if this ever gets run
        for(int i = 0; i < 4; ++i){newcoord.emplace_back(lowx + i, lowy);}
    }
    if(pos == 3) pos = 0;
    else pos += 1;
    return newcoord;
}

std::vector<std::pair<int,int>> I::rotatecc(std::pair<int,int> lowleft){
    std::vector<std::pair<int, int>> newcoord;
    for(int i = 0; i < 3; ++i){
        newcoord = rotatec(lowleft);
    }
    return newcoord;
}

void I::updatecoord(std::vector<std::pair<int,int>> newcoord){
    this->coord.clear();
    for (auto & c: newcoord){
        this->coord.emplace_back(c.first, c.second);
    }
}

I::~I(){} 
