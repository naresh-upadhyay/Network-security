#include <bits/stdc++.h>
#define fl(i, n) for (int i = 0; i < n; i++)
using namespace std;
void encyption(string sin, string sout, string key)
{
    string word, text;
    int wordint;
    ifstream ifile1(sin, ios::in);
    ofstream ofile(sout, ios::out);
    if (ifile1.is_open())
    {
        while (ifile1 >> word)
        {
            transform(word.begin(), word.end(), word.begin(), ::toupper);
            text.append(word);
        }
    }
    int i = 0;
    while (text[i])
    {
        if (isalpha(text[i]))
        {
            int index = int(text[i] - 'A');
            text[i] = key[index];
        }
        i++;
    }
    ofile << text;
    ifile1.close();
    ofile.close();
}
void decryption(string sin, string sout, string key)
{
    string word, text;
    int wordint;
    map<char, char> dekey;
    ifstream ifile1(sin, ios::in);
    ofstream ofile(sout, ios::out);
    fl(i, 26)
        dekey[key[i]] = 'A' + i;
    if (ifile1.is_open())
    {
        while (ifile1 >> word)
        {
            text.append(word);
        }
    }
    int i = 0;
    while (text[i])
    {
        if (isalpha(text[i]))
            text[i] = dekey[text[i]];
        i++;
    }
    ofile << text;

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
bool isMatch(string keystr, char ch)
{
    fl(i, keystr.length())
    {
        if (ch == keystr[i])
            return true;
    }
    return false;
}
string getstr(char ch)
{
    string s(1, ch);
    return s;
}
string processkey(string keyfile)
{
    ifstream keyf(keyfile, ios::in);
    string word, newkey = "";

    keyf >> word;
    keyf.close();
    transform(word.begin(), word.end(), word.begin(), ::toupper);
    fl(i, word.length())
    { //keywords
        if (!isMatch(newkey, word[i]) && isalpha(word[i]))
            newkey.push_back(word[i]);
    }
    word = newkey;
    fl(i, 26)
    {
        if (!isMatch(word, 'A' + i))
            newkey.push_back('A' + i);
    }
    ofstream outkey(keyfile, ios::out);
    outkey << newkey;
    keyf.close();
    return newkey;
}
int main()
{
    fstream file;
    string fileinput, fileoutput, key;
    int x;
    cout << "Enter number for encryption , decryption and key 1/0 and filename:-";
    cin >> x >> key;
    key = processkey(key);
    while (1)
    {
        if (x == 1)
        {
            cout << "Enter the input filename and output filename :-";
            cin >> fileinput >> fileoutput;
            encyption(fileinput, fileoutput, key);
        }
        else if (x == 0)
        {
            cout << "Enter the input filename and output filename :-";
            cin >> fileinput >> fileoutput;
            decryption(fileinput, fileoutput, key);
        }
        else
            break;
        cout << "Enter number for encryption and decryption 1/0:-";
        cin >> x;
    }
    printing(fileoutput);
}