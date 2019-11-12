#include <bits/stdc++.h>
#define fl(i, n) for (int i = 0; i < n; i++)
using namespace std;
int xornum(int n1, int n2)
{
    int num = 0;
    fl(i, 8)
    {
        int b1 = n1 % 2, b2 = n2 % 2;
        n1 /= 2;
        n2 /= 2;
        num += (pow(2, i) * (b1 ^ b2));
    }
    return num;
}
string tostr(char ch)
{
    string s(1, ch);
    return s;
}
string generatekey(string text, string key)
{
    int i = -1;
    string keynew;
    ifstream keyfile(key, ios::in);
    keyfile >> keynew;
    int sz = keynew.size();
    string newkey="";
    while (text[++i])
    {
        newkey.push_back(toupper(keynew[i%sz]));
        //newkey.append(tostr('A' + clock() % 26));
    }
    keyfile.close();
    return newkey;
}
void encyption(string sin, string sout, string keyfname)
{
    string word, text, key;
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
    key = generatekey(text, keyfname);
    ofstream keyfile(keyfname, ios::out);
    keyfile << key;
    int i = 0;
    while (text[i])
    {
        int p = text[i] - 'A';
        int k = key[i] - 'A';
        int c = xornum(p, k);
        text[i] = 'A' + c;
        i++;
    }
    ofile << text;
    ifile1.close();
    keyfile.close();
    ofile.close();
}
void decryption(string sin, string sout, string keyfname)
{
    string word, text, key;
    int wordint;
    ifstream ifile1(sin, ios::in);
    ifstream keyfile(keyfname, ios::in);
    ofstream ofile(sout, ios::out);
    keyfile >> key;
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
        int c = text[i] - 'A';
        int k = key[i] - 'A';
        int p = xornum(c, k);
        text[i] = 'A' + p;
        i++;
    }
    ofile << text;

    ifile1.close();
    keyfile.close();
    ofile.close();
}
int main()
{
    fstream file;
    string fileinput, fileoutput, keyfile, key;
    int x;
    cout << "Enter number for encryption , decryption and key 1/0 and filename:-";
    cin >> x >> keyfile;
    while (1)
    {
        if (x == 1)
        {
            cout << "Enter the input filename and output filename :-";
            cin >> fileinput >> fileoutput;
            encyption(fileinput, fileoutput, keyfile);
        }
        else if (x == 0)
        {
            cout << "Enter the input filename and output filename :-";
            cin >> fileinput >> fileoutput;
            decryption(fileinput, fileoutput, keyfile);
        }
        else
            break;
        cout << "Enter number for encryption and decryption 1/0:-";
        cin >> x;
    }
}