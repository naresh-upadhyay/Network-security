#include <bits/stdc++.h>
#define fl(i, n) for (int i = 0; i < n; i++)
using namespace std;
int posmaxint(int arr[], int n)
{
    int pos, max = INT_MIN;
    fl(i, n)
    {
        if (arr[i] > max)
        {
            pos = i;
            max = arr[i];
        }
    }
    cout << "value of E is:-" << char('a' + pos) << " is " << max << endl;
    return pos;
}
string mostfreqstr(unordered_map<string, int> umap)
{
    int max = INT_MIN;
    string mfstr;
    for (auto it = umap.begin(); it != umap.end(); it++)
    {
        if (it->second > max)
        {
            max = it->second;
            mfstr = it->first;
        }
    }
    cout << "value of string is:-" << mfstr << endl;
    return mfstr;
}
void decryption(string sin, string sout)
{
    string word, text;
    int letters[26] = {0};
    ifstream ifile1(sin, ios::in);
    ofstream ofile(sout, ios::out);
    unordered_map<string, int> mostfreqstring;
    if (ifile1.is_open())
    {
        while (ifile1 >> word)
        {
            cout << word << flush;
            text.append(word);
            mostfreqstring[word] += 1;
            for (int i = 0; word[i]; i++)
            {
                if (word[i] <= 'z' || word[i] >= 'a')
                    letters[word[i] - 'a'] += 1;
            }
        }
    }
    string st = mostfreqstr(mostfreqstring);
    char che = posmaxint(letters, 26);
    //ofile <<st<<"<->"<<che<<flush;
    ofile << text;

    ifile1.close();
    ofile.close();
}

int main()
{
    //Decryption
    string fileinput, fileoutput;
    cout << "Enter the input filename and output filename :-";
    cin >> fileinput >> fileoutput;
    decryption(fileinput, fileoutput);
}