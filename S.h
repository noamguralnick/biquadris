#ifndef S_H
#define S_H
#include "block.h"
#include <map>

class S: public Block{
    int pos;
    char letter;
    std::pair<int,int> lowerleft;
    std::vector<std::pair<int,int>> coord;

    public:
    int levelcreation;
    S(int level, int startx, int starty, int pos = 0, char letter = 'S'); 
    char getletter() override;
    std::vector<std::pair<int,int>> getcoord() override;
    std::vector<std::pair<int,int>> rotatecc(std::pair<int,int> lowleft) override; 
    std::vector<std::pair<int,int>> rotatec(std::pair<int,int> lowleft) override;
    void updatecoord(std::vector<std::pair<int,int>> newcoord) override;
    int getlevel() override;
    ~S();
};


#endif 
