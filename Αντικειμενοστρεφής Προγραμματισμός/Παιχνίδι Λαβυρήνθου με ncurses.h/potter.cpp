#include "rubine.h"
#include <ncurses.h>
#include "rubine.h"
#include "potter.h"

using namespace std;

void Potter::display()
{
  mvwaddch(curwin,y,x,icon);
}

void Potter::check_mv()
    {
        switch(choice)
       {
         case KEY_UP:
             mvwaddch(curwin,y,x,' ');
             y-=1;
             if(mvwinch(curwin,y,x)=='*')
               y+=1;
             break;
          case KEY_DOWN:
             mvwaddch(curwin,y,x,' ');
             y+=1;
             if(mvwinch(curwin,y,x)=='*')
               y-=1;
             break;
          case KEY_LEFT:
            mvwaddch(curwin,y,x,' ');
            x-=1;
            if(mvwinch(curwin,y,x)=='*')
             x+=1;
             break;
          case KEY_RIGHT:
             mvwaddch(curwin,y,x,' ');
             x+=1;
             if(mvwinch(curwin,y,x)=='*')
               x-=1;
             break;    
           default:
             break;
       }
    }

int Potter::getmv()
{
    choice=wgetch(curwin);
    check_mv();
    return choice;
}

void Potter::set_rub(rubine &_rub)
{
   rub=&_rub;
}

int Potter::check_win()
{
    if(mvwinch(curwin,y,x)==rub->get_icon())
     return 1;
    else 
     return 0; 
}
