#include <bits/stdc++.h>
using namespace std;
int main()
{
    ifstream kiki("votein.txt");
    ofstream pc("kiki.txt");
    int ls;
    int e=0;
    while (kiki>>ls)
    {
        if(ls>=10)
        {
           pc<<ls<<" "; 
        }
        else
        {
            pc<<ls<<"  ";
        }
        e++;
        if(e==10)
        {
            pc<<endl;
            e=0;
        }
    }
    
}