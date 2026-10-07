#include <iostream>
#include <math.h>
using namespace std;

u_int8_t pat[4] = {0x04, 0x03, 0x01, 0x02};
void print_byte(u_int64_t num){
    for (size_t i = 0; i < 65; i++)
    {   
        if(num - (pow(2, 64 - i)) >= 0){
            num <<= i + 1;
            num >>= i + 1;
            cout << '1';
        }else{
            if(i != 0){
                cout << '0';
            }
        }
    }
}
u_int64_t shift(u_int64_t num){
    u_int64_t buff = 0;
    for (u_int8_t i = 0; i < 4; i++)
    {   
        buff |= ((num >> (4 - pat[i])) & 0x1) << (3 - i);
        print_byte(buff);
        cout << (int)buff << '\n';
    }
    return buff;
}
u_int64_t str_to_uint(string mes){
    u_int64_t buff = 0;
    for (size_t i = 0; i < mes.size(); i++)
    {
        buff |= mes[i];
        i != mes.size() - 1 ? buff <<= 8 : buff; 
    }
    return buff;
}
string uint_to_str(u_int64_t mes_byte){
    string mes(8,char(NULL));
    for(int i = 0; i < 8; i++){
        mes[i] |= (mes_byte >> 64 - ((i + 1) * 8)) & 0x7F;
    }
    return mes;
}
int main(void){
    string mes = "ABCDEFGH";
    mes = uint_to_str(str_to_uint(mes));
    for (size_t i = 0; i < mes.size(); i++)
    {
        print_byte(mes[i]);
        cout << '\n';
    }
    cout << mes;
    return 0;
}
