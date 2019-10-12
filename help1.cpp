
/* triangle.c */
#include <bits/stdc++.h>
#include <curses.h>
#include <stdlib.h>

using namespace std;
#define ITERMAX 10000
using namespace chrono;
using namespace this_thread;
void statWind(int h, int w)
{

    WINDOW *win = newwin(26, 3, h, w);
    scrollok(win, TRUE);
    for (int row = 0; row < 26; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            mvwaddch(win, row, col, ' ' | COLOR_PAIR(2));
        }
    }
    for (int i = 0; i < 26; i++)
    {
        mvwaddch(win, i, 1, 'a' + i | COLOR_PAIR(2));
    }

    wrefresh(win);
}
void rotorWind(int h, int w)
{
    WINDOW *win = newwin(26, 10, h, w);
    scrollok(win, TRUE);

    for (int row = 0; row < 26; row++)
    {
        for (int col = 0; col < 10; col++)
        {
            mvwaddch(win, row, col, ' ' | COLOR_PAIR(2));
        }
    }
    for (int i = 0; i < 26; i++)
    {
        mvwaddch(win, i, 1, 'a' + i | COLOR_PAIR(2));
        mvwaddch(win, i, 8, 'a' + ((i + 5) % 26) | COLOR_PAIR(2));
    }

    wrefresh(win);
}
void printingscr(){
    int maxlines, maxcols;
    initscr();
    cbreak();
    clear();
    getmaxyx(stdscr, maxlines, maxcols);
    printw("Size of screen is : %d  X  %d\n", maxlines, maxcols);
    wrefresh(stdscr);

    start_color();
    init_pair(2, COLOR_YELLOW, COLOR_GREEN);
    init_pair(3, COLOR_CYAN, COLOR_BLUE);
    init_pair(4, COLOR_BLACK, COLOR_WHITE);
    init_pair(5, COLOR_RED, COLOR_MAGENTA);
    mvaddstr(maxlines, 0, "Press any key to quit");


}
int main()
{
    //Static window
    printingscr();
    statWind(0, 0);
    statWind(5, 46);

    //Rotor window
    rotorWind(5, 10);
    rotorWind(5, 22);
    rotorWind(5, 34);
    /* done */


    refresh();

    char ch = getch();
    switch (ch)
    {
    case KEY_UP:
    case 'w':
    case 'W':
        cout << ch << endl;
        break;
    }


    endwin();

    exit(0);
}