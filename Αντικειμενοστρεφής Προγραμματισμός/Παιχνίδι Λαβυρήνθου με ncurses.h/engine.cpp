#include "rubine.h"
#include <fstream>
#include <vector>
#include <ncurses.h>
#include <string>
#include "potter.h"
#include "malfoi.h"
#include "engine.h"

using namespace std;

void engine::make_maze(char *filename)
{
     //Διαβασε τον λαβυρινθο απο το αρχειο.
         ifstream myfile;
         myfile.open(filename);
         string temp;
          while(!myfile.eof())
         {
          getline(myfile,temp);
          str.push_back(temp);
         }
         myfile.close();
         //Υψος και πλατος πινακα.
         height=str.size();
         width=str[1].length();
         //φταιξε τον πινακα.
         pin=new char*[height];
         for(unsigned long int i=0; i<height; i++)
          pin[i]=new char[width];
          //----------------
           for(unsigned long int i=0; i<height; i++)
           {
            for(unsigned long int j=0; j<width; j++)
             {
               pin[i][j]=str[i][j];
               if(pin[i][j]=='.')
                pin[i][j]=' ';
             }
           }
}

void engine::draw_maze(WINDOW *win)
{
  //Εμφάνισε τον πίνακα στον window
        curwin=win;
        for(unsigned long int i=0; i<=height-1; i++)
        {
         for(unsigned long int j=0; j<width; j++)
          {
           if(i==1)
           {
              mvwprintw(win,i,j," ");
              if(j==0)
               mvwprintw(win,i,j,"*");
              if(j==width-1)
               mvwprintw(win,i,j,"*"); 
           }
           else 
            mvwprintw(win,i,j,"%c",pin[i][j]); 
          }
           cout<<endl;
        }
        wrefresh(win);  
}

void engine::set_malfoi(int y,int x,chtype icon,rubine *rub,int h,int w)
{
  malf=new malfoi(curwin,y,x,icon,h,w);
  malf->set_rub(*rub);
  malf->make_maps(pin);
}


void engine::set_potter(int y,int x,chtype icon,rubine *rub,int h,int w)
{
  poter=new Potter(curwin,y,x,icon,h,w);
  poter->set_rub(*rub);
}

int engine::check_win()
{
  if(poter->check_win())
   return 1;
  else if(malf->check_win())
   return 2;
  else 
   return 0;  
}

void engine::dipslay_char()
{
  poter->display();
  malf->display();
}

void engine::make_mv()
{
  poter->getmv();
  malf->getmv();
}

void engine::make_malf_map()
{
   malf->make_maps(pin);
}