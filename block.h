#ifndef BLOCK_H
#define BLOCK_H
#include <utility>
#include <vector>

class Block {
    int pos;
    char letter;
    std::pair<int,int> lowerleft;
    std::vector<std::pair<int,int>> coord;//a vector holding all pairs of coordinates in the block

    public:
    int levelcreation;
    virtual char getletter() = 0;
    virtual std::vector<std::pair<int,int>> getcoord() = 0;
    virtual std::vector<std::pair<int,int>> rotatecc(std::pair<int,int> lowleft) = 0; //counterclock
    virtual std::vector<std::pair<int,int>> rotatec(std::pair<int,int> lowleft) = 0; //clockwise
    virtual ~Block();
    virtual void updatecoord(std::vector<std::pair<int,int>> newcoord) = 0;
    virtual int getlevel() = 0;
    friend class DisplayOurs;
};

#endif 

