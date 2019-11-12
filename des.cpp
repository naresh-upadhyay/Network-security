#include <bits/stdc++.h>
using namespace std;
#define fl(i, n) for (int i = 0; i < n; i++)
#define unset unordered_set<int>
#define dequ deque<int>
#define ddequ deque<deque<int>>
string dectobin(int d)
{
    string st;
    int i = 0;
    while (i < 8)
    {
        if (d)
        {
            st.insert(st.begin(), '0' + d % 2);
            d /= 2;
        }
        else
        {
            st.insert(st.begin(), '0');
        }
        i++;
    }
    return st;
}
void printdequ(dequ dequu){
    fl(i,dequu.size()){
        cout <<dequu[i]<<" "<<flush;
    }cout<<endl;
}
dequ stringtodequ(string str)
{
    dequ dq;
    for (int i = 0; str[i]; i++)
    {
        dq.push_back(str[i] - '0');
    }
    return dq;
}
string bintostr(dequ dq)
{
    string str;
    for (int i = 0; i < dq.size() / 8; i++)
    {
        int temp = 0;
        for (int j = 0; j < 8; j++)
        {
            temp = temp + (dq[8 * i + j] * pow(2, 7 - j));
        }
        str.push_back(char(temp));
    }
    cout <<"bintostr"<<endl;
    return str;
}
dequ initialpermutaiton() //64 bits
{
    unset uset;
    dequ arr;
    arr.resize(64);
    while (uset.size() < 64)
    {
        uset.insert(rand() % 64);
    }
    int i = 0;
    for (auto it = uset.begin(); it != uset.end(); i++, it++)
    {
        arr[i] = *it;
    }
    printdequ(arr);
    cout <<"initialpermutaiton"<<endl;
    return arr;
}
dequ inverseinitalperm(dequ arr)
{
    int i = 0;
    dequ newarr;
    newarr.resize(64);
    while (i < 64)
    {
        newarr[arr[i]] = i;
        i++;
    }
    printdequ(newarr);
    cout <<"inverseinitialpermutaiton"<<endl;
    return newarr;
}
dequ expansionfun(dequ arr)
{ //32 to 48
    dequ newarr;
    newarr.resize(48);
    newarr[0] = arr[31];
    printdequ(arr);
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if ((j > 0 && j < 5))
                newarr[(6 * i + j)] = arr[(4 * i + j - 1)];
            else if (j == 0)
            {
                newarr[(6 * i + j - 1 + 48) % 48] = arr[(4 * i + j)];
            }
            else if (j == 5)
            {
                newarr[(6 * i + j)] = arr[(4 * (i + 1)) % 32];
            }
        }
    }
    printdequ(newarr);
    cout <<"expansionfunction"<<endl;
    return newarr;
}
dequ permutaiton() //32 bits
{
    unset uset;
    dequ arr;
    arr.resize(32);
    while (uset.size() < 32)
    {
        uset.insert(rand() % 32);
    }
    int i = 0;
    for (auto it = uset.begin(); it != uset.end(); i++, it++)
    {
        arr[i] = *it;
    }
    printdequ(arr);
    cout <<"permutation"<<endl;
    return arr;
}
dequ permutaitonforchoice1() //32 bits
{
    unset uset;
    dequ arr;
    arr.resize(64);
    while (uset.size() < 64)
    {
        uset.insert(rand() % 64);
    }
    int i = 0;
    for (auto it = uset.begin(); it != uset.end(); i++, it++)
    {
        arr[i] = *it;
    }
    printdequ(arr);
    cout <<"permutation"<<endl;
    return arr;
}
dequ mapbin2permut(dequ bin, dequ permut)
{
    int sz = permut.size();
    dequ newdq;
    newdq.resize(sz);
    for (int i = 0; i < sz; i++)
    {
        newdq[i] = bin[permut[i]];
    }
    printdequ(newdq);
    cout <<"mapbin2permut"<<endl;
    return newdq;
}
dequ permutationchoice1(string arr,dequ permutc1) //64->56 bits
{
    unset uset;
    int i = 0;
    dequ newarr;
    newarr.resize(56);
    for (int i=0 ; i<64; i++)
    {
        if(i%8)
        newarr[i] = (arr[i] - '0');
        cout <<newarr[i]<<" "<<flush;
    }
    newarr = mapbin2permut(newarr,permutc1);
    cout<<endl;
    printdequ(newarr);
    cout <<"permutationchoice1"<<endl;
    return newarr;
}
dequ permutationchoice2() //56 -> 48 bits
{
    unset uset;
    dequ newarr;
    newarr.resize(48);
    while (uset.size() <= 48)
    {
        uset.insert(rand() % 56);
    }
    auto it = uset.begin();
    for (int j = 0; j < uset.size(); j++, it++)
    {
        newarr[j] = *it;
    }
    printdequ(newarr);
    cout <<"permutationchoice2"<<endl;
    return newarr;
}
dequ leftcircularsift(dequ arr)
{ //28->28
    int temp = arr.front();
    arr.pop_front();
    arr.push_back(temp);
    printdequ(arr);
    cout <<"leftcircularshift"<<endl;
    return arr;
}
dequ keygeneration(string key,dequ permutc1)
{
    transform(key.begin(), key.end(), key.begin(), ::tolower);
    string keystr = "";
    for (int i = 0; i < 8; i++)
    {
        keystr += dectobin(int(key[i]));
    }
    cout <<keystr<<endl;
    dequ key56 = permutationchoice1(keystr,permutc1);
    printdequ(key56);
    cout <<"keygeneration"<<endl;
    return key56;
}
dequ afterleftcircularkey(dequ key) //56 key
{
    int i1 = key[0], i32 = key[32];
    key = leftcircularsift(key);
    key[31] = i1;
    key[55] = i32;
    printdequ(key);
    cout <<"afterleftcircular"<<endl;
    return key;
}
dequ xorfun(dequ d1, dequ d2)
{
    dequ xorval;
    xorval.resize(d1.size());
    printdequ(d1);
    printdequ(d2);
    for (int i = 0; i < d1.size(); i++)
    {
        xorval[i] = ((d1[i]) ^ (d2[i]));
    }
    printdequ(xorval);
    cout <<"xorfun"<<endl;
    return xorval;
}
dequ mapingsbox(dequ xorv, int **sboxes)
{
    dequ smap;
    smap.resize(32);
    for (int i = 0; i < 8; i++)
    {
        int r = xorv[8 * i + 0] * 2 + xorv[8 * i + 5], c = 0;
        for (int j = 4; j > 0; j--)
        {
            c = c + (xorv[8 * i + j] * pow(2, (4 - j)));
        }
        int val = sboxes[r][c];
        string bin = dectobin(val);
        bin = bin.substr(4, 4);
        dequ binaryy = stringtodequ(bin);
        for (int k = 0; k < 4; k++)
        {
            smap[8 * i + k] = binaryy[k];
        }
    }
    printdequ(smap);
    cout <<"mapingfuntion"<<endl;
    return smap;
}
class DES
{
    dequ exp, straitp, initalp, inverseinitialp, permut, keyin56, permutc1,permutaionc2;
    ddequ rkeys;
    int **sboxes,rindex=-1;

public:
    DES(string kiy)
    {
        //round fun()
        sboxes = (int **)malloc(32 * sizeof(*sboxes));
        for (int i = 0; i < 32; i++)
        {
            sboxes[i] = (int *)malloc(16 * sizeof(*sboxes[i]));
        }
        sboxes = fillsboxes();
        permut = permutaiton();
        //round
        initalp = initialpermutaiton();
        inverseinitialp = inverseinitalperm(initalp);
        //key
        rkeys.resize(16);
        permutc1 = permutaitonforchoice1();
        permutaionc2 = permutationchoice2();
        keyin56 = keygeneration(kiy,permutc1);
    cout <<"desconstructor"<<endl;
    }
    //alreaddy function
    dequ subkey(dequ key)
    {
        dequ subkeyin = afterleftcircularkey(key);
        subkeyin = mapbin2permut(subkeyin, permutaionc2);
        printdequ(subkeyin);
        cout <<"subkey"<<endl;
        return subkeyin;
    }

