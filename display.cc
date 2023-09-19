#include "display.h"
#include "generator.h"
#include "I.h"
#include <fstream>
#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <string>

DisplayOurs::DisplayOurs(int player, int numblocks, bool blind, int level, int currScore, int hiScore, bool graphics, bool text, bool newblockneeded, bool firsttime): player{player}, numblocks{numblocks}, blind{blind}, level{level}, currScore{currScore}, hiScore{hiScore}, firsttime{firsttime}, graphics{graphics}, text{text}, newblockneeded(newblockneeded){
    for (int i = 0; i < 18; ++i)
    {
        for (int j = 0; j < 11; ++j)
        {
            grid[i][j] = ' ';
        }
    }
    // creating generator
    currB = g->getblock(level, player);
    bl = g->getblock(level, player);
}

void DisplayOurs::updategrid(std::vector<std::pair<int, int>> coord)
{ // NEW - takes in coord
    char let = currB->getletter();
    for (auto &c : coord)
    {
        grid[c.second - 1][c.first - 1] = let;
    }
}

void DisplayOurs::displayscreen()
{
    displayheader();
    if (blind){
        blindboard();
    } else {
        displayblocks();
    }
    displayfooter();
}

void DisplayOurs::displayheader()
{
    std::cout << "Level:          "
              << level << std::endl;
    std::cout << "Current Score:  "
              <<  currScore << std::endl;
    std::cout << "High Score:     "
              <<  hiScore << std::endl;
    std::cout << "-----------" << std::endl;
}

void DisplayOurs::displayblocks()
{
    if (newblockneeded){
        numblocks ++;
        currB = bl;
        bl = g->getblock(level, player);
        newblockneeded = false;
        allBlocks.emplace_back(currB);
        if (numblocks%5 == 0 && level == 4){
            for (int i = 0; i < 18; ++i){
                if (grid[i][5] != ' '){
                    continue;
                } else {
                    grid[i][5] = '*';
                    break;
                }
            }
        }
    }
    updategrid(currB->getcoord());
    for (int i = 0; i < 7; ++i)
    {
        std::cout << "_ ";
    }
    std::cout << std::endl;
    for (int i = 17; i > -1; --i)
    {
        std::cout << '|';
        for (int j = 0; j < 11; ++j)
        {
            std::cout << grid[i][j];
        }
        std::cout << '|' << std::endl;
    }
    for (int i = 0; i < 7; ++i)
    {
        if (i == 6)
            std::cout << "- " << std::endl;
        else
            std::cout << "- ";
    }
}

void DisplayOurs::displayfooter()
{
    std::cout << "-----------" << std::endl;
    std::cout << "Next: " << std::endl;

    std::vector<std::pair<int, int>> newcoord = bl->getcoord();

    int minRow = newcoord[0].second;
    int minCol = newcoord[0].first;

    // Find the maximum row and column
    int maxRow = newcoord[0].second;
    int maxCol = newcoord[0].first;

    for (const auto &c : newcoord)
    {
        int row = c.second;
        int col = c.first;

        // Update the minimum and maximum row and column
        minRow = std::min(minRow, row);
        minCol = std::min(minCol, col);
        maxRow = std::max(maxRow, row);
        maxCol = std::max(maxCol, col);
    }

    // Print the shape
    for (int i = maxRow; i >= minRow; --i)
    {
        for (int j = minCol; j <= maxCol; ++j)
        {
            bool isBlock = false;
            for (const auto &c : bl->getcoord())
            {
                int row = c.second;
                int col = c.first;
                if (row == i && col == j)
                {
                    isBlock = true;
                    break;
                }
            }
            std::cout << (isBlock ? bl->getletter() : ' ');
        }
        std::cout << std::endl;
    }
}

int DisplayOurs::lineclearer(){
    int numblocks = 0;
    int linescleared = 0;
    bool rowfull = true;
    for (int i = 0; i < 18; ++i){
        rowfull = true;
        for (int j = 0; j < 11; ++j)
        {
            if (grid[i][j] == ' ')
            {
                rowfull = false;
                break;
            }
        }
        if (rowfull){
            linescleared++;
            for (int x = i; x < 17; ++x)
            {
                std::swap(grid[x], grid[x + 1]);
            }
            for (int j = 0; j < 11; ++j)
            {
                grid[17][j] = ' ';
            }
            --i;
        }
    }
    return linescleared;
}

void DisplayOurs::cleargrid(std::vector<std::pair<int,int>> coord){
    for (auto & c: coord){
        grid[c.second -1][c.first -1] = ' ';
    }
}

void DisplayOurs::left(){
    bool cango = true;
    std::vector<std::pair<int,int>> coord = currB->getcoord();
    cleargrid(coord);
    std::vector<std::pair<int,int>> newcoord;
    for (auto & c: coord){
        newcoord.emplace_back(c.first -1, c.second);
    }
    for (auto &c: newcoord){
        if (grid[c.second-1][c.first-1] != ' '){
            cango = false;
        } if (c.first <= 0){
            cango = false;
        }
    } 
    if (cango){
        currB->updatecoord(newcoord);
    }
    updategrid(currB->getcoord());
}

