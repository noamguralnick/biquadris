#include "S.h"
#include "block.h"
#include <vector>
#include <utility>

S::S(int level, int startx, int starty, int pos, char letter):
levelcreation{level}, pos{pos}, letter{letter}, lowerleft{startx,starty} {
    int j = 0;
    int k = 0; 
    for(int i = 0; i < 4; ++i){
        coord.emplace_back(startx + k, starty + j);
            if (i == 1)  { j += 1; }
            if (i == 0 || i ==2) { k += 1; }
    }
}

char S::getletter(){return letter;}

int S::getlevel() {return levelcreation;}

std::vector<std::pair<int,int>> S::getcoord(){return coord;}

std::vector<std::pair<int,int>> S::rotatec(std::pair<int,int> lowleft) { 
    std::vector<std::pair<int,int>> newcoord;
    int lowx = lowleft.first;
    int lowy = lowleft.second;
    if(pos == 0 || pos == 2){
        int j = 2;
        int k = 0; 
        for(int i = 0; i < 4; ++i){
            newcoord.emplace_back(lowx + k, lowy + j);
            if(i == 0) { j = 1;}
            if(i == 1) { k = 1;}
            if(i == 2) { j = 0;}
        }
    } else if (pos == 1 || pos == 3){
        int lowx = lowerleft.first;
        int lowy = lowerleft.second;
             
        int j = 0;
        int k = 0; 
        for(int i = 0; i < 4; ++i){
            newcoord.emplace_back(lowx + k, lowy + j);
                if (i == 1)  { j += 1; }
                if (i == 0 || i ==2) { k += 1; }
            }
        }
        if(pos == 3) pos = 0;
        else pos += 1;
        return newcoord;
}

std::vector<std::pair<int,int>> S::rotatecc(std::pair<int,int> lowleft){
    std::vector<std::pair<int, int>> newcoord;
    for(int i = 0; i < 3; ++i){
        newcoord = rotatec(lowleft);
    }
    return newcoord;
}

void S::updatecoord(std::vector<std::pair<int,int>> newcoord){
    for (int i = 0; i < 4; ++i){
        coord.pop_back();
    } 
    for (auto & c: newcoord){
        coord.emplace_back(c.first, c.second);
    }
}

S::~S(){} 

