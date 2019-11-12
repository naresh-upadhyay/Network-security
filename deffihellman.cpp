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
int moduloexpo(int a, int b, int m)
{
    int modvl = 1;
    for (int i = 0; i < b; i++)
    {
        modvl = (modvl * a) % m;
    }
    return modvl;
}
vct PrimRoot(int q)
{
    vct proots;
    for (int p = 1; p <= (q - 1); p++)
    {
        set<int> roots;
        for (int i = 0; i < (q - 1); i++)
        {
            roots.insert(moduloexpo(p, i, q));
        }
        if (roots.size() == (q - 1))
            proots.push_back(p);
    }
    return proots;
}
int randab(int q)
{
    return (rand() % (q - 3)) + 2;
}
void keygenration(int p, int q)
{
    int a = randab(q), b = randab(q);
    cout << "Alice and Bob private keys :-"<<a<<" "<<b<<endl;
    int A = moduloexpo(p, a, q);
    int B = moduloexpo(p, b, q);
    int sa = moduloexpo(B, a, q);
    int sb = moduloexpo(A, b, q);
    cout << "Alice key :-" << sa << " \nBob key :-" << sb << endl;
}
int main()
{
    string filein, fileout;
    int publickey, privatekey, ii = 1, p, q;
    vct primevct = primenumbers();
    for (int i = 0; i < primevct.size(); i++)
    {
        cout << primevct[i] << " ";
    }
    cout << endl;
    cout << "Enter 1/0 for keygeneration / exit :-";
    cin >> ii;
    while (ii == 1)
    {
        cout << "Select a Q from above list:-";
        cin >> q;
        vct proot = PrimRoot(q);
        cout << "Primitive roots :-\n";
        for (int i = 0; i < proot.size(); i++)
        {
            cout << proot[i] << " ";
        }
        cout << endl;
        int p;
        cout << "Select Primitive root :-";
        cin >> p;
        if (ii == 1)
            keygenration(p, q);
        else
            break;
        cout << "Enter 1/0 for keygeneration / exit :-";
        cin >> ii;
    }
}