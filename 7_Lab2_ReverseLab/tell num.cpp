#include<iostream>
using namespace std;

int main(void)
{
    int whichone;
    cout << "you want char2int or int2char?  answer with 1 or 2"  << endl;
    cin >> whichone;
    if(whichone == 2)
    {
        int howmany;
        cout << "how many int_8 to char?" << endl;
        cin >> howmany;
        cout << "now enter int" << endl;
        for(int i=0;i<howmany;i++)
        {
            int temp;
            cin >> temp;
            cout << (char)temp << ' ';
        }
    }
    else if(whichone == 1)
    {
        int howmany;
        cout << "how many char to int_8" << endl;
        cin >> howmany;
        cout << "now enter char" << endl;
        for(int i=0;i<howmany;i++)
        {
            char temp;
            cin >> temp;
            cout << (int)temp << ' ';
        }
    }
    else
    {
        cout << "sorry, we dont have this service" << endl;
    }

    getchar();
    getchar();
    getchar();
    getchar();
    getchar();
    return 0;
}