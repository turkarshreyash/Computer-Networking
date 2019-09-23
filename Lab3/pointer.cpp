#include<iostream>
#include<string.h>

struct temp{
    char *a;
    int b;
};

struct temp_2{
    char a[256];
    int b;
};

int main(){
    temp *temp_struct = new temp;
    temp_struct->a = new char[256];
    strcpy(temp_struct->a,"Hello world");
    std::cout<<temp_struct->a<<"\n";
}