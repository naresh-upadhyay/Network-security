//frequency attack(monoalphabetics substitution)
#include <bits/stdc++.h>
#define mapc2c map<char, char>
#define mapc2i map<char, int>
#define vecti2c vector<pair<int,char>>
#define mapi2i map<int, int>
using namespace std;
bool decreasing(const pair<int,int> &a, 
              const pair<int,int> &b) 
{ 
    return (a.first >= b.first); 
} 
mapc2c keyorder(mapc2i maping)
{
    char dict[] = {'E', 'T', 'A', 'O', 'I', 'N', 'S', 'R', //order of decreasing frequency
                   'H', 'D', 'L', 'U', 'C', 'M', 'F', 'Y',
                   'W', 'G', 'P', 'B', 'V', 'K', 'X', 'Q',
                   'J', 'Z'};
    vecti2c mi2c;
    for (int i = 0; i < 26; i++)
    {
        mi2c.push_back({maping['A'+i],('A'+i)});
    }
    sort(mi2c.begin(),mi2c.end(),decreasing);
    mapc2c keymap;
    for(int i=0; i<26; i++){
        keymap[mi2c[i].second] = dict[i];
    }

    return keymap;
}
mapc2c keygerator(string sin)
{
    string wordin;
    ifstream ifile(sin, ios::in);
    mapc2i mping;
    for (int i = 0; i < 26; i++){
        mping['A'+i]=0;
    }
    
    while (ifile >> wordin)
    {
        int i=-1;
        if(isalpha(wordin[++i])){
            char chw = toupper(wordin[i]);
            mping[chw] +=1;
        }
    }
    return keyorder(mping);

}
void decryption(string sin, string sout, mapc2c subst)
{
    string word;
    int wordint;
    ifstream ifile1(sin, ios::in);
    ofstream ofile(sout, ios::out);
    if (ofile.is_open())
    {
        while (ifile1 >> word)
        {
            int i = -1;
            while (isalpha(word[++i]))
            {
                word[i] = toupper(word[i]);
                word[i] = subst[word[i]];
                word[i] = tolower(word[i]);
                ofile << word[i];
            }
            ofile << " ";
        }
    }
    ifile1.close();
    ofile.close();
}
void printing(string filename)
{
    fstream file;
    string word;
    file.open(filename.c_str());
    while (file >> word)
    {
        cout << word << " ";
    }
    file.close();
}
int main()
{
    fstream file;
    string fileinput, fileoutput, comfile;
    int x;
    cout << "Enter 1 for decryption :-";
    cin >> x;
    while (1)
    {
        if (x == 1)
        {
            cout << "Enter the input filename and output filename:-";
            cin >> fileinput >> fileoutput;
            mapc2c k = keygerator(fileinput);
            decryption(fileinput, fileoutput, k);
        }
        else
            break;
        cout << "Enter 1 for decryption :-";
        cin >> x;
    }
    printing(fileoutput);
}