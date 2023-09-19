#ifndef DISPLAY_H
#define DISPLAY_H
#include "generator.h"
#include <vector>
#include "block.h"
#include <memory>
#include "I.h"
#include <string>

class DisplayOurs {
    //Block *b;
    char grid[18][11];
    //void updategrid(std::vector<std::pair<int,int>> coord);
    void displayheader();
    void displayblocks(); // this is where the grid is 
    void displayfooter();
    void cleargrid(std::vector<std::pair<int,int>> coord); 
    std::vector<Block*> allBlocks; // this maybe should not be here - CLaire

    public:
    Generator* g;
    Block *bl;
    Block *currB;
    int player;
    int level;
    int numblocks;
    int currScore;
    int hiScore;
    bool firsttime;
    bool graphics;
    bool text;
    bool blind;
    bool newblockneeded;
    void updategrid(std::vector<std::pair<int,int>> coord);
    int lineclearer(); //clears lines and updates scores
    DisplayOurs(int player, int numblocks = 0, bool blind = false, int level = 1, int currScore = 0, int hiScore = 0, bool graphics = false, bool text = true, bool newblockneeded = false, bool firsttime = true);
    void displayscreen();
    void left();
    void right();
    void down();
    void drop(); //might change to private
    void rotatec();
    void rotatecc();
    void blindboard();
    void force(std::string s);
    void clearfullgrid();
    std::pair<int, int> lowleft(std::vector<std::pair<int,int>> coord);
    ~DisplayOurs();
};

#endif

