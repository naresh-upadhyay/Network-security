#include<bits/stdc++.h>
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

int main(){ 
       gcd(3, 26);
    int ainverse = (x + 26) % 26;
    cout <<ainverse;

}