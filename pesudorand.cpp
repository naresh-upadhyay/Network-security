#include <bits/stdc++.h>
using namespace std;
int pesudorand(){
    unsigned int overflow = 34255;
    overflow = clock()*overflow + 342352352;
    return overflow % clock();
}
int main()
{
    //buffer overflow with clock
    for (int i = 0 ;i < 5000; i++)
        cout <<pesudorand()<<" ";
}