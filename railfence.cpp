#include <bits/stdc++.h>
#define fl(i, n) for (int i = 0; i < n; i++)
using namespace std;
int *keyarr(string key)
{
    int *arr = (int *)malloc(key.size() * sizeof(int));
    map<char, int> indexedkey;
    for (int i = 0; key[i]; i++)
    {
        indexedkey[key[i]] = i;
    }
    int ii = 0;
    for (auto it = indexedkey.begin(); it != indexedkey.end(); it++)
        arr[ii++] = it->second;
    return arr; //first which line should i read
}
string ntransposecipher(char **matrix, string text, int *key, float ksz)
{
    float tsz = text.size();
    //text to matrix
    fl(row, ceil(tsz / ksz))
    {
        fl(col, ksz)
        {
            if (!text[row * ksz + col])
                text[row * ksz + col] = 'x';
            matrix[row][col] = text[row * ksz + col];
        }
    }
    //matrix  to cipher
    string cipher;
    fl(col, ksz)
    {
        fl(row, ceil(tsz / ksz))
        {
            cipher.push_back(matrix[row][key[col]]);
        }
    }
    return cipher;
}
string ntransposetext(char **matrix, string ciphertext, int *key, float ksz)
{
    float tsz = ciphertext.size();
    //cipher to matrix
    fl(col, ksz)
    {
        fl(row, ceil(tsz / ksz))
        {
            matrix[row][key[col]] = ciphertext[col * ceil(tsz / ksz) + row];
        }
    }
    //matrix  to text
    string text1;
    fl(row, ceil(tsz / ksz))
    {
        fl(col, ksz)
        {
            text1.push_back(matrix[row][col]);
        }
    }
    return text1;
}

void encyption(string sin, string sout, int *key, int ksz, int ntimes)
{
    string word, text;
    int wordint;
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
    float tsz = text.size();
    char **matrix = (char **)malloc(tsz * sizeof(char *));
    fl(i, tsz)
    {
        matrix[i] = (char *)malloc(ksz * sizeof(char));
    }
    string cipher;
    fl(k, ntimes)
    {
        text = ntransposecipher(matrix, text, key, ksz);
    }
    cipher = text;
    ofile << cipher;
    ifile1.close();
    ofile.close();
}
void decryption(string sin, string sout, int *key, int ksz, int ntimes)
{
    string word, text;
    int wordint;
    ifstream ifile1(sin, ios::in);
    ofstream ofile(sout, ios::out);
    if (ifile1.is_open())
    {
        while (ifile1 >> word)
        {
            text.append(word);
        }
    }
    float tsz = text.size();
    char **matrix = (char **)malloc(tsz * sizeof(char *));
    fl(i, tsz)
    {
        matrix[i] = (char *)malloc(ksz * sizeof(char));
    }
    fl(k, ntimes)
    {
        text = ntransposetext(matrix, text, key, ksz);
    }

    ofile << text;

    ifile1.close();
    ofile.close();
}
void printing(int x, int y, int **arr)
{
    fl(i, x)
    {
        fl(j, y)
        {
            cout << arr[i][j] << " ";
        }
        cout << "\t" << i << "\n";
    }
}
int main()
{
    fstream file;
    string fileinput, fileoutput, key;
    int x, ksz, ntime;

    cout << "Enter number for encryption , decryption 1/0 :-";
    cin >> x;
    cout << "Enter the key as string and no. of times to encrypt:-";
    cin >> key >> ntime;
    //int *key1 = (int *)malloc(key.size()*sizeof(int));
    int *key1 = keyarr(key);
    ksz = key.size();
    while (1)
    {
        if (x == 1)
        {
            cout << "Enter the input filename and output filename :-";
            cin >> fileinput >> fileoutput;
            encyption(fileinput, fileoutput, key1, ksz, ntime);
        }
        else if (x == 0)
        {
            cout << "Enter the input filename and output filename :-";
            cin >> fileinput >> fileoutput;
            decryption(fileinput, fileoutput, key1, ksz, ntime);
        }
        else
            break;
        cout << "Enter number for encryption and decryption 1/0:-";
        cin >> x;
    }
}