void DisplayOurs::right(){
    bool cango = true;
    std::vector<std::pair<int,int>> coord = currB->getcoord();
    cleargrid(coord);
    std::vector<std::pair<int,int>> newcoord;
    for (auto & c: coord){
        newcoord.emplace_back(c.first +1, c.second);
    }
    for (auto &c: newcoord){
        if (grid[c.second-1][c.first-1] != ' '){
            cango = false;
        } if (c.first >= 12 || c.first <= 1){ //delete c.second <= 1 after rotate implementation
            cango = false;
        }
    } 
    if (cango){
        currB->updatecoord(newcoord);
    }
    updategrid(currB->getcoord());
}

void DisplayOurs::down(){
    bool cango = true;
    std::vector<std::pair<int,int>> coord = currB->getcoord();
    cleargrid(coord);
    std::vector<std::pair<int,int>> newcoord;
    for (auto & c: coord){
        newcoord.emplace_back(c.first, c.second -1);
    }
    for (auto &c: newcoord){
        if (grid[c.second-1][c.first-1] != ' '){
            cango = false;
        }
        if (c.second < 1){
            cango = false;
        }
    } 
    if (cango){
        currB->updatecoord(newcoord);
    }
    updategrid(currB->getcoord());
}


void DisplayOurs::drop(){
    for(int i = 0; i < 18; ++i){
        down();
    }
    newblockneeded = true;
}

void DisplayOurs::rotatec(){
    bool cango = true;
    std::vector<std::pair<int,int>> coord = currB->getcoord();
    cleargrid(coord);
    std::pair<int,int> lowerleft = lowleft(coord);
    std::vector<std::pair<int,int>> newcoord = currB->rotatec(lowerleft);
    for (auto &c: newcoord){
        if (grid[c.second-1][c.first-1] != ' '){
            cango = false;
        }
        if (c.second < 1){
            cango = false;
        }
    } 
    if (cango){
        currB->updatecoord(newcoord);
    }
    updategrid(currB->getcoord());
}

void DisplayOurs::rotatecc(){
    bool cango = true;
    std::vector<std::pair<int,int>> coord = currB->getcoord();
    cleargrid(coord);
    std::pair<int,int> lowerleft = lowleft(coord);
    std::vector<std::pair<int,int>> newcoord = currB->rotatecc(lowerleft);
    for (auto &c: newcoord){
        if (grid[c.second-1][c.first-1] != ' '){
            cango = false;
        }
        if (c.second < 1){
            cango = false;
        }
    } 
    if (cango){
        currB->updatecoord(newcoord);
    }
    updategrid(currB->getcoord());
}

std::pair<int, int> DisplayOurs::lowleft(std::vector<std::pair<int,int>> coord){
    int lowx = coord[0].first;
    int lowy = coord[0].second;
    for (auto & c: coord){
        if (c.second < lowy && c.first <= lowx){
            lowx = c.first;
            lowy = c.second;
        }
    }
    std::pair<int, int> result = {lowx, lowy};
    return result;
}

void DisplayOurs::blindboard(){
    if (newblockneeded){
        currB = bl;
        bl = g->getblock(level, player);
        newblockneeded = false;
        allBlocks.emplace_back(currB);
    }
    updategrid(currB->getcoord());
    for (int i = 0; i < 7; ++i)
    {
        std::cout << "_ ";
    }
    std::cout << std::endl;
    for (int i = 17; i > 11; --i)
    {
        std::cout << '|';
        for (int j = 0; j < 11; ++j)
        {
            std::cout << grid[i][j];
        }
        std::cout << '|' << std::endl;
    }
    for (int i = 11; i > 1; --i)
    {
        std::cout << '|';
        for (int j = 0; j < 2; ++j)
        {
            std::cout << grid[i][j];
        }
        for (int j = 2; j < 9; ++j){
            std::cout << '?';
        }
        for (int j = 9; j < 11; ++j){
            std::cout << grid[i][j];
        }
        std::cout << '|' << std::endl;
    }
    for (int i = 2; i > -1; --i)
    {
        std::cout << '|';
        for (int j = 0; j < 11; ++j)
        {
            std::cout << grid[i][j];
        }
        std::cout << '|' << std::endl;
    }
    for (int i = 0; i < 7; ++i)
    {
        if (i == 6)
            std::cout << "- " << std::endl;
        else
            std::cout << "- ";
    }
}

void DisplayOurs::force(std::string s){
    cleargrid(currB->getcoord());
    currB = g->forceb(s, level);
}

void DisplayOurs::clearfullgrid(){
    for (int i = 0; i < 18; ++i)
    {
        for (int j = 0; j < 11; ++j)
        {
            grid[i][j] = ' ';
        }
    }
}

DisplayOurs::~DisplayOurs()
{}
