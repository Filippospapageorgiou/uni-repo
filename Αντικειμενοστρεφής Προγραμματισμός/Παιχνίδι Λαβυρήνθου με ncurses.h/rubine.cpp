#include "rubine.h"
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

rubine::rubine(WINDOW *win,int _y,int _x,chtype c)
{
   srand(time(NULL));
    curwin=win;
    y=_y;
    x=_x;
    start_color();
    icon=c;
}

void rubine::display()
{
    mvwaddch(curwin,y,x,icon);
}

bool rubine::check_pos(int h,int w)
{
        int pos=rand()%100+1;
        if(pos<=3)
        {
           mvwaddch(curwin,y,x,' ');
           while(mvwinch(curwin,y=rand()%h+1,x=rand()%w+1)!=' ');
           mvwaddch(curwin,y,x,icon);
           return true;
        }
        return false;
}