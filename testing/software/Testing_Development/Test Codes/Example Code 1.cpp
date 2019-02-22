/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

This is an example of:
(1) how to change char array elements
(2) how to print using iostream
(3) how to make a for loop

*******************************************************************************/

#include <iostream>

using namespace std;

struct HexCharStruct
{
  unsigned char c;
  HexCharStruct(unsigned char _c) : c(_c) { }
};

inline std::ostream& operator<<(std::ostream& o, const HexCharStruct& hs)
{
  return (o << std::hex << (int)hs.c);
}

inline HexCharStruct hex(unsigned char _c)
{
  return HexCharStruct(_c);
}

int main()
{
    unsigned char stmp[8] = {0xC0, 0x29, 0xEE, 0x00, 0x00, 0x00, 0x00, 0x00};
    
    stmp[0] = 0x01;
    
    for( int i = 0; i < (sizeof(stmp)/sizeof(*stmp)); i++ ) {
    cout << "for i: "<< i << endl << "We have: " << hex(stmp[i]) << endl;
    }

}
