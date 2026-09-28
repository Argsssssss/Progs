#include <array>
#include <cstdint>
#include <fstream>
#include <random>
using namespace std;

constexpr size_t KEY_SIZE_BYTES = 2048 / 8;

array<uint8_t, KEY_SIZE_BYTES> rc4(){
    random_device RNDOM;
    array<uint8_t, KEY_SIZE_BYTES> privateKey2048;
    array <uint8_t, 255>S;
    int j = 0;
    for(size_t i = 0; i < 255;i++){
        S[i] = i;
    }
    for(size_t i = 0; i < 255;i++){
        j = (j + S[i] + RNDOM()) % KEY_SIZE_BYTES;
        swap(S[i], S[j]);
    }
    for(size_t i = 0, t, buff_i, buff_j; i < 255; i++){
        buff_i = (buff_i + 1) % KEY_SIZE_BYTES;
        buff_j = (buff_j + S[buff_i]) % KEY_SIZE_BYTES;
        swap(S[buff_i], S[buff_j]);
        t = (S[buff_i] + S[buff_j]) % KEY_SIZE_BYTES;
        privateKey2048[i] += S[t];
       
    }
    
    return privateKey2048;
}

void rec_key(array<uint8_t, KEY_SIZE_BYTES> privateKey){

    ofstream infile("key.k");
    for (auto &&i : privateKey)
    {
        infile << hex << i;
    }
}
int main(){
    rec_key(rc4());
}