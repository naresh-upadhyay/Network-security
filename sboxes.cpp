#include <bits/stdc++.h>
using namespace std;
#define vct vector<int>
#define pquesrem pair<vector<int>, vector<int>>
#define vct2dstr vector<vector<string>>
#define fl(i, n) for (int i = 0; i < n; i++)

void printvct(vct printv)
{
    fl(i, printv.size())
    {
        cout << printv[i];
    }
    cout << endl;
}
void functiongeneration(vct cofficients)
{
    for (int i = 0; i < cofficients.size(); i++)
    {
        if (cofficients[i] && i < cofficients.size() - 1)
        {
            cout << "(x^" << cofficients.size() - 1 - i << ")+";
        }
        else if (cofficients[i] && i == cofficients.size() - 1)
        {
            cout << "1" << endl;
        }
    }
    cout << endl;
}
vct input()
{
    vct cofficent;
    for (int i = 7; i >= 0; i--)
    {
        int cof = 0;
        cout << "Enter cofficient of x^" << i << ":";
        cin >> cof;
        cofficent.push_back((cof % 2 + 2) % 2);
    }
    return cofficent;
}
vct addition(vct coff1, vct coff2)
{
    vct coff;
    for (int i = 0; i < 8; i++)
    {
        coff.push_back((coff1[i] ^ coff2[i]));
    }
    return coff;
}
pquesrem division(vct dividend, vct divby)
{
    int ii = 0, count = 0, sz = divby.size();
    vct rem, ques;
    //trim divby remove zeros
    for (int i = 0; i < sz; i++)
    {
        if (divby[i] == 0)
        {
            divby.erase(divby.begin());
            i--;
        }
        else
            break;
    }
    //Normal divide
    while (ii < (dividend.size() - (divby.size() - 1)))
    {
        if (dividend[ii])
        {
            fl(k, divby.size())
            {
                dividend[ii + k] = (dividend[ii + k] ^ divby[k]);
            }
            ques.push_back(1);
        }
        else
        {
            ques.push_back(0);
        }
        ii++;
    }
    for (int nsz = ques.size(); nsz < 8; nsz++)
    {
        ques.insert(ques.begin(), 0);
    }
    while (dividend.size() > 8)
    {
        dividend.erase(dividend.begin());
    }
    rem = dividend;
    pquesrem quesremval;
    quesremval.first = ques;
    quesremval.second = rem;
    return quesremval;
}
vct multiply(vct arr1, vct arr2)
{
    vct temp(15, 0); //of size 15;
    fl(i, 8)
    {
        fl(j, 8)
        {
            temp[i + j] = (temp[i + j] ^ (arr1[i] & arr2[j]));
        }
    }

    //trim remove zeros make it's length 8
    int sz = temp.size();
    for (int i = 0; temp.size()>8; i++)
    {
        if (temp[i] == 0)
        {
            temp.erase(temp.begin());
            i--;
        }
        else
            break;
    }
    if (temp.size() > 8)
    {
        //take modulo with 8 4 3 1 0
        vct modby(9, 0);
        modby[8 - 8] = 1;
        modby[8 - 4] = 1;
        modby[8 - 3] = 1;
        modby[8 - 1] = 1;
        modby[8 - 0] = 1;
        return division(temp, modby).second;
    }
    return temp;
}
bool checkzero(vct arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i])
        {
            return 1;
        }
    }
    return 0;
}
vct multiinverse(vct ra)
{
    vct q, r1, r2, r, t1(8, 0), t2(8, 0), t;
    vct rp(9, 0);
    rp[8 - 8] = 1;
    rp[8 - 4] = 1;
    rp[8 - 3] = 1;
    rp[8 - 1] = 1;
    rp[8 - 0] = 1;

    if (rp.size() < ra.size())
        swap(rp, ra);
    r1 = rp;
    r2 = ra;
    t2[7] = 1;
    while (1)
    {
        q = division(r1, r2).first;
        r = division(r1, r2).second;
        if (checkzero(r))
        {
            t = addition(t1, multiply(q, t2));
            t1 = t2;
            t2 = t;
            r1 = r2;
            r2 = r;
        }
        else
            break;
    }
    return t;
}
string vct2str(vct arr){
    string st;
    for(int i=0; i<arr.size(); i++){
        st.push_back('0'+arr[i]);
    }
    return st;
}
vct str2vct(string str){
    vct arr;
    for(int i=0; str[i];i++){
        arr.push_back(str[i]-'0');
    }
    return arr;
}
string inttohex(int num){
    if(num <10){
        return to_string(num);
    }else if(num == 10){
        return "a";
    }else if(num == 11){
        return "b";
    }else if(num == 12){
        return "c";
    }else if(num == 13){
        return "d";
    }else if(num == 14){
        return "e";
    }else if(num == 15){
        return "f";
    }
}
string bin2hex(string bin){
    int val1=0,val2 = 0;
    //cout <<"["<<bin<<"]";
    for(int i=0;i<4;i++){
        val1 += (bin[i]-'0')*pow(2,(4-i-1));
        val2 += (bin[4+i]-'0')*pow(2,(4-i-1));
    }
    return inttohex(val1)+inttohex(val2);
}
string inttostr(int num){
    string st;
    int i=0;
    while(i<4){
        st.push_back('0'+(num&1));
        num>>=1;
        i++;
    }
    reverse(st.begin(),st.end());
    return st;
}
void printboxes(vct2dstr boxes){
    fl(i,16){
        fl(j,16){
            cout<<bin2hex(boxes[i][j])<<" ";
            //cout<<stoi(string(boxes[i][j]),nullptr,2)<<" ";
        }cout <<endl;
    }
}
vct2dstr sboxesfunct(){
    vct2dstr boxes(16,vector<string>());
    fl(i,16){
        fl(j,16){
            boxes[i].push_back(inttostr(i)+inttostr(j));
        }
    }
    return boxes;
}
vct2dstr invsboxesfunct(vct2dstr boxes){
    fl(i,16){
        fl(j,16){
            if(!checkzero(str2vct(boxes[i][j])))
                boxes[i][j] = "00000000";
            else
            boxes[i][j] = vct2str(multiinverse(str2vct(boxes[i][j])));
        }
    }
    return boxes;
}
vct2dstr specialsboxes(vct2dstr boxes){
    string c = "01100011";
    fl(i,16){
        fl(j,16){
            string byteval;
            cout <<"["<<bin2hex(boxes[i][j])<<"]";
            fl(k,8){
                byteval.push_back('0'+((boxes[i][j][k]-'0')^(boxes[i][j][(k+4)%8]-'0')^(boxes[i][j][(k+5)%8]-'0')^(boxes[i][j][(k+6)%8]-'0')^(boxes[i][j][(k+7)%8]-'0')^(c[k]-'0')));
            }
            boxes[i][j] = byteval;
            cout <<bin2hex(boxes[i][j])<<" ";
        }cout <<endl;
    }
    return boxes;
}
int main()
{
    int t;
    cout << "Enter :-";
    cin >> t;
    while (1)
    {
        if (t == 1)
        {
            functiongeneration(input());
        }
        else if (t == 2)
        {
            functiongeneration(addition(input(), input()));
        }
        else if (t == 3)
        {
            functiongeneration(multiply(input(), input()));
        }
        else if (t == 4)
        {
            functiongeneration(multiinverse(input()));
        }else if(t == 5){
            printboxes(sboxesfunct());
        }else if(t == 6){
            printboxes(invsboxesfunct(sboxesfunct()));
        }else if(t == 7){
            specialsboxes(sboxesfunct());
        }
        cout << "Enter :-";
        cin >> t;
    }
}