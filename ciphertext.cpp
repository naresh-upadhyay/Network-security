#include <bits/stdc++.h>
using namespace std;
void encyption(string sin, string sout, int k)
{
    string word;
    int wordint;
    ifstream ifile1(sin, ios::in);
    ofstream ofile(sout, ios::out);
    k %= 26;
    if (ofile.is_open())
    {
        while (ifile1 >> word)
        {
            int i = -1;
            while (word[++i])
            {
                wordint = word[i];
                wordint += k;
                word[i] = tolower(word[i]);

                if (wordint > 122)
                {
                    int temp = wordint - 122;
                    wordint = 96 + temp;
                }
                word[i] = wordint;

                word[i] = toupper(word[i]);
                ofile << word[i];
            }
            ofile << " ";
        }
    }
    ifile1.close();
    ofile.close();
}
void decryption(string sin, string sout, int k)
{
    string word;
    int wordint;
    ifstream ifile1(sin, ios::in);
    ofstream ofile(sout, ios::out);
    k %= 26;
    if (ofile.is_open())
    {
        while (ifile1 >> word)
        {
            int i = -1;
            while (word[++i])
            {
                wordint = word[i];
                wordint -= k;
                word[i] = tolower(word[i]);

                if (wordint < 65)
                {
                    int temp = 65 - wordint;
                    wordint = 90 - temp;
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
    string fileinput, fileoutput;
    int x, k;
    cout << "Enter number for encryption and decryption 1/0:-";
    cin >> x;
    while (1)
    {
        cout << "Enter the input filename and output filename:-";
        cin >> fileinput >> fileoutput;
        cout << "Enter key:-";
        cin >> k;
        if (x == 1)
            encyption(fileinput, fileoutput, k);
        else if (x == 0)
            decryption(fileinput, fileoutput, k);
        else
            break;
        cout << "Enter number for encryption and decryption 1/0:-";
        cin >> x;
    }
    printing(fileoutput);
}