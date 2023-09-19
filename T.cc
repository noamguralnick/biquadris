#include "T.h"
#include "block.h"
#include <vector>
#include <utility>

T::T(int level, int startx, int starty, int pos, char letter): levelcreation{level}, pos{pos}, letter{letter}, lowerleft{startx, starty}{
    coord.emplace_back(startx+1, starty);
    for(int i = 0; i < 3; ++i){coord.emplace_back(startx+i, starty + 1);}
}

char T::getletter(){return letter;}

int T::getlevel() {return levelcreation;}

std::vector<std::pair<int,int>> T::getcoord(){return coord;}

std::vector<std::pair<int,int>> T::rotatec(std::pair<int,int> lowleft){
    std::vector<std::pair<int,int>> newcoord;
    int lowx = lowleft.first;
    int lowy = lowleft.second;

    if (pos == 0) {
        newcoord.emplace_back(lowx, lowy + 1);
        for(int i = 0; i < 3; ++i) {
            newcoord.emplace_back(lowx + 1, lowy + i);
        }
    } else if (pos == 1) {
        newcoord.emplace_back(lowx + 1, lowy + 2);
        for(int i = 0; i < 3; ++i) {
            newcoord.emplace_back(lowx + i, lowy + 1);
        }
    }else if (pos == 2) {
        newcoord.emplace_back(lowx+2, lowy + 1);
        for(int i = 0; i < 3; ++i) {
            newcoord.emplace_back(lowx + 1, lowy + i);
        }
            
    } else if (pos == 3) {
        newcoord.emplace_back(lowx+1, lowy);
        for(int i = 0; i < 3; ++i) {
            newcoord.emplace_back(lowx + i, lowy + 1);
        }
    }
    if(pos == 3) pos = 0;
    else pos += 1;  
    return newcoord; 
}

std::vector<std::pair<int,int>> T::rotatecc(std::pair<int,int> lowleft){
    std::vector<std::pair<int, int>> newcoord;
    for(int i = 0; i < 3; ++i){
        newcoord = rotatec(lowleft);
    }
    return newcoord;
}

void T::updatecoord(std::vector<std::pair<int,int>> newcoord){
    for (int i = 0; i < 4; ++i){
        coord.pop_back();
    } 
    for (auto & c: newcoord){
        coord.emplace_back(c.first, c.second);
    }
}

T::~T(){} 
