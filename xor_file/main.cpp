#include <iostream>
#include <cstdint>
#include <fstream>
#include <array>

using namespace std;

constexpr size_t KEY_SIZE_BYTES = 2048 / 8;


int main(int argc, char* argv[]){


    ifstream file_byte(argv[1], ios::binary);
    
    char byte;
    string u_byte_text_file, u_byte_key;
    while(file_byte.get(byte)){
        int i = 0;
        u_byte_text_file += static_cast<unsigned char>(byte);
        
        // cout << hex << static_cast<unsigned int>(u_byte_text_file[i]) << " ";
    }
    byte = char(NULL);
    ifstream key_byte("key.k", ios::binary);
    while (key_byte.get(byte))
    {
        int i = 0;
        u_byte_key += static_cast<unsigned char>(byte);
        
        // cout << hex << static_cast<unsigned int>(u_byte_key[i]) << " ";
    }
    
    for (size_t i = 0; i < u_byte_text_file.size(); i++)
    {
        u_byte_text_file[i] ^= u_byte_key[i % sizeof(u_byte_key)];
    }
    ofstream in_file(argv[1]);
    in_file << hex << u_byte_text_file;
    file_byte.close();
    key_byte.close();
    return 0;
}
