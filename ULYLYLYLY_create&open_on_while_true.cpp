#include <iostream>
using namespace std;

#define mem(open_file){int i = 0;while(i < 10){string create = "echo ULYLYLYLYLYLYLYLYLYLYLYLYLYLYLYLYYLYLYYLYLYLLYYLYLYLYLYLY > qwe_", BUFF = open_file;create += to_string(i) + ".txt";open_file += to_string(i) + ".txt";const char* com_create = create.c_str();const char* com_open = open_file.c_str();system(com_create);system(com_open);open_file = BUFF;i++;clear();}}

#if defined(_WIN32) || defined (_WIN64)
    string open_file = "start qwe_";
    void clear(){
        system ("cls");
    }
    void open(){mem(open_file);}
#elif defined(unix)
    string open_file = "open qwe_";
    void clear(){
        system ("clear");
    }
    void open(){mem(open_file);}
#else 
    #error "Platform is not supported"
#endif

int main(){
    open();
    return 0;
}
