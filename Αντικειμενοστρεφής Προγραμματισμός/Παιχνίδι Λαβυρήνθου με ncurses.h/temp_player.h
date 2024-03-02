#ifndef _TEMP_PLAYER_H
#define _TEMP_PLAYER_H
#include <ncurses.h>
#include <stdlib.h>

using namespace std;

//abstract class
class Player
{
protected:
    int y,x;
    chtype icon;
    WINDOW * curwin;
    int height,width;
public:
    Player()
    { }
    Player(WINDOW * win, int yc, int xc, chtype c,int _heigth,int _width)
    {
      height=_heigth;
      width=_width;
      curwin = win;
      y = yc;
      x = xc;
      keypad(curwin, true);
      icon = c;
    }
    virtual void display()=0;
    virtual int  getmv()=0;
    virtual int check_win()=0;
    virtual ~Player()
    { }  
};



#endif