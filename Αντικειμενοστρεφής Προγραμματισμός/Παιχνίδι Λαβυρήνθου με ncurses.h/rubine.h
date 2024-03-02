#ifndef _RUBINE_H_
#define _RUBINE_H_
#include <ncurses.h>


using namespace std;

class rubine
{
private:
    int y,x;
    chtype icon;
    WINDOW *curwin;
public:
    rubine(WINDOW *win,int _y,int _x,chtype c);
    void display();
    bool check_pos(int h,int w);
    chtype get_icon()
    {return icon;}
    int gety()
    {return y;}
    int getx()
    {return x;}
};



#endif