#include <iostream>
using namespace std;
char temp=0;
char now=0;
int j;
string target = "Zxb3xo_qe4_Dob@q";
bool check(char nowwhat,int which)      //检查对不对，对的话返回1
{
    if(nowwhat==target[which])
        return 1;
    else
        return 0;
}

// target str
// Zxb3xo_qe4_Dob@q
// Z x b 3 x   o _ q e 4   _ D o b @   q
// 90 120 98 51 120 111 95 113 101 52 95 68 111 98 64 113
int main(void)
{

    char ans[16] = {0};
    for ( int i = 0; i < 16; ++i )
    {
        for(temp = 0;temp<=255;temp++)
        {
            if ( temp < 65 || temp > 90 )
            {
                if ( temp < 97 || temp > 122 )
                {
                    now = temp;
                    if(check(now,i))
                    {
                        ans[i] = temp;
                        break;
                    }
                    else
                        continue;
                }
                else
                {
                    for ( j = temp - 100; j < 0; j += 26 )
                        ;
                    now = j + 97;
                    if(check(now,i))
                    {
                        ans[i] = temp;
                        break;
                    }
                    else
                        continue;
                }
            }
            else
            {
                for ( j = temp - 68; j < 0; j += 26 )
                ;
                now = j + 65;
                if(check(now,i))
                    {
                        ans[i] = temp;
                        break;
                    }
                    else
                        continue;
            }
        }
    }

    cout << "the ans is:" << endl;
    for(int i=0;i<16;i++)
        cout << ans[i];
    cout << endl;
    return 0;
}

//Cae3ar_th4_Gre@t