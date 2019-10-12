#include <bits/stdc++.h>
#define fl(i, n) for (int i = 0; i < n; i++)
#define umstring map<string, int>
#define umfreq2str map<int,string>
#define umc2p map<char, char>
#define umi2c map<int, char>
#define umc2i map<char, int>
using namespace std;
umi2c reversemc2i(umc2i c2f)
{
    umi2c f2c;
    for (auto it = c2f.begin(); it != c2f.end(); it++)
    {
        f2c[it->second] = it->first;
    }
    return f2c;
}
string * reverstr2freq(umstring c2f)
{
    umfreq2str f2c;
    for (auto it = c2f.begin(); it != c2f.end(); it++)
    {
        f2c[it->second] = it->first;
    }
    string *arr = (string *) malloc(10 * sizeof(string));
    int i = 0;
    for(auto it = f2c.rbegin();it!= f2c.rend(),i<f2c.size();i++,it++){
        arr[i] = it->second;
    }
    return arr;
}
umc2p ciphertopalinfreq(string cipher)
{
    umc2i c2f;
    umi2c f2c;
    char arr[] = {'z', 'q', 'x', 'j', 'k', 'v', 'b', 'p', 'y', 'g', 'f', 'w', 'm', 'u', 'c', 'l', 'd', 'r', 'h', 's', 'n', 'i', 'o', 'a', 't', 'e'};
    umc2p newmp;
    for (int i = 0; cipher[i]; i++)
    {
        c2f[cipher[i]] += 1;
    }
    f2c = reversemc2i(c2f);
    auto it = f2c.begin();
    for (int i = 0; i < 26; i++, it++)
    {
        newmp[it->second] = arr[i];
    }
    return newmp;
}
void decryption(string sin, string sout,string * top10plain)
{
    ifstream infile(sin, ios::in);
    ofstream outfile(sout, ios::out);
    umstring freqmap;
    string word, cipher;
    if (infile.is_open())
    {
        while (infile >> word)
        {
            transform(word.begin(), word.end(), word.begin(), ::toupper);
            freqmap[word] += 1;
            cipher.append(word);
        }
    }
    umc2p cipher2plain = ciphertopalinfreq(cipher);
    string * freqstring = reverstr2freq(freqmap);// last element has most frequency


}
int main()
{
    string fileinput, fileoutput;
    int x;
    cout << "Enter 1 for decryption :-";
    cin >> x;
    while (1)
    {
        cout << "Enter the input filename and output filename :-";
        cin >> fileinput >> fileoutput;
        if (x == 1)
            decryption(fileinput, fileoutput);
        else
            break;
        cout << "Enter 1 for decryption :-";
        cin >> x;
    }
}