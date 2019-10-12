#include <bits/stdc++.h>
#define fl(i,n) for(int i = 0 ; i< n ; i++)
using namespace std;

string generatekey(string text){
    int i=0;
    string key;
    while(text[i++]){
        key.push_back('A' + clock()%26);
    }
    return key;
}
void encyption(string sin, string sout,string keyfname)
{
    string word,text,key;
    int wordint;
    ifstream ifile1(sin, ios::in);
    ofstream keyfile(keyfname, ios::out);
    ofstream ofile(sout, ios::out);
    if (ifile1.is_open())
    {
        while (ifile1 >> word)
        {
            transform(word.begin(),word.end(),word.begin(), ::toupper);
            text.append(word);
        }
    }
    key = generatekey(text);
    keyfile << key;
    int i=0;
    while(text[i]){
        int p = text[i] - 'A';
        int k = key[i] - 'A';
        int c = (p + k ) % 26;
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
    string word,text,key;
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
    int i=0;
    while(text[i]){
        int c = text[i] - 'A';
        int k = key[i] - 'A';
        int p = (c - k + 26) % 26;
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
    string fileinput, fileoutput, keyfile,key;
    int x;
    cout << "Enter number for encryption , decryption and key 1/0 and filename:-";
    cin >> x >> keyfile;
    while (1)
    {
        cout << "Enter the input filename and output filename :-";
        cin >> fileinput >> fileoutput;
        if (x == 1){
            encyption(fileinput, fileoutput,keyfile);
        }
        else if (x == 0){
            decryption(fileinput, fileoutput, keyfile);
        }
        else
            break;
        cout << "Enter number for encryption and decryption 1/0:-";
        cin >> x;
    }
}