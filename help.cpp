#include <bits/stdc++.h>
using namespace std;
int main()
{
    pair<int, int> p;
    p.first = 5;
    p.second = 23;
    int j1=5, j2=6;
    j1 ^= j2;
    j2 ^= j1;
    j1 ^= j2;

    cout << j1 << " " << j2;
}