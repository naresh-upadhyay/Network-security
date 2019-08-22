#include <bits/stdc++.h>
#define fl2(i, n) for (int i = 0; i < n; i += 2)
#define fl(i, n) for (int i = 0; i < n; i++)
using namespace std;
#define index 5
pair<int, int> location(char key[][index], char ch)
{
    pair<int, int> loc;
    fl(j, 5)
    {
        fl(k, 5)
        {
            if (ch == 'J')
                ch = 'I';
            if (ch == key[j][k])
            {
                loc.first = j;
                loc.second = k;
            }
        }
    }
    return loc;
}
string stringcon(string text)
{
    fl2(k, text.length())
    {
        if (k + 1 == text.length() || text[k] == text[k + 1])
        {
            text.insert(k + 1, 1, 'X');
        }
    }
    return text;
}
string ciphertext(char key[][index], string ptext)
{
    ptext = stringcon(ptext);
    int i1, j1, i2, j2;
    pair<int, int> p;
    fl2(i, ptext.length())
    {
        p = location(key, ptext[i]);
        i1 = p.first;
        j1 = p.second;
        p = location(key, ptext[i + 1]);
        i2 = p.first;
        j2 = p.second;
        if (j1 == j2)
        { //column are equal
            i1 = (i1 + 1) % 5;
            i2 = (i2 + 1) % 5;
        }
        else if (i1 == i2)
        {
            j1 = (j1 + 1) % 5;
            j2 = (j2 + 1) % 5;
        }
        else
        {
            j1 ^= j2;
            j2 ^= j1;
            j1 ^= j2;
        }
        ptext[i] = key[i1][j1];
        ptext[i + 1] = key[i2][j2];
    }
    return ptext;
}
string plaintext(char key[][index], string cipher)
{
    int i1, j1, i2, j2;
    pair<int, int> p;
    fl2(i, cipher.length())
    {
        p = location(key, cipher[i]);
        i1 = p.first;
        j1 = p.second;
        p = location(key, cipher[i + 1]);
        i2 = p.first;
        j2 = p.second;
        if (j1 == j2)
        { //column are equal
            i1 = (i1 - 1 + 5) % 5;
            i2 = (i2 - 1 + 5) % 5;
        }
        else if (i1 == i2)
        {
            j1 = (j1 - 1 + 5) % 5;
            j2 = (j2 - 1 + 5) % 5;
        }
        else
        {
            j1 ^= j2;
            j2 ^= j1;
            j1 ^= j2;
        }
        cipher[i] = key[i1][j1];
        cipher[i + 1] = key[i2][j2];
    }
    return cipher;
}
bool isMatch(string keystr,char ch){
    fl(i,keystr.length()){
        if(ch == keystr[i])
            return true;
    }
    return false;
}
string getstr(char ch){
    string s(1,ch);
    return s;
}

string processkey(string keyfile)
{
    ifstream keyf(keyfile , ios::in);
    string word,newkey="";

    keyf >> word;
    keyf.close();
    transform(word.begin(),word.end(),word.begin(),::toupper);
    fl(i,word.length()){//keywords
        if(!isMatch(newkey,word[i]))
            newkey.append(getstr(word[i]));
    }
    word = newkey;
    fl(i,26){
        if(isMatch(word,'J') && i == ('I'-'A')){ // skipping the case of i/j block
            continue;
        }else if(isMatch(word,'I') && i == ('J'-'A'))
            continue;
        else if(i == ('J'-'A'))
            continue;
        if(!isMatch(word,'A'+i))
            newkey.append(getstr('A'+i));
    }
    ofstream outkey(keyfile,ios::out);
    outkey << newkey;
    keyf.close();
    return newkey;
}

int main()
{
    char arr[5][5];
    string sin, sout, ord, text, cipher,keyfile,key;
    cout << " Enter the key file name:-";
    cin >> keyfile;
    ifstream inkey(keyfile,ios::in);
    inkey >> key;
    key = processkey(key);
    fl(i,5){
        fl(j,5){
            arr[i][j] = key[i*5 + j];
        }
    }
    char ch;
    while (1)
    {
        string word;
        text = "";
        cout << "Encryption/Decryption ?";
        cin >> ch;
        if (ch == 'E' || ch == 'e')
        {
            cout << "Enter the input and output file name :-";
            cin >> sin >> sout;
            ifstream if1(sin, ios::in);
            ofstream outf1(sout, ios::out);
            if (if1.is_open())
            {
                while (if1 >> word)
                {
                    transform(word.begin(), word.end(), word.begin(), ::toupper);
                    text.append(word);
                }
            }
            cipher = ciphertext(arr, text);
            outf1 << cipher;
            if1.close();
            outf1.close();
        }
        else if (ch == 'D' || ch == 'd')
        {
            cout << "Enter the input and output file name :-";
            cin >> sin >> sout;
            ifstream if1(sin, ios::in);
            ofstream outf1(sout, ios::out);
            if (if1.is_open())
            {
                while (if1 >> word)
                {
                    transform(word.begin(), word.end(), word.begin(), ::toupper);
                    text.append(word);
                }
            }
            text = plaintext(arr, text);
            outf1 << text;
            if1.close();
            outf1.close();
        }
        else
            break;
    }
}