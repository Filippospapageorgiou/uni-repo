#ifndef _MALFOI_H
#define _MALFOI_H
#include <iostream>
#include <ncurses.h>
#include "rubine.h"
#include "temp_player.h"
#include <algorithm>

using namespace std;

class malfoi:public Player
{
private:
    rubine *rub;
    int **map;
    int x_rub,y_rub;
public:
    malfoi()
    { }
    malfoi(WINDOW *win,int y,int x,chtype ch,int h,int w):Player(win,y,x,ch,h,w)
    { }
    void set_rub(rubine &_rub);    
    void display();
    void make_maps(char **pin);
    void func(int y,int x,int limit=1);
    int getmv();
    int check_win();
};




#endif