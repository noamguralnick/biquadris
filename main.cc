#include <iostream> 
#include <fstream>
#include <utility> 
#include <memory>
#include <sstream>
#include "display.h"
#include "generator.h"
#include "block.h"
#include "S.h"
#include "T.h"
#include "J.h"
#include "L.h"
#include "O.h"
#include "I.h"
#include "Z.h"
#include "player.h"
#include "window.h"


using namespace std; 

void readfile(string s, Player &p1, Player &p2, int level, bool heavy){
    if (s == "left") {
            if (p1.isTurn){
                p1.d->left();
                level = p1.d->currB->getlevel();
                if (level > 2){
                    p1.d->down();
                }
                if (heavy){
                    p1.d->down();
                    p1.d->down();
                }
            } else {
                p2.d->left();
                level = p2.d->currB->getlevel();
                if (level > 2){
                    p2.d->down();
                }
                if (heavy){
                    p2.d->down();
                    p2.d->down();
                }
            }
            
        }
        else if (s == "right"){
            if (p1.isTurn){
                p1.d->right();
                level = p1.d->currB->getlevel();
                if (level > 2){
                    p1.d->down();
                }
                if (heavy){
                    p1.d->down();
                    p1.d->down();
                }
            } else {
                p2.d->right();
                level = p2.d->currB->getlevel();
                if (level > 2){
                    p2.d->down();
                }
                if (heavy){
                    p2.d->down();
                    p2.d->down();
                }
            }
        }
        else if (s == "down"){
            if (p1.isTurn){
                p1.d->down();
                level = p1.d->currB->getlevel();
                if (level > 2){
                    p1.d->down();
                }
            } else {
                p2.d->down();
                level = p2.d->currB->getlevel();
                if (level > 2){
                    p2.d->down();
                }
            }
        }
        else if (s == "clockwise"){
            if (p1.isTurn){
                p1.d->rotatec();
                level = p1.d->currB->getlevel();
                if (level > 2){
                    p1.d->down();
                }
            } else {
                p2.d->rotatecc();
                level = p2.d->currB->getlevel();
                if (level > 2){
                    p2.d->down();
                }
            }
        }
        else if (s == "counterclockwise"){
            if (p1.isTurn){
                p1.d->rotatecc();
                level = p1.d->currB->getlevel();
                if (level > 2){
                    p1.d->down();
                }
            } else {
                p2.d->rotatecc();
                level = p1.d->currB->getlevel();
                if (level > 2){
                    p2.d->down();
                }
            }
        }
        else if (s == "drop"){
            if (p1.isTurn){
                p1.d->drop();
                int linescleared = p1.d->lineclearer();
                p1.currentScore(linescleared);
                p1.isTurn = false;
                p2.isTurn = true;
                heavy = false;
                if (linescleared >= 2){
                    cout << "Please select one of the following actions: " << endl;
                    cout << "Blind" << endl;
                    cout << "Heavy" << endl;
                    cout << "Force (please enter the forced block as well)" << endl;
                    cin >> s;
                    if (s == "Blind" || s == "blind"){
                        p2.d->blindboard();
                    } else if (s == "Heavy" || s == "heavy"){
                        heavy = true;
                    } else if (s == "Force" || s == "force"){
                        cin >> s;
                        p2.d->force(s);
                    }

                    }
                } else {
                p2.d->drop();
                int linescleared = p2.d->lineclearer();
                p2.currentScore(linescleared);
                p2.isTurn = false;
                p1.isTurn = true;
                heavy = false;
                if (linescleared >= 2){
                    cout << "Please select one of the following actions: " << endl;
                    cout << "Blind" << endl;
                    cout << "Heavy" << endl;
                    cout << "Force (please enter the forced block as well)" << endl;
                    cin >> s;
                    if (s == "Blind" || s == "blind"){
                        p1.d->blindboard();
                    } else if (s == "Heavy" || s == "heavy"){
                        heavy = true;
                    } else if (s == "Force" || s == "force"){
                        cin >> s;
                        p1.d->force(s);
                    }
                }
            }
        }
        else if (s == "levelup"){
            if (p1.isTurn){
                p1.levelup();
            } else {
                p2.levelup();
            }
        }
        else if (s == "leveldown"){
            if(p1.isTurn){
                p1.leveldown();
            } else {
                p2.leveldown();
            }
        } 
        else if (s == "I"){
            p1.d->force("I");
        }
        else if (s == "J"){
            p1.d->force("J");
        } 
        else if (s == "L"){
            p1.d->force("L");
        }
        else if (s == "O"){
            p1.d->force("O");
        }
        else if (s == "S"){
            p1.d->force("S");
        }
        else if (s == "T"){
            p1.d->force("T");
        }
        else if (s == "Z"){
            p1.d->force("Z");
        }
        else if (s == "restart"){
            if (p1.isTurn){
                p1.d->clearfullgrid();
            } else {
                p2.d->clearfullgrid();
            }
        }
}

