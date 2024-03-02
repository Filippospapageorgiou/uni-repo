#include <iostream>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "rubine.h"
#include "engine.h"


using namespace std;

void print_message();

int main(int argc,char *argv[])
{
    srand(time(NULL));

    

    if(argc!=2)
    {
        cout<<"Δώσε το αρχείο για να διαβασώ τον λαβυρινθό."<<endl;
        return 0;
    }

   engine game;
   game.make_maze(argv[1]);

   
   
   //------------------------------------------------
   //Start ncurses
   initscr();
   noecho();
   cbreak();

   print_message();
   
    

   //get scrren size
   int ymax,xmax;
   int h=game.get_heitgh(); int w=game.get_width();
   int x_potter,y_potter,x_rub,y_rub,x_malfoi,y_malfoi;
   ymax=getmaxy(stdscr); xmax=getmaxx(stdscr);

   //set up the window game 
   WINDOW  *win=newwin(h,w,(ymax/2)-(h/2),(xmax/2)-(w/2));
   game.draw_maze(win);
   wrefresh(win);
   //---------------------------------------------------
   
   //characther for players-------------------------------
   start_color();
   init_pair(1,COLOR_CYAN,COLOR_BLACK);
   chtype ch='@' |A_BLINK | init_color(COLOR_YELLOW,255,156,0) | A_BOLD;

   init_pair(2,COLOR_CYAN,COLOR_BLACK);
   chtype ch2='?' |A_BLINK |COLOR_PAIR(2);

   init_pair(3,COLOR_RED,COLOR_MAGENTA);
   chtype ch3='$' |A_BLINK|COLOR_PAIR(3);
   //-----------------------------------------------------

     //set_roubine
    while(mvwinch(win,y_rub=rand()%h+1,x_rub=rand()%w+1)!=' ');
    rubine *rub=new rubine(win,y_rub,x_rub,ch2);
    rub->display();



   //set_player potter
   while(mvwinch(win,y_potter=rand()%h+1,x_potter=rand()%w+1)!=' ');
   game.set_potter(y_potter,x_potter,ch,rub,h,w);
   
   //-------------------------------------------------------
   //set_up malfoi
   while(mvwinch(win,y_malfoi=rand()%h+1,x_malfoi=rand()%w+1)!=' ');
   game.set_malfoi(y_malfoi,x_malfoi,ch3,rub,h,w);
   




     int check_game;

    
        do{
         game.dipslay_char();
         game.make_mv();
         if(rub->check_pos(h,w))
           game.make_malf_map();
         wrefresh(win);
         check_game=game.check_win();
       }while(!game.check_win());
       wclear(win);


   
    refresh();
    attron(COLOR_PAIR(1));
    if(check_game==1)
     printw("\nYOU WIN BIG MAN");
    else if(check_game==2)
     printw("\nYOU LOSE....MALFOI WIN"); 
    attroff(COLOR_PAIR(1));

    getch();
   
    endwin();
   
   

   return 0;

}

void print_message()
{
    printw("YOUR PLAYER -> '@'\n");
    printw("ENEMY -> '$'\n");
    printw("Get the -> '?' TO WIN!\n");
    printw("move with arrows trhow the maze.\n");
    printw("  ^\n");
    printw("<  >\n");
    printw("press anything to start.....");
    getch();
    refresh();
}
