#ifndef GENERATOR_H
#define GENERATOR_H
#include "block.h"
#include <iostream>
#include <string>

class Generator{

    public:
    int p1;
    int p2;
    std::string s1;
    std::string s2; 
    Generator(std::string s1 = "biquadris_sequence1.txt", std::string s2 = "biquadris_sequence2.txt");
    Block* getblock(int level, int player);
    Block* forceb(std::string s, int lev);
    void setseed(int seed);
};

#endif
