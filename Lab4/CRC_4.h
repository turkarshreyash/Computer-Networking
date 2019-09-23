#include<iostream>

#ifndef CRC_4

class CRC{
    static int divisor[4];
    static int temp[4];
    static bool copy(int*,int , int);
    static void _xor();
    public:
        static void generate_CRC(int*, int);
        static void get_reminder();
};

#endif