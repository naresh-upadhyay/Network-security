#include <bits/stdc++.h>
#define fl(i, n) for (int i = 0; i < n; i++)
#define fln(i, n, r) for (int i = 0; i < n; i += r)
using namespace std;
//Encryption
int p;
int *multimatrix(int **key, int *text, int row)
{
    int *finalmat = (int *)malloc(row * sizeof(int));
    fl(r, row)
    {
        int temp = 0;
        fl(c, row)
        {
            temp += key[r][c] * text[c];
            temp %= 26;
        }
        finalmat[r] = temp;
    }
    return finalmat;
}
int **keymat(string key, int r)
{
    int **keym1;
    keym1 = (int **)malloc(r * sizeof(*keym1));
    fl(i, r)
    {
        keym1[i] = (int *)malloc(r * sizeof(*keym1[i]));
        fl(j, r)
        {
            keym1[i][j] = key[i * r + j] - 'A';
        }
    }
    return keym1;
}
int *textmat(string text, int r)
{
    int *txtm = (int *)malloc(r * sizeof(int));
    fl(i, r)
    {
        txtm[i] = text[i] - 'A';
    }
    return txtm;
}
string intTochar(int *arr, int sz)
{
    string s1;
    fl(i, sz)
    {
        s1.push_back('A' + arr[i]);
    }
    return s1;
}
//Decryption
int **trans2d(int **key, int r)
{
    key[0][0] ^= key[1][1];
    key[1][1] ^= key[0][0];
    key[0][0] ^= key[1][1];
    key[0][1] = (-key[0][1] + 26) % 26;
    key[1][0] = (-key[1][0] + 26) % 26;
    return key;
}
int **trans3d(int **key, int r)
{
    int **tm3;
    tm3 = (int **)malloc(r * sizeof(*tm3));
    fl(k,r)
        tm3[k] = (int *)malloc(r * sizeof(*tm3[k]));

    fl(i, r)
    {
        fl(j, r)
        {
            tm3[j][i] = ((key[(i + 1) % 3][(j + 1) % 3] * key[(i + 2) % 3][(j + 2) % 3]) % 26 - (key[(i + 1) % 3][(j + 2) % 3] * key[(i + 2) % 3][(j + 1) % 3]) % 26 + 26) % 26;
        }
    }
    return tm3;
}
int d, x, y;
void modulofun(int num, int m)
{ //m=26
    if (m == 0)
    {
        d = num;
        x = 1;
        y = 0;
    }
    else
    {
        modulofun(m, num % m);
        int temp = x;
        x = y;
        y = temp - (num / m) * y;
    }
}
int moduloinverse(int num, int m)
{
    modulofun(num, m);
    if (d == 1) // if we repace this then it will work for non coprimes too.
    {
        return (x % m + m) % m;
    }else
        cout <<"Not invertible "<<"gcd("<<num<<","<<m<<") != 1\n";
        exit(1);
    return 0;
}
int determ2d(int **key)
{
    return (key[0][0] * key[1][1] - key[0][1] * key[1][0]);
}
int determ3d(int **key)
{
    return (key[0][0] * (key[1][1] * key[2][2] - key[1][2] * key[2][1]) - key[0][1] * (key[1][0] * key[2][2] - key[1][2] * key[2][0]) + key[0][2] * (key[1][0] * key[2][1] - key[1][1] * key[2][0]));
}
int **inversemat(int **key, int determinant, int r)
{
    int invmodulo = moduloinverse(determinant, 26);
    if (invmodulo != 0)
    {
        fl(i, r)
        {
            fl(j, r)
            {
                key[i][j] = ((key[i][j] * invmodulo) % 26 + 26) % 26;
            }
        }
        return key;
    }
}
int main()
{
    char ch; //e= encryption & d= decryption
    int n;   //n*n dimention of key matrix
    while (1)
    {
        cout << "Encryption /Decryption ?";
        cin >> ch;
        cout << "Key size :-";
        cin >> n;
        string keyname, textinname, textoutname, word, text1 = "", key1 = "", tout1 = "", cptext = "";
        cout << "key ,input text  and output text file names :-";
        cin >> keyname >> textinname >> textoutname;
        ifstream filekey(keyname, ios::in);
        ifstream filein(textinname, ios::in);
        ofstream fileout(textoutname, ios::out);
        if (filein.is_open())
            while (filein >> word)
            {
                text1.append(word);
            }
        filekey >> key1;

        transform(key1.begin(), key1.end(), key1.begin(), ::toupper);
        transform(text1.begin(), text1.end(), text1.begin(), ::toupper);
        if (ch == 'e' || ch == 'E')
        {
            fln(i, text1.length(), n)
            {
                string subst = text1.substr(i, n);
                int *cipher;
                cipher = (int *)malloc(n * sizeof(int));
                cipher = multimatrix(keymat(key1, n), textmat(subst, n), n);
                cptext.append(intTochar(cipher, n));
            }
        }
        else if (ch == 'd' || ch == 'D')
        {
            fln(i, text1.length(), n)
            {
                string subst = text1.substr(i, n);
                int *cipher = (int *)malloc(n * sizeof(int));
                int **invkey = (int **)malloc(n * sizeof(*invkey));
                fl(j, n)
                    invkey[j] = (int *)malloc(n * sizeof(*invkey[j]));
                if (n == 2)
                    invkey = inversemat(trans2d(keymat(key1, n), n), determ2d(keymat(key1, n)), n);
                else if (n == 3)
                    invkey = inversemat(trans3d(keymat(key1, n), n), determ3d(keymat(key1, n)), n);

                cipher = multimatrix(invkey, textmat(subst, n), n);
                cptext.append(intTochar(cipher, n));
            }
        }
        else
            break;
        fileout << cptext;
        filein.close();
        filekey.close();
        fileout.close();
    }
}