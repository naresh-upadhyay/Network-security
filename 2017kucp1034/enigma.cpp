#include <bits/stdc++.h>
#include <curses.h>                //It provide GUI for program
#define dqmap deque<map<int, int>> //Use to create Rotor and create wiring inside that
using namespace std;
using namespace chrono;      //for time
using namespace this_thread; //use for delay
//GUI Portion no. 1
//use for creating static maped (Entry wheel & Reflector wheel) wheel at begining and ending position of enigma
void statWind(int h, int w)
{

    WINDOW *win = newwin(26, 3, h, w); //(cureses function) use to create child window for GUI

    for (int row = 0; row < 26; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            mvwaddch(win, row, col, ' ' | COLOR_PAIR(2)); //coloring the rotor
        }
    }
    for (int i = 0; i < 26; i++)
    {
        mvwaddch(win, i, 1, 'a' + i | COLOR_PAIR(2)); //data inside rotor with color
    }

    wrefresh(win); //update changes made above
}
//use for creating the rotor window or wheel(all 3) GUI
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
//installing rotors on main window or screen  GUI
void installMachine(dqmap dqmR1, dqmap dqmR2, dqmap dqmR3)
{
    //Static maping
    statWind(5, 5);  //for initial simple map
    statWind(5, 46); //for last jumbled map
    //Rotor wheels
    rotorWind(5, 10, dqmR1); //for first rotor
    rotorWind(5, 22, dqmR2); //for second rotor
    rotorWind(5, 34, dqmR3); //for third rotor
}
//reseting screen to initial state (blank screen)
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
//for initializing the screen
void printingscr()
{
    initscr(); // start screen
    clear();   //clear it

    //enable coloring
    start_color();
    init_pair(2, COLOR_YELLOW, COLOR_GREEN);
    init_pair(3, COLOR_CYAN, COLOR_BLUE);
    init_pair(4, COLOR_BLACK, COLOR_WHITE);
    init_pair(5, COLOR_RED, COLOR_MAGENTA);
    init_pair(6, COLOR_WHITE, COLOR_RED);
    resetscr();
}
//Simulator Portion no.2
//Enigma machine class (complete machine)
class EnigmaMachine
{
    dqmap dqmR1, dqmR2, dqmR3, statdqm;
    dqmap ddqmR1, ddqmR2, ddqmR3, dstatdqm;
    unordered_set<int> rval1, rval2, rval3, statval;
    int countr1, countr2, countr3;

public:
    EnigmaMachine() // constructor for enigma
    {
        //Random alphabets generation from a to z (26)
        rval1 = randomgenrator();
        rval2 = randomgenrator();
        rval3 = randomgenrator();
        statval = randomgenrator();
        //create a map on rotors with random alphabets and index alphabets
        mapingRotor(dqmR1, rval1);
        mapingRotor(dqmR2, rval2);
        mapingRotor(dqmR3, rval3);
        statMaping(statdqm, statval);
        //use to keep track of rotations
        countr1 = 0;
        countr2 = 0;
        countr3 = 0;
        //duplicate value storation for backup (for decyphering)
        ddqmR1 = dqmR1;
        ddqmR2 = dqmR2;
        ddqmR3 = dqmR3;
        //start GUI
        printingscr();
        installMachine(dqmR1, dqmR2, dqmR3);
    }
    /*
    void printrotors(dqmap pdq)
    {
        cout << "sz" << pdq.size() << endl;
        for (int i = 0; i < pdq.size(); i++)
        {
            cout << pdq[i].begin()->first << " " << pdq[i].begin()->second << endl;
        }
    }*/
    //random alphabets genrator
    unordered_set<int> randomgenrator()
    {
        unordered_set<int> rand1;
        while (rand1.size() < 26)
        {
            rand1.insert(rand() % 26);
        }
        return rand1;
    }
    //reseting machine to initial state
    void resetMachine()
    {
        dqmR1 = ddqmR1;
        dqmR2 = ddqmR2;
        dqmR3 = ddqmR3;
        resetscr();
        installMachine(dqmR1, dqmR2, dqmR3);
    }
    //static map creation for reflector (random)
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
            mapR.push_front(temp2);
            it++;
            itr++;
            temp.erase(temp.begin());
            temp2.erase(temp2.begin());
        }
    }
    //rotor maping
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
    //finding position of a perticular alphabet in a rotor map
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

    //finding position in reverse direction of a perticular alphabet in a rotor map
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
    //show path how plain text convertes into ciphertext
    void blinkcolr(int x1, int x2, int index, int delayval)
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
        sleep_for(seconds(delayval));
    }
    //show path how plain text character convertes into ciphertext character in reverse direction
    void blinkcolrrev(int x1, int x2, int index, int delyaval)
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
        sleep_for(seconds(delyaval));
    }
    //conversion of a single character (plain to chipher) and vice - versa
    char conversion(char inputval, int delayv)
    {
        int r1, r2, r3, st4;
        int index = inputval - 'a';
        blinkcolr(5 + 1, 10 + 1, index, delayv);
        r1 = position(dqmR1, dqmR1[index].begin()->first);
        blinkcolr(10 + 8, 22 + 1, r1, delayv);
        r2 = position(dqmR2, dqmR2[r1].begin()->first);
        blinkcolr(22 + 8, 34 + 1, r2, delayv);
        r3 = position(dqmR3, dqmR3[r2].begin()->first);
        blinkcolr(34 + 8, 46 + 1, r3, delayv);
        st4 = position(statdqm, statdqm[r3].begin()->first);
        blinkcolrrev(34 + 8, 46 + 1, st4, delayv);
        r3 = rposition(dqmR3, dqmR3[st4].begin()->second);
        blinkcolrrev(22 + 8, 34 + 1, r3, delayv);
        r2 = rposition(dqmR2, dqmR2[r3].begin()->second);
        blinkcolrrev(10 + 8, 22 + 1, r2, delayv);
        r1 = rposition(dqmR1, dqmR1[r2].begin()->second);
        blinkcolrrev(5 + 1, 10 + 1, r1, delayv);
        return 'a' + r1;
    }
    //enabling enigma machine to perform all conversions
    char machine(char inputval, int delayv)
    {
        char newch = conversion(inputval, delayv);
        countr1++;
        map<int, int> temp;
        //for rotor 1 (fast)
        temp = dqmR1.back();
        dqmR1.pop_back();
        dqmR1.push_front(temp);

        if (countr1 % 26 == 0)
        {
            //for rotor 2 (medium)
            temp = dqmR2.back();
            dqmR2.pop_back();
            dqmR2.push_front(temp);
            countr2++;

            if (countr2 % 26 == 0)
            {
                //for rotor 3 (slow)
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
//Portion no.3
//encrypton of complete file
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
//Portion no.4
//decrypton of complete file
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
//Input form GUI Portion no. 5
//geting string (file name) from GUI
string getstringval()
{
    string input;

    // let the terminal do the line editing
    nocbreak();
    echo();

    int ch = getch();
    while (ch != '\n')
    {
        input.push_back(ch);
        ch = getch();
    }
    cbreak();
    noecho();

    // restore your cbreak / echo settings here
    return input;
}
//Main program Portion no. 6
int main()
{

    EnigmaMachine eMachine;
    int x;
    int maxlines, maxcols;
    cbreak();
    noecho();
    getmaxyx(stdscr, maxlines, maxcols); //geting size of screen
    wmove(stdscr, maxlines, 0);          //move the cursure in GUI for curent location (from where to print)
    //printing on GUI
    attron(COLOR_PAIR(6));
    addstr("|||Warning :- Don't use backspace|||");
    attroff(COLOR_PAIR(6));
    addstr("Enter number for encryption and decryption 1/0:-");
    x = (getch() - '0');
    refresh();
    while (1)
    {
        string fileinput, fileoutput;
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
        wmove(stdscr, maxlines, 0);
        addstr("Enter number for encryption and decryption 1/0:-");
        x = getch() - '0';
        refresh();
    }
}
