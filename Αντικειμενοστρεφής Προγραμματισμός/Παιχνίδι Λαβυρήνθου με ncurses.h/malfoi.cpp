#include <ncurses.h>
#include "malfoi.h"
#include <algorithm>
#include "rubine.h"

using namespace std;

void malfoi::display()
{
  mvwaddch(curwin,y,x,icon);
}

void malfoi::set_rub(rubine &_rub)
{
   rub=&_rub;
}

void malfoi::make_maps(char **pin)
{
    map=new int*[height];
    //ftaije to xarti
    for(int i=0; i<height; i++)
    {
      map[i]=new int[width];
    }
    //these tis thesis
    for(int i=0; i<height; i++)
    {
      for(int j=0; j<width; j++)
       if(pin[i][j]=='*')
        map[i][j]=900;
       else 
        map[i][j]=0;
    }
      //---------------   
      map[y][x]=800;
      y_rub=rub->gety();
      x_rub=rub->getx();
      map[y_rub][x_rub]=1;
  
  
  //ftiaje diadromi
  func(y_rub,x_rub);


}

void malfoi::func(int _y,int _x,int limit)
{
  if(map[_y-1][_x]==800 || map[_y][_x+1]==800 || map[_y+1][_x]==800 || map[_y][_x-1]==800)
   return ;
 
  if(map[_y-1][_x]!=900 && (map[_y-1][_x]==0 || map[_y-1][_x]==limit))
  {
    map[_y-1][_x]=limit;
    func(_y-1,_x,limit+1);
  }
  if(map[_y][_x+1]!=900 && (map[_y][_x+1]==0 || map[_y][_x+1]==limit))
  {
    map[_y][_x+1]=limit;
    func(_y,_x+1,limit+1);
  }
  if(map[_y+1][_x]!=900 && (map[_y+1][_x]==0 || map[_y+1][_x]==limit))
  {
    map[_y+1][_x]=limit;
    func(_y+1,_x,limit+1);
  }
  if(map[_y][_x-1]!=900 && (map[_y][_x-1]==0 || map[_y][_x-1]==limit))
  {
    map[_y][_x-1]=limit;
    func(_y,_x-1,limit+1);
  }

}

int malfoi::getmv()
{
  mvwaddch(curwin,y,x,' ');
  static int myMin;
  int min1,min2;
  int a,b,c,d;
  a=map[y+1][x];
  b=map[y][x+1];
  c=map[y-1][x];
  d=map[y][x-1];
  min1=min(a,b);
  min2=min(c,d);
  myMin=min(min1,min2);

  if(myMin==a)
  {
    y=y+1;
    x=x;
  }
  else if(myMin==b)
  {
    y=y;
    x=x+1;
  }
  else if(myMin==c)
  {
    y=y-1;
    x=x;
  }
  else if(myMin==d)
  {
    y=y;
    x=x-1;
  }

  return 1;
}

int malfoi::check_win()
{
   if(mvwinch(curwin,y,x)==rub->get_icon())
     return 1;
    else 
     return 0; 
}