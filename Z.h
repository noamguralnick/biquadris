#ifndef Z_H
#define Z_H
#include "block.h"
#include <vector>
#include <utility>

/* J Block is ZZ
               ZZ
this is pos = 0
startx and starty is the coordinates for the space beside the bottom left Z -> this is important when making the display!!!!
also important for rotate functions so don't forget this!!
 */

class Z: public Block{
    int pos;
    char letter;
    std::pair<int, int> lowerleft;
    std::vector<std::pair<int,int>> coord;

    public:
    int levelcreation;
    Z(int level, int startx, int starty, int pos=0, char letter = 'Z'); 
    char getletter() override;
    std::vector<std::pair<int,int>> getcoord() override;
    std::vector<std::pair<int,int>> rotatecc(std::pair<int,int> lowleft) override; 
    std::vector<std::pair<int,int>> rotatec(std::pair<int,int> lowleft) override;
    void updatecoord(std::vector<std::pair<int,int>> newcoord) override;
    int getlevel() override;
    ~Z();
};

#endif 
