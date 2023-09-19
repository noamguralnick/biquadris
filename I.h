#ifndef I_H
#define I_H
#include "block.h"
#include <vector>
#include <utility>
#include <iostream>

//I is IIII
//this is pos 0, and startx and starty are the left-most I.
//lowerleft is set to startx and starty for this block

class I: public Block{
    int pos;
    char letter;
    std::pair<int,int> lowerleft;
    std::vector<std::pair<int,int>> coord;

    public:
    int levelcreation;
    I(int level, int startx, int starty, int pos = 0, char letter = 'I'); 
    char getletter() override;
    std::vector<std::pair<int,int>> getcoord() override;
    std::vector<std::pair<int,int>> rotatecc(std::pair<int,int> lowleft) override; 
    std::vector<std::pair<int,int>> rotatec(std::pair<int,int> lowleft) override;
    void updatecoord(std::vector<std::pair<int,int>> newcoord) override;
    int getlevel() override;
    ~I();
};


#endif 

