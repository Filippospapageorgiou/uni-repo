#ifndef _POTTER_H
#define _POTTER_H
#include <ncurses.h>
#include "rubine.h"
#include "temp_player.h"

using namespace std;

class Potter:public Player
{
public:
    Potter()
    { }
    Potter(WINDOW *win,int y,int x,chtype c,int h,int w):Player(win,y,x,c,h,w)
    { }
    void display();
    void check_mv();
    int getmv();
    void set_rub(rubine &_rub);
    int check_win();
    int get_y()
    {return y;}
    int get_x()
    {return x;}
private:
   rubine *rub;
   int choice;
};




#endif