#include <bits/stdc++.h>
#define fl(i,n) for(int i = 0 ; i< n ; i++)
using namespace std;
void encyption(string sin, string sout, string key)
{
    string word,text;
    int wordint;
    ifstream ifile1(sin, ios::in);
    ofstream ofile(sout, ios::out);
    if (ifile1.is_open())
    {
        while (ifile1 >> word)
        {
            transform(word.begin(),word.end(),word.begin(), ::toupper);
            text.append(word);
        }
    }
    int i=0;
    while(text[i]){
        int index = i % key.length();
        int p = text[i] - 'A';
        int k = key[index] - 'A';
        int c = (p + k ) % 26;
        text[i] = 'A' + c;
        i++;
    }
    ofile << text;
    ifile1.close();
    ofile.close();
}
void decryption(string sin, string sout, string key)
{
    string word,text;
    int wordint;
    ifstream ifile1(sin, ios::in);
    ofstream ofile(sout, ios::out);
    if (ifile1.is_open())
    {
        while (ifile1 >> word)
        {
            text.append(word);
        }
    }
    int i=0;
    while(text[i]){
        int index = i % key.length();
        int c = text[i] - 'A';
        int k = key[index] - 'A';
        int p = (c - k + 26) % 26;
        text[i] = 'A' + p;
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
int main()
{
    string fileinput, fileoutput, keyfile,key;
    int x;
    
    cout << "Enter number for encryption , decryption and key 1/0 and filename:-";
    cin >> x >> keyfile;
    ifstream keyf(keyfile , ios::in);
    keyf>>key;
    transform(key.begin(),key.end(),key.begin(),::toupper);
    while (1)
    {
        cout << "Enter the input filename and output filename :-";
        cin >> fileinput >> fileoutput;
        if (x == 1)
            encyption(fileinput, fileoutput, key);
        else if (x == 0)
            decryption(fileinput, fileoutput, key);
        else
            break;
        cout << "Enter number for encryption and decryption 1/0:-";
        cin >> x;
    }
    printing(fileoutput);
}