    dequ roundfunction(dequ text32, dequ key48)
    {
        dequ temp = expansionfun(text32);
        temp = xorfun(temp, key48);
        temp = mapingsbox(temp, sboxes);
        temp = mapbin2permut(temp, permut);
        printdequ(temp);
        cout <<"roundfunction"<<endl;
        return temp;
    }
    dequ round(dequ arr)
    {
        dequ left, right, temp, templeft;
        left = copy32(arr,0,31);
        right = copy32(arr,32,63);
        keyin56 = subkey(keyin56);
        rkeys[++rindex] = keyin56;
        printdequ(left);
        printdequ(right);
        cout<<"then roundfun"<<endl;
        temp = roundfunction(right, keyin56);
        templeft = temp;
        right = xorfun(left, temp);
        left = templeft;
        arr = merge(left,right);
        printdequ(arr);
        cout <<"round"<<endl;
        return arr;
    }
    dequ merge(dequ src1,dequ src2){
        dequ cp;
        cp.resize(src1.size()+src2.size());
        int i=0;
        for(; i<src1.size(); i++){
            cp[i] = src1[i];
        }
        int j=0;
        for(;i<(src1.size()+src2.size());i++,j++){
            cp[i] = src2[j];
        }
        return cp;
    }

    dequ copy32(dequ src,int start,int end){
        dequ cp32;
        cp32.resize(32);
        int j=0;
        for(int i=start ; i<=end; i++,j++){
            cp32[j] = src[i];
        }
        return cp32;
    }
    dequ allrounds(dequ arr)
    {
        dequ temp = mapbin2permut(arr, initalp);
        temp = round(temp);
        temp = round(temp);
        temp = round(temp);
        temp = round(temp);
        temp = round(temp);
        temp = round(temp);
        temp = round(temp);
        temp = round(temp);
        temp = round(temp);
        temp = round(temp);
        temp = round(temp);
        temp = round(temp);
        temp = round(temp);
        temp = round(temp);
        temp = round(temp);
        temp = round(temp);
        temp = mapbin2permut(temp, inverseinitialp);
        printdequ(temp);
        cout <<"allrounds"<<endl;
        return temp;
    }
    string DESrun(string str)
    {
        string stbin = "";
        for (int i = 0; i < 8; i++)
        {
            stbin += dectobin(int(str[i]));
        }
        dequ temp = stringtodequ(stbin);
        temp = allrounds(temp);
        printdequ(temp);
        cout <<"Desrun"<<endl;
        return bintostr(temp);
    }
    int *randum()
    { //0->15
        int *rval ;
        rval = (int *)malloc(16 * sizeof(*rval));
        unset st;
        while (st.size() < 16)
        {
            st.insert(rand() % 16);
        }
        int i = 0;
        for (auto it = st.begin(); it != st.end(); it++, i++)
        {
            rval[i] = *it;
        }
        cout <<"randum"<<endl;
        return rval;
    }
    int **fillsboxes()
    {
        int **boxes;
        boxes = (int **)malloc(32 * sizeof(*boxes));
        for (int i = 0; i < 32; i++)
        {
            boxes[i] = (int *)malloc(16 * sizeof(*boxes[i]));
        }
        for (int j = 0; j < 32; j++)
        {
            boxes[j] = randum();
        }
        cout <<"fillsboxes"<<endl;
        return boxes;
    }
};
void encyption(string sin, string sout, DES des)
{
    string word, text;
    ifstream ifile1(sin, ios::in);
    ofstream ofile(sout, ios::out);
    if (ifile1.is_open())
    {
        while (ifile1 >> word)
        {
            transform(word.begin(), word.end(), word.begin(), ::toupper);
            text.append(word);
        }
    }
    int sz = text.size(), ii;
    ii = (sz / 8) * 8;
    string str;
    for (int i = 0; i < ii; i += 8)
    {
        str += des.DESrun(text.substr(i, 8));
    }
    sz = 8 - (sz % 8);
    while (sz % 8)
    {
        text.push_back('x');
        sz--;
        if (sz == 0)
        {
            str += des.DESrun(text.substr(ii, 8));
        }
    }
    cout<<"chipher text --------------------------------->:"<<str<<endl;
    ofile << str;
    ifile1.close();
    ofile.close();
}
void decryption(string sin, string sout)
{
    string word, text;
    ifstream ifile1(sin, ios::in);
    ofstream ofile(sout, ios::out);
    if (ifile1.is_open())
    {
        while (ifile1 >> word)
        {
            text.append(word);
        }
    }
    ofile << text;
    ifile1.close();
    ofile.close();
}
int main()
{
    string fileinput, fileoutput, key;
    int x, ksz;

    cout << "Enter number for encryption , decryption 1/0 :-";
    cin >> x;
    cout << "Enter the key as string :-";
    cin >> key ;
    DES des(key);
    while (1)
    {
        cout << "Enter the input filename and output filename :-";
        cin >> fileinput >> fileoutput;
        if (x == 1)
            encyption(fileinput, fileoutput,des);
        else if (x == 0)
            decryption(fileinput, fileoutput);
        else
            break;
        cout << "Enter number for encryption and decryption 1/0:-";
        cin >> x;
    }
}