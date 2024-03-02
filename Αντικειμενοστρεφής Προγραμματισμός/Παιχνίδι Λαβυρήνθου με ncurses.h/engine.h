#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <ncurses.h>
#include "potter.h"
//#include "rubine.h"
#include "malfoi.h"

using namespace std;

class engine
{
private:
    char **pin;
    WINDOW  *curwin;
    vector<string> str;
    int height,width;
    Potter *poter;
    malfoi *malf;
public:
     engine()
     { }
     void make_map_malf();
     void make_maze(char *filename);
     void draw_maze(WINDOW *win);
     void set_potter(int y,int x,chtype icon,rubine *rub,int h,int w);
     void set_malfoi(int y,int x,chtype icon,rubine *rub,int h,int w);
     void make_malf_map();
     void dipslay_char();
     void make_mv();
     int check_win();
     int get_heitgh()
     {return height;}
     int get_width()
     {return width;}
     char **get_map()
     { return pin;}
};



#endif



