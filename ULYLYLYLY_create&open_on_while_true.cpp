#include <iostream>

using namespace std;

#if defined(_WIN32) || defined (_WIN64)
    void clear(){
        system ("cls");
    }
    void open(){

    }
#elif defined(unix)
    void clear(){
        system ("clear");
    }
    void open()
    {   int i = 0;
        while(true){
            string create = "echo ULYLYLYLYLYLYLYLYLYLYLYLYLYLYLYLYYLYLYYLYLYLLYYLYLYLYLYLY > qwe_", open = "open qwe_";
            create += to_string(i) + ".txt";
            open += to_string(i) + ".txt";
            const char* com_create = create.c_str();
            const char* com_open = open.c_str();
            system(com_create);
            system(com_open);
            i++;
            clear();
        }
    }
#else 
    #error "Platform is not supported"

#endif

int main(){
    open();
    return 0;
}
