#include <bits/stdc++.h>
#define fl(i, n) for (int i = 0; i < n; i++)
#define pare pair<int, int>
#define dque deque<pair<int, int>>
using namespace std;
int search(dque arr, int v1, int v2)
{
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i].first == v1 && arr[i].second == v2 || arr[i].first == v2 && arr[i].second == v1)
        {
            return 1;
        }
    }
    return 0;
}
void matrix(string sin)
{
    string word, text = "", key;
    int wordint;
    ifstream ifile1(sin, ios::in);
    ofstream ofile("matirx.txt", ios::out);
    if (ifile1.is_open())
    {
        while (ifile1 >> word)
        {
            text.append(word);
        }
    }
    int i = -1;
    int n1, n2;
    char temp;
    vector<int> nodes;
    set<int> vertes;
    while (text[++i])
    {
        if (isalpha(text[i]))
        {
            temp = toupper(text[i]);
            nodes.push_back((temp - 'A'));
            vertes.insert((temp - 'A'));
        }
    }
    dque pairs;
    for (int i = 0; i < (nodes.size()); i += 2)
    {
        pairs.push_back({nodes[i], nodes[i + 1]});
        //cout << "nodes" << nodes[i] << " " << nodes[i + 1] << endl;
    }
    int vsz = vertes.size();
    int mat[vsz][vsz];
    for (int r = 0; r < vsz; r++)
    {
        for (int c = 0; c < vsz; c++)
        {
            mat[r][c] = search(pairs, r, c);
            ofile << mat[r][c] << " ";
        }
        ofile << "\n";
    }
    ofile.close();
}
void pathfind(int vertex , dque graph){
    vector<char> path;
    ofstream ofile("path.txt", ios::out);
    int temp1 = vertex,temp2 = vertex;
    for(int i =0; i< graph.size(); i++){
        if(graph[i].first == temp1){
            path.push_back('A'+graph[i].second);
            ofile<< 'A'+graph[i].second<<" ";
            temp1 = graph[i].second;
        }else if(graph[i].second == temp2){
            path.push_back('A'+graph[i].first);
            ofile<< 'A'+graph[i].first<<" ";
            temp2 = graph[i].first;
        }
    }
}

void path(string sin)
{
    string word, text = "", key;
    int wordint;
    ifstream ifile1(sin, ios::in);
    ofstream ofile("matirx.txt", ios::out);
    if (ifile1.is_open())
    {
        while (ifile1 >> word)
        {
            text.append(word);
        }
    }
    int i = -1;
    int n1, n2;
    char temp;
    vector<int> nodes;
    set<int> vertes;
    while (text[++i])
    {
        if (isalpha(text[i]))
        {
            temp = toupper(text[i]);
            nodes.push_back((temp - 'A'));
            vertes.insert((temp - 'A'));
        }
    }
    dque pairs;
    for (int i = 0; i < (nodes.size()); i += 2)
    {
        pairs.push_back({nodes[i], nodes[i + 1]});
    }
    int vsz = vertes.size();
    int mat[vsz][vsz];
    for (int r = 0; r < vsz; r++)
    {

    }
    ofile.close();
}

int main()
{
    string fileinput;
    int x;
    cout << "Enter number for matrix and path 1/0 and filename:-";
    cin >> x >> fileinput;
    while (1)
    {
        if (x == 1)
        {
            matrix(fileinput);
        }
        else if (x == 0)
        { /*
            cout << "Enter the input filename and output filename :-";
            cin >> fileinput >> fileoutput;
            paths(fileinput, fileoutput, keyfile);*/
        }
        else
            break;
        cout << "Enter number for encryption and decryption 1/0:-";
        cin >> x;
    }
}