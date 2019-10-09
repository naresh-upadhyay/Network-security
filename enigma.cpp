#include <bits/stdc++.h>
#include <curses.h>
#define dqmap deque<map<int, int>>
using namespace std;
using namespace chrono;
using namespace this_thread;
void statWind(int h, int w)
{

    WINDOW *win = newwin(26, 3, h, w);

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
void rotorWind(int h, int w, dqmap dmap)
{
    WINDOW *win = newwin(26, 10, h, w);

    for (int row = 0; row < 26; row++)
    {
        for (int col = 0; col < 10; col++)
        {
            mvwaddch(win, row, col, ' ' | COLOR_PAIR(2));
        }
    }
    for (int i = 0; i < 26; i++)
    {
        auto c = dmap[i].begin();
        mvwaddch(win, i, 1, 'a' + (c->first) | COLOR_PAIR(2));
        mvwaddch(win, i, 8, 'a' + (c->second) | COLOR_PAIR(2));
    }

    wrefresh(win);
}
void installMachine(dqmap dqmR1, dqmap dqmR2, dqmap dqmR3)
{

    statWind(5, 5);
    statWind(5, 46);
    //Rotor window
    rotorWind(5, 10, dqmR1);
    rotorWind(5, 22, dqmR2);
    rotorWind(5, 34, dqmR3);
}
void resetscr()
{
    int y, x;
    attron(COLOR_PAIR(4));
    for (y = 0; y < LINES; y++)
    {
        mvhline(y, 0, ' ', COLS);
    }
    attroff(COLOR_PAIR(4));
}
void printingscr()
{
    initscr();
    //cbreak();
    clear();

    start_color();
    init_pair(2, COLOR_YELLOW, COLOR_GREEN);
    init_pair(3, COLOR_CYAN, COLOR_BLUE);
    init_pair(4, COLOR_BLACK, COLOR_WHITE);
    init_pair(5, COLOR_RED, COLOR_MAGENTA);
    init_pair(6, COLOR_WHITE, COLOR_RED);
    resetscr();
}

class EnigmaMachine
{
    dqmap dqmR1, dqmR2, dqmR3, statdqm;
    dqmap ddqmR1, ddqmR2, ddqmR3, dstatdqm;
    unordered_set<int> rval1, rval2, rval3, statval;
    int countr1, countr2, countr3;

public:
    EnigmaMachine()
    {
        rval1 = randomgenrator();
        rval2 = randomgenrator();
        rval3 = randomgenrator();
        statval = randomgenrator();
        mapingRotor(dqmR1, rval1);
        mapingRotor(dqmR2, rval2);
        mapingRotor(dqmR3, rval3);
        statMaping(statdqm, statval);
        countr1 = 0;
        countr2 = 0;
        countr3 = 0;
        ddqmR1 = dqmR1;
        ddqmR2 = dqmR2;
        ddqmR3 = dqmR3;
        //Static window
        printingscr();
        installMachine(dqmR1, dqmR2, dqmR3);

        //printrotors(statdqm);
    }
    void printrotors(dqmap pdq)
    {
        cout << "sz" << pdq.size() << endl;
        for (int i = 0; i < pdq.size(); i++)
        {
            cout << pdq[i].begin()->first << " " << pdq[i].begin()->second << endl;
        }
    }
    unordered_set<int> randomgenrator()
    {
        unordered_set<int> rand1;
        while (rand1.size() < 26)
        {
            rand1.insert(rand() % 26);
        }
        return rand1;
    }
    void resetMachine()
    {
        dqmR1 = ddqmR1;
        dqmR2 = ddqmR2;
        dqmR3 = ddqmR3;
        resetscr();
        installMachine(dqmR1, dqmR2, dqmR3);
    }
    void statMaping(dqmap &mapR, unordered_set<int> randumval)
    {
        auto it = randumval.begin();
        auto itr = randumval.begin();
        map<int, int> temp, temp2;
        advance(itr, 13);
        while (mapR.size() < 26)
        {
            temp.emplace(*it, *itr);
            mapR.push_back(temp);
            temp2.emplace(*itr, *it);
            mapR.push_back(temp2);
            it++;
            itr++;
            temp.erase(temp.begin());
            temp2.erase(temp2.begin());
        }
    }
    void mapingRotor(dqmap &mapR, unordered_set<int> randumval)
    {
        int k = 0;
        auto it = randumval.begin();
        map<int, int> temp;
        while (mapR.size() < 26)
        {
            temp.emplace((k % 26), (*it));
            mapR.push_back(temp);
            k++;
            it++;
            temp.erase(temp.begin());
        }
    }
    int position(dqmap mapR, int val)
    {
        int pos = 0;
        for (int i = 0; i < 26; i++)
        {
            //map<int,int> mp=mapR[i];
            if (mapR[i].begin()->second == val)
            {
                pos = i;
            }
        }
        return pos;
    }

    int rposition(dqmap mapR, int val)
    {
        int pos = 0;
        for (int i = 0; i < 26; i++)
        {
            if (mapR[i].begin()->first == val)
            {
                pos = i;
            }
        }
        return pos;
    }
    void blinkcolr(int x1, int x2, int index)
    {
        for (int x = x1; x <= x2; x++)
        {
            attron(COLOR_PAIR(5));
            mvaddch(index + 5, x, '>'); //mvgetch(index + 5, x)
            attroff(COLOR_PAIR(5));
            move(index + 5, x);
            refresh();
        }
        installMachine(dqmR1, dqmR2, dqmR3);
    }
    void blinkcolrrev(int x1, int x2, int index)
    {
        //+5,10,22,34
        for (int x = x1; x <= x2; x++)
        {
            attron(COLOR_PAIR(5));
            mvaddch(index + 5, x, '<'); //mvgetch(index + 5, x)
            attroff(COLOR_PAIR(5));
            move(index + 5, x);
            refresh();
        }
        installMachine(dqmR1, dqmR2, dqmR3);
    }
    char conversion(char inputval, int delayv)
    {
        int r1, r2, r3, st4, d = delayv;
        int index = inputval - 'a';
        blinkcolr(5 + 1, 10 + 1, index);
        r1 = position(dqmR1, dqmR1[index].begin()->first);
        sleep_for(seconds(d));
        blinkcolr(10 + 8, 22 + 1, r1);
        r2 = position(dqmR2, dqmR2[r1].begin()->first);
        sleep_for(seconds(d));
        blinkcolr(22 + 8, 34 + 1, r2);
        r3 = position(dqmR3, dqmR3[r2].begin()->first);
        sleep_for(seconds(d));
        blinkcolr(34 + 8, 46 + 1, r3);
        st4 = position(statdqm, statdqm[r3].begin()->first);
        sleep_for(seconds(d));
        blinkcolrrev(34 + 8, 46 + 1, st4);
        r3 = rposition(dqmR3, dqmR3[st4].begin()->second);
        sleep_for(seconds(d));
        blinkcolrrev(22 + 8, 34 + 1, r3);
        r2 = rposition(dqmR2, dqmR2[r3].begin()->second);
        sleep_for(seconds(d));
        blinkcolrrev(10 + 8, 22 + 1, r2);
        r1 = rposition(dqmR1, dqmR1[r2].begin()->second);
        sleep_for(seconds(d));
        blinkcolrrev(5 + 1, 10 + 1, r1);
        return 'a' + r1;
    }
    char machine(char inputval, int delayv)
    {
        char newch = conversion(inputval, delayv);
        countr1++;
        map<int, int> temp;
        temp = dqmR1.back();
        dqmR1.pop_back();
        dqmR1.push_front(temp);

        if (countr1 % 26 == 0)
        {
            temp = dqmR2.back();
            dqmR2.pop_back();
            dqmR2.push_front(temp);
            countr2++;

            if (countr2 % 26 == 0)
            {
                temp = dqmR3.back();
                dqmR3.pop_back();
                dqmR3.push_front(temp);
                countr3++;
            }
        }
        resetscr();
        installMachine(dqmR1, dqmR2, dqmR3);

        return newch;
    }
};
void encyption(string sin, string sout, EnigmaMachine emachine)
{
    string word;
    ifstream ifile1(sin, ios::in);
    ofstream ofile(sout, ios::out);
    if (ofile.is_open())
    {
        while (ifile1 >> word)
        {
            int i = -1;
            while (word[++i])
            {
                word[i] = tolower(word[i]);
                word[i] = emachine.machine(word[i], 1); //char with delay seconds
                word[i] = toupper(word[i]);
                ofile << word[i];
            }
            ofile << " ";
        }
    }
    ifile1.close();
    ofile.close();
}
void decryption(string sin, string sout, EnigmaMachine emachine)
{
    string word;
    ifstream ifile1(sin, ios::in);
    ofstream ofile(sout, ios::out);
    emachine.resetMachine(); // Reseting the rotors
    if (ofile.is_open())
    {
        while (ifile1 >> word)
        {
            int i = -1;
            while (word[++i])
            {
                word[i] = tolower(word[i]);
                word[i] = emachine.machine(word[i], 1); //char with delay
                //word[i] = toupper(word[i]);
                ofile << word[i];
            }
            ofile << " ";
        }
    }
    ifile1.close();
    ofile.close();
}
string getstringval()
{
    string input;

    // let the terminal do the line editing
    nocbreak();
    echo();

    // this reads from buffer after <ENTER>, not "raw"
    // so any backspacing etc. has already been taken care of
    int ch = getch();

    while (ch != '\n')
    {
        input.push_back(ch);
        ch = getch();
    }

    // restore your cbreak / echo settings here

    return input;
}
int main()
{

    string fileinput, fileoutput;
    EnigmaMachine eMachine;
    int x;
    int maxlines, maxcols;
    getmaxyx(stdscr, maxlines, maxcols);
    wmove(stdscr, maxlines, 0);

    attron(COLOR_PAIR(6));
    addstr("|||Warning :- Don't use backspace|||");
    attroff(COLOR_PAIR(6));
    addstr("Enter number for encryption and decryption 1/0:-");
    x = (getch() - '0');
    refresh();
    while (1)
    {
        resetscr();
        wmove(stdscr, maxlines, 0);
        attron(COLOR_PAIR(6));
        addstr("|||Warning :- Hit Enter after the complete name of file|||");
        attroff(COLOR_PAIR(6));
        addstr("Enter the input filename and output filename:-");
        fileinput = getstringval();
        fileoutput = getstringval();
        refresh();
        if (x == 1)
            encyption(fileinput, fileoutput, eMachine);
        else if (x == 0)
            decryption(fileinput, fileoutput, eMachine);
        else
        {
            endwin();
            exit(0);
        }
        wmove(stdscr, maxlines , 0);
        addstr("Enter number for encryption and decryption 1/0:-");
        x = getch() - '0';
        refresh();
    }
}
