#include <utility>
#include <vector>
#include "Z.h"
#include "block.h"

Z::Z(int level, int startx, int starty, int pos, char letter):
levelcreation{level}, pos{pos}, letter{letter}, lowerleft{startx,starty} {
    coord.emplace_back(startx, starty + 1);
    coord.emplace_back(startx + 1, starty + 1);
    coord.emplace_back(startx + 1, starty);
    coord.emplace_back(startx + 2, starty);
}

char Z::getletter() {return letter;}

int Z::getlevel() {return levelcreation;}

std::vector<std::pair<int,int>> Z::getcoord() {return coord;}

std::vector<std::pair<int,int>> Z::rotatec(std::pair<int,int> lowleft) {
    std::vector<std::pair<int,int>> newcoord;
    int lowx = lowleft.first;
    int lowy = lowleft.second;

    if(pos == 3) pos = 0;
    else pos += 1;
    
    if (pos == 1 || pos == 3){
        newcoord.emplace_back(lowx, lowy);
        newcoord.emplace_back(lowx, lowy + 1);
        newcoord.emplace_back(lowx + 1, lowy + 1);
        newcoord.emplace_back(lowx + 1, lowy + 2);
    }
    
    if (pos == 0 || pos == 2){
        newcoord.emplace_back(lowx, lowy + 1);
        newcoord.emplace_back(lowx + 1, lowy + 1);
        newcoord.emplace_back(lowx + 1, lowy);
        newcoord.emplace_back(lowx + 2, lowy);
    }
    return newcoord; 
 }

std::vector<std::pair<int,int>> Z::rotatecc(std::pair<int,int> lowleft){
    std::vector<std::pair<int, int>> newcoord;
    for(int i = 0; i < 3; ++i){
        newcoord = rotatec(lowleft);
    }
    return newcoord;
}

void Z::updatecoord(std::vector<std::pair<int,int>> newcoord){
    for (int i = 0; i < 4; ++i){
        coord.pop_back();
    } 
    for (auto & c: newcoord){
        coord.emplace_back(c.first, c.second);
    }
}

Z::~Z(){}
