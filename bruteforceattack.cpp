//take some data to train ceaser chipher
#include <bits/stdc++.h>
using namespace std;
int bestkey(map<int, int> keys)
{
    int k = 0, kold = keys[0];
    for (int i = 0; i < 26; i++)
    {
        if (keys[i] > kold)
        {
            k = i;
            kold = keys[i];
        }
    }
    return k;
}
int keygerator(string sin, string comfile)
{
    string wordin, wordcom;
    map<int, int> keywithfreq; //to find best key
    ifstream ifile(sin, ios::in);
    for (int i = 0; i < 26; i++)
    {
        keywithfreq[i] = 0;
    }
    while (ifile >> wordin)
    {
        ifstream ifilecom(comfile, ios::in);
        while (ifilecom >> wordcom)
        {
            if (wordin.size() == wordcom.size())
            {
                if((wordin[0] - wordcom[0]) >= 0)
                keywithfreq[(wordin[0] - wordcom[0])] += 1;
            }
        }
    }
    return bestkey(keywithfreq);
}
void decryption(string sin, string sout, int k)
{
    string word;
    int wordint;
    ifstream ifile1(sin, ios::in);
    ofstream ofile(sout, ios::out);
    cout << k << endl;
    k %= 26;
    if (ofile.is_open())
    {
        while (ifile1 >> word)
        {
            int i = -1;
            while (isalpha(word[++i]))
            {
                word[i] = toupper(word[i]);
                wordint = word[i];
                wordint -= k;

                if (wordint < 65)
                {
                    int temp = 65 - wordint;
                    wordint = 90 - temp + 1;
                }
                word[i] = wordint;

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
    cout << "Enter common words file name:-";
    cin >> comfile;
    cout << "Enter 1 for decryption :-";
    cin >> x;
    while (1)
    {
        if (x == 1)
        {
            cout << "Enter the input filename and output filename:-";
            cin >> fileinput >> fileoutput;
            int k = keygerator(fileinput, comfile);
            decryption(fileinput, fileoutput, k);
        }
        else
            break;
        cout << "Enter 1 for decryption :-";
        cin >> x;
    }
    printing(fileoutput);
}