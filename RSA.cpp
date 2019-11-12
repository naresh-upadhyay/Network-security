#include <bits/stdc++.h>
using namespace std;
#define vct vector<int>
int gcd(int a, int b)
{
    if (b == 0)
    {
        return a;
    }
    else
    {
        return gcd(b, a % b);
    }
}
vct primenumbers()
{
    int num;
    vct values;
    for (int i = 2;; i++)
    {
        int count = 0;
        for (int j = 2; j * j <= i; j++)
        {
            if (i % j == 0)
            {
                count++;
            }
        }
        if (!count)
            values.push_back(i);
        if (values.size() == 100)
            return values;
    }
}
vct listE(int fi)
{
    vct listofEs;
    int e = 2;
    while (e < fi)
    {
        if (gcd(e, fi) == 1)
            listofEs.push_back(e);
        e++;
    }
    return listofEs;
}
int calcd(int e, int fi)
{
    int d = 1;
    while (1)
    {
        if ((e * d) % fi == 1)
            return d;
        d++;
    }
}
int moduloexpo(int a,int b,int m){
    int modvl=1;
    for(int i=0;i<b;i++){
        modvl=(modvl*a)%m;
    }
    return modvl;
}
void encryption(string fin, string fout, int e, int n) //e = public key
{
    string text, word;
    ifstream filein(fin, ios::in);
    ofstream fileout(fout, ios::out);
    while (filein >> word)
    {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        for (int i = 0; word[i]; i++)
        {
            if (isalpha(word[i]))
                text += to_string(moduloexpo((word[i] - 'a'), e,n)) + " ";
        }
    }
    fileout << text;
}
void decryption(string fin, string fout, int d, int n) //d = private key
{
    string text;
    int word;
    ifstream filein(fin, ios::in);
    ofstream fileout(fout, ios::out);
    while (filein >> word)
    {
        text += 'a'+(moduloexpo(word, d,n));
    }
    fileout << text;
}
int main()
{
    string filein, fileout;
    int publickey, privatekey, i = 0, p, q;
    vct primevct = primenumbers();
    for (int i = 0; i < primevct.size(); i++)
    {
        cout << primevct[i] << " ";
    }
    cout << endl;
    cout << "Select a P and Q from above list:-";
    cin >> p >> q;
    int n = p * q;
    int fi = (p - 1) * (q - 1);
    vct liEs = listE(fi);
    for (int i = 0; i < liEs.size(); i++)
    {
        cout << liEs[i] << " ";
    }
    cout << endl;
    cout << "Select a public key from above list:-";
    cin >> publickey;
    privatekey = calcd(publickey, fi);
    cout << "Private key:-" << privatekey << endl;
    cout << "Enter encryption/decryption 1/2 :-";
    cin >> i;
    while (1)
    {
        cout << "Enter the input and output file :-";
        cin >> filein >> fileout;
        if (i == 1)
            encryption(filein, fileout, publickey, n);
        else if (i == 2)
            decryption(filein, fileout, privatekey, n);
        else
            break;
        cout << "Enter encryption/decryption :-";
        cin >> i;
    }
}