#include <iostream>

using namespace std;

int main(void)
{
    // char anschar[42] ={0xDD,0x5B,0x9E,0x1D,0x20,0x9E,0x90,0x91,
    //                0x90,0x90,0x91,0x92,0xDE,0x8B,0x11,0xD1,
    //                0x1E,0x9E,0x8B,0x51,0x11,0x50,0x51,0x8B,
    //                0x9E,0x5D,0x5D,0x11,0x8B,0x90,0x12,0x91,
    //                0x50,0x12,0xD2,0x91,0x92,0x1E,0x9E,0x90,
    //                0xD2,0x9F};

    unsigned char ansint[42] ={0xDD,0x5B,0x9E,0x1D,0x20,0x9E,0x90,0x91,
                   0x90,0x90,0x91,0x92,0xDE,0x8B,0x11,0xD1,
                   0x1E,0x9E,0x8B,0x51,0x11,0x50,0x51,0x8B,
                   0x9E,0x5D,0x5D,0x11,0x8B,0x90,0x12,0x91,
                   0x50,0x12,0xD2,0x91,0x92,0x1E,0x9E,0x90,
                   0xD2,0x9F};
    bool flag=0;
    for(int i=0;i<42;i++)
    {
        flag=0;
        for(char trynow=0;trynow<=126;trynow++)
        {
            //cout << "try now: " << trynow << ' ';

            char left = char(trynow<<6);
            char right = (int)(unsigned)trynow >> 2;
            unsigned char ans1 = left ^ right;
            unsigned char ans2 = ans1 ^ 0x23u;
            unsigned char ans3 = ans2 + 35;
            if(ans3 == ansint[i])
            {
                //cout << endl << endl << (char)trynow << endl << endl;
                cout << (char)trynow;
                flag=1;
                break;
            }
        }
        if(flag==0)
        ;
            // cout << "|failed: " << i << endl << endl;
    }

    return 0;
}

flag{a959951b-76ca-4784-add7-93583251ca92}