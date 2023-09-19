#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "block.h"
#include "generator.h"
#include "I.h"
#include "J.h"
#include "L.h"
#include "O.h"
#include "S.h"
#include "Z.h"
#include "T.h"

Generator::Generator(std::string s1, std::string s2): s1{s1}, s2{s2}{
    srand(time(NULL));
}

Block* Generator::getblock(int level, int player){
    if (level == 0){
        std::string s;
        if (player == 1){
            std::ifstream f;
            std::string p1_file = "biquadris_sequence1.txt";
            f.open(p1_file);
            f >> s;
            ++p1;
        } else {
            std::string p2_file = "biquadris_sequence2.txt";
            std::ifstream f{p2_file};
            f >> s;
            ++p2;
        }
        if (s == "I"){return new I{level, 1, 15};} 
        else if (s == "J"){return new J{level, 1, 15};}
        else if (s == "L"){return new L{level, 1, 15};} 
        else if (s == "O"){return new O{level, 1, 15};} 
        else if (s == "T"){return new T{level, 1, 15};} 
        else if (s == "S"){return new S{level, 1, 15};} 
        else if (s == "Z"){return new Z{level, 1, 15};}
    } 
    else if (level == 1){
        int num = rand() % 6 + 1;
        if (num == 1){return new I{level, 1, 15};}
        else if (num == 2){return new J{level, 1, 15};}
        else if (num == 3){return new L{level, 1, 15};} 
        else if (num == 4){return new O{level, 1, 15};} 
        else if (num == 5){return new T{level, 1, 15};}
        else if (num == 6){
            int num2 = rand() % 2 + 1;
            if (num2 == 1){return new S{level, 1, 15};} 
            else if (num2 == 2){return new Z{level, 1, 15};}
        }
    } 
    else if (level == 2){
        srand(time(NULL));
        int num = rand() % 7 + 1;
        if (num == 1){return new I{level, 1, 15};} 
        else if (num == 2){return new J{level, 1, 15};}
        else if (num == 3){return new  L{level, 1, 15};} 
        else if (num == 4){return new O{level, 1, 15};} 
        else if (num == 5){return new T{level, 1, 15};} 
        else if (num == 6){return new S{level, 1, 15};} 
        else if (num == 7){return new Z{level, 1, 15};}
    } 
    else if (level == 3){
        srand(time(NULL));
        int num = rand() % 9 + 1;
        if (num == 1){return  new I{level, 1, 15};} 
        else if (num == 2){return new J{level, 1, 15};} 
        else if (num == 3){return new L{level, 1, 15};}
        else if (num == 4){return new O{level, 1, 15};}
        else if (num == 5){return new T{level, 1, 15};}
        else if (num == 6){return new S{level, 1, 15};}
        else if (num == 7){return new Z{level, 1, 15};}
        else if (num == 8){return new S{level, 1, 15};}
        else if (num == 9){return new Z{level, 1, 15};}
    } else if (level == 4){ // level 4: level 3 + star in the middle
        srand(time(NULL));
        int num = rand() % 9 + 1;
        if (num == 1){return  new I{level, 1, 15};} 
        else if (num == 2){return new J{level, 1, 15};} 
        else if (num == 3){return new L{level, 1, 15};}
        else if (num == 4){return new O{level, 1, 15};}
        else if (num == 5){return new T{level, 1, 15};}
        else if (num == 6){return new S{level, 1, 15};}
        else if (num == 7){return new Z{level, 1, 15};}
        else if (num == 8){return new S{level, 1, 15};}
        else if (num == 9){return new Z{level, 1, 15};}
    } 
    return nullptr;
}

Block* Generator::forceb(std::string s, int lev){
        if (s == "I" || s == "i"){
            return new I{lev, 1, 15};
        } else if (s == "J" || s == "j"){
            return new J{lev, 1, 15};
        } else if (s == "L" || s == "l"){
            return new L{lev, 1, 15};
        } else if (s == "O" || s == "o"){
            return new O{lev, 1, 15};
        } else if (s == "S" || s == "s"){
            return new S{lev, 1, 15};
        } else if (s == "T" || s == "t"){
            return new T{lev, 1, 15};
        } else if (s == "Z" || s == "z"){
            return new Z{lev, 1, 15};
        }
        return nullptr;
    }

void Generator::setseed(int seed){
    srand(seed);
}
