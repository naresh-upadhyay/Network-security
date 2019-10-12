#include <bits/stdc++.h>
#define fl(i, n) for (int i = 0; i < n; i++)
using namespace std;
int d, x, y;
void gcd(int a, int b)
{
    if (b == 0)
    {
        d = a;
        x = 1;
        y = 0;
    }
    else
    {
        gcd(b, a % b);
        int tempx = x;
        x = y;
        y = tempx - (a / b) * y;
    }
}
int *keygenerate()
{
    srand(time(0));
    int *arr = (int *)malloc(10 * sizeof(int));
    for (int i = 0; i < 10; i++)
    {
        int key = rand() % 26;
        gcd(key, 26);
        while (d != 1)
        {
            key = rand() % 26;
            gcd(key, 26);
        }
        arr[i] = key;
    }
    return arr;
}
void encryption(string sin, string sout, int a, int b)
{
    string word, text, cipher;
    ifstream filein(sin, ios::in);
    ofstream fileout(sout, ios::out);
    if (filein.is_open())
    {
        while (filein >> word)
        {
            transform(word.begin(), word.end(), word.begin(), ::toupper);
            text.append(word);
        }
    }
    for (int i = 0; text[i]; i++)
    {
        int ch = (a * (text[i] - 'A') + b) % 26;
        cipher.push_back('A' + ch);
    }
    fileout << cipher;
    filein.close();
    fileout.close();
}
void decryption(string sin, string sout, int a, int b)
{
    string word, text, cipher;
    ifstream filein(sin, ios::in);
    ofstream fileout(sout, ios::out);
    gcd(a, 26);
    int ainverse = (x + 26) % 26;
    cout << "A inverse :-" << ainverse;
    if (filein.is_open())
    {
        while (filein >> word)
        {
            cipher.append(word);
        }
    }
    for (int i = 0; cipher[i]; i++)
    {
        int ch = (((cipher[i] - 'A') - b + 26) * (ainverse)) % 26;
        text.push_back('A' + ch);
    }
    fileout << text;
    filein.close();
    fileout.close();
}
int main()
{
    int *keys = keygenerate();
    int a = keys[2];
    int b, eord;
    string filein, fileout, word;
    cout << "Enter the value of b less than " << a << " :-";
    cin >> b;
    if (b >= a)
    {
        cout << "Sorry\n";
        exit(0);
    }
    cout << "Enter for encryption / decryption 1/0 :-";
    cin >> eord;
    while (1)
    {
        cout << "Enter file name for input and output :-";
        cin >> filein >> fileout;
        if (eord == 1)
        {
            encryption(filein, fileout, a, b);
        }
        else if (eord == 0)
        {
            decryption(filein, fileout, a, b);
        }
        else
            break;
        cout << "Enter for encryption / decryption 1/0 :-";
        cin >> eord;
    }
}