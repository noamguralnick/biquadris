#include "J.h"
#include "block.h"
#include <vector>
#include <utility>

J::J(int level, int startx, int starty, int pos, char letter): 
levelcreation{level}, pos{pos}, letter{letter}, lowerleft{startx, starty}{ //look at shape to plan coordinates
    coord.emplace_back(startx, starty+1);
    for(int i = 0; i < 3; ++i){coord.emplace_back(startx + i,starty);}
}

char J::getletter() {return letter;}

int J::getlevel() {return levelcreation;}

std::vector<std::pair<int,int>> J::getcoord() {return coord;}

std::vector<std::pair<int,int>> J::rotatec(std::pair<int,int> lowleft) { 
    std::vector<std::pair<int, int>> newcoord;
    int lowx = lowleft.first;
    int lowy = lowleft.second;

    if(pos == 3) pos = 0;
    else pos += 1;

    if (pos == 0){
        newcoord.emplace_back(lowx, lowy + 1);
        for (int i = 0; i < 3; ++i){newcoord.emplace_back(lowx + i, lowy);}
    } else if(pos == 1){
        newcoord.emplace_back(lowx + 1, lowy + 2);
        for (int i = 0; i < 3; ++i){newcoord.emplace_back(lowx, lowy + i);}
    } else if (pos == 2){
        newcoord.emplace_back(lowx +2, lowy);
        for (int i = 0; i < 3; ++i){
            newcoord.emplace_back(lowx + i, lowy +1);
        }
    } else if (pos == 3){
        newcoord.emplace_back(lowx, lowy);
        for (int i = 0; i < 3; ++i){
            newcoord.emplace_back(lowx + 1, lowy + i);
        }
    }
    
    return newcoord;
}
        


std::vector<std::pair<int,int>> J::rotatecc(std::pair<int,int> lowleft){
    std::vector<std::pair<int, int>> newcoord;
    for(int i = 0; i < 3; ++i){
        newcoord = rotatec(lowleft);
    }
    return newcoord;
}

void J::updatecoord(std::vector<std::pair<int,int>> newcoord){
    for (int i = 0; i < 4; ++i){
        coord.pop_back();
    } 
    for (auto & c: newcoord){
        coord.emplace_back(c.first, c.second);
    }
}

J::~J(){} 
