#include "block.h"
#include "O.h"
#include <vector>
#include <utility>

O::O(int level, int startx, int starty, int pos, char letter):
levelcreation{level}, pos{pos}, letter{letter}, lowerleft{startx, starty} {
    coord.emplace_back(startx,starty);
    coord.emplace_back(startx + 1,starty);
    coord.emplace_back(startx,starty + 1);
    coord.emplace_back(startx + 1,starty + 1);
}

char O::getletter() {return letter;}

int O::getlevel() {return levelcreation;}

std::vector<std::pair<int,int>> O::getcoord() {return coord;}

std::vector<std::pair<int,int>> O::rotatec(std::pair<int,int> lowleft) {
    return coord;
}

std::vector<std::pair<int,int>> O::rotatecc(std::pair<int,int> lowleft){
    return coord;
}

void O::updatecoord(std::vector<std::pair<int,int>> newcoord){
    for (int i = 0; i < 4; ++i){
        coord.pop_back();
    } 
    for (auto & c: newcoord){
        coord.emplace_back(c.first, c.second);
    }
}

O::~O(){} 