int main(int argc, char **argv){
    Xwindow w;
  
    w.fillRectangle(100, 100, 220, 360, 2);
    w.fillRectangle(400, 100, 220, 360, 2);

    w.drawString(100, 70, "Level:    ");
    w.drawString(100, 90, "Score:    ");

    int gridSize = 20; 
   // Draw grid lines
    w.drawGridLines(100, 100 ,gridSize);
    w.drawGridLines(400, 100 ,gridSize);

    w.drawString(400, 70, "Level:    ");
    w.drawString(400, 90, "Score:    ");

    int level;
    bool heavy = false;
    bool graphics = true;
    bool blind = false;
    DisplayOurs *d1 = new DisplayOurs{1};
    DisplayOurs *d2 = new DisplayOurs{2};
    Player p1 = {true, d1};
    Player p2 = {false, d2};
    string argument;
    string s;
    if (argc > 2){
        for (int i = 0; i < argc; ++i){
            istringstream ss1(argv[i]);
            ss1 >> argument;
            if (argument == "-text"){
                graphics = false;
            } else if (argument == "-seed"){
                istringstream ss2(argv[i+1]);
                int seed;
                ss2 >> seed;
                p1.d->g->setseed(seed);
                ++i;
            } else if (argument == "-scriptfile1"){
                istringstream ss3(argv[i+1]);
                string file1;
                ss3 >> file1;
                p1.d->g->s1 = file1;
                ++i;
            } else if (argument == "-scriptfile2"){
                istringstream ss4(argv[i+1]);
                string file2;
                ss4 >> file2;
                p1.d->g->s2 = file2;
                ++i;
            } else if (argument == "-startlevel"){
                istringstream ss5(argv[i+1]);
                int lev = 0;
                ss5 >> lev;
                p1.d->currB->levelcreation = lev;
                p1.d->level = lev;
                p2.d->currB->levelcreation = lev;
                p2.d->level = lev;
            }
        }
    }
    p1.d->displayscreen();
    p2.d->displayscreen();
    while (cin >> s){
        if (s == "left") {
            if (p1.isTurn){
                p1.d->left();
                level = p1.d->currB->getlevel();
                if (level > 2){
                    p1.d->down();
                }
                if (heavy){
                    p1.d->down();
                    p1.d->down();
                }
            } else {
                p2.d->left();
                level = p2.d->currB->getlevel();
                if (level > 2){
                    p2.d->down();
                }
                if (heavy){
                    p2.d->down();
                    p2.d->down();
                }
            }
            
        }
        else if (s == "right"){
            if (p1.isTurn){
                p1.d->right();
                level = p1.d->currB->getlevel();
                if (level > 2){
                    p1.d->down();
                }
                if (heavy){
                    p1.d->down();
                    p1.d->down();
                }
            } else {
                p2.d->right();
                level = p2.d->currB->getlevel();
                if (level > 2){
                    p2.d->down();
                }
                if (heavy){
                    p2.d->down();
                    p2.d->down();
                }
            }
        }
        else if (s == "down"){
            if (p1.isTurn){
                p1.d->down();
                level = p1.d->currB->getlevel();
                if (level > 2){
                    p1.d->down();
                }
            } else {
                p2.d->down();
                level = p2.d->currB->getlevel();
                if (level > 2){
                    p2.d->down();
                }
            }
        }
        else if (s == "clockwise"){
            if (p1.isTurn){
                p1.d->rotatec();
                level = p1.d->currB->getlevel();
                if (level > 2){
                    p1.d->down();
                }
            } else {
                p2.d->rotatecc();
                level = p2.d->currB->getlevel();
                if (level > 2){
                    p2.d->down();
                }
            }
        }
        else if (s == "counterclockwise"){
            if (p1.isTurn){
                p1.d->rotatecc();
                level = p1.d->currB->getlevel();
                if (level > 2){
                    p1.d->down();
                }
            } else {
                p2.d->rotatecc();
                level = p1.d->currB->getlevel();
                if (level > 2){
                    p2.d->down();
                }
            }
        }
        else if (s == "drop"){
            if (p1.isTurn){
                p1.d->drop();
                int linescleared = p1.d->lineclearer();
                p1.currentScore(linescleared);
                p1.isTurn = false;
                p2.isTurn = true;
                heavy = false;
                if (p1.d->blind){
                    p1.d->blind = false;
                }
                if (linescleared >= 2){
                    cout << "Please select one of the following actions: " << endl;
                    cout << "Blind" << endl;
                    cout << "Heavy" << endl;
                    cout << "Force (please enter the forced block as well)" << endl;
                    cin >> s;
                    if (s == "Blind" || s == "blind"){
                        p2.d->blind = true;
                    } else if (s == "Heavy" || s == "heavy"){
                        heavy = true;
                    } else if (s == "Force" || s == "force"){
                        cin >> s;
                        p2.d->force(s);
                    }

                }
                } else {
                p2.d->drop();
                int linescleared = p2.d->lineclearer();
                p2.currentScore(linescleared);
                p2.isTurn = false;
                p1.isTurn = true;
                heavy = false;
                if (p2.d->blind){
                    p2.d->blind = false;
                }
                if (linescleared >= 2){
                    cout << "Please select one of the following actions: " << endl;
                    cout << "Blind" << endl;
                    cout << "Heavy" << endl;
                    cout << "Force (please enter the forced block as well)" << endl;
                    cin >> s;
                    if (s == "Blind" || s == "blind"){
                        p1.d->blind = true;
                    } else if (s == "Heavy" || s == "heavy"){
                        heavy = true;
                    } else if (s == "Force" || s == "force"){
                        cin >> s;
                        p1.d->force(s);
                    }
                }
            }
        }
        else if (s == "levelup"){
            if (p1.isTurn){
                p1.levelup();
            } else {
                p2.levelup();
            }
        }
        else if (s == "leveldown"){
            if(p1.isTurn){
                p1.leveldown();
            } else {
                p2.leveldown();
            }
        } 
        else if (s == "I"){
            if(p1.isTurn){
                p1.d->force("I");
            } else {
                p2.d->force("I");
            }
        }
        else if (s == "J"){
            if(p1.isTurn){
                p1.d->force("J");
            } else {
                p2.d->force("J");
            }
        } 
        else if (s == "L"){
            if(p1.isTurn){
                p1.d->force("L");
            } else {
                p2.d->force("L");
            }
        }
        else if (s == "O"){
            if(p1.isTurn){
                p1.d->force("O");
            } else {
                p2.d->force("O");
            }
        }
        else if (s == "S"){
            if(p1.isTurn){
                p1.d->force("S");
            } else {
                p2.d->force("S");
            }
        }
        else if (s == "T"){
            if(p1.isTurn){
                p1.d->force("T");
            } else {
                p2.d->force("T");
            }
        }
        else if (s == "Z"){
            if(p1.isTurn){
                p1.d->force("Z");
            } else {
                p2.d->force("Z");
            }
        }
        else if (s == "restart"){
            if (p1.isTurn){
                p1.d->clearfullgrid();
            } else {
                p2.d->clearfullgrid();
            }
        }
        else if (s == "sequence"){
            string filename;
            cin >> filename;
            ifstream f{filename};
            string command;
            while (f >> command) readfile(command, p1, p2, level, heavy);
        }
            p1.d->displayscreen();
            p2.d->displayscreen();
    }
}

