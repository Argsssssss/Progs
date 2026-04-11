#include <iostream>
#include <chrono>
#include <time.h>
#include <thread>
using namespace std;
#if defined(_WIN32) || defined(_WIN64) 
    #define WINDOWS
    #include <conio.h>
#elif defined(unix)
    #define UNIX
    char getch(void);
    int _kbhit(void);
#else
    #error "Platform is not supported go to play minecraft"
#endif
void clear (void) {
    #ifdef WINDOWS
        system("cls");
    #else
        system("clear");
    #endif
}
#ifdef UNIX
    char getch (void) {
        char ch;
        system("stty raw");
        ch = getchar();
        system("stty cooked");
        return ch;
    }
    #ifndef KBHIT_H
    #define KBHIT_H
    #include <termios.h>
    class keyboard{
        public:
            keyboard();
            ~keyboard();
            int _kbhit();
            int getch();

        private:
            struct termios initial_settings, new_settings;
            int peek_character;
    };
    #endif
    #include <unistd.h> // read()
    keyboard::keyboard(){
        tcgetattr(0,&initial_settings);
        new_settings = initial_settings;
        new_settings.c_lflag &= ~ICANON;
        new_settings.c_lflag &= ~ECHO;
        new_settings.c_lflag &= ~ISIG;
        new_settings.c_cc[VMIN] = 1;
        new_settings.c_cc[VTIME] = 0;
        tcsetattr(0, TCSANOW, &new_settings);
        peek_character=-1;
    }
    keyboard::~keyboard(){
        tcsetattr(0, TCSANOW, &initial_settings);
    }
    int keyboard::_kbhit(){
        unsigned char ch;
        int nread;
        if (peek_character != -1) return 1;
        new_settings.c_cc[VMIN]=0;
        tcsetattr(0, TCSANOW, &new_settings);
        nread = read(0,&ch,1);
        new_settings.c_cc[VMIN]=1;
        tcsetattr(0, TCSANOW, &new_settings);

        if (nread == 1){
            peek_character = ch;
            return 1;
        }
        return 0;
    }
    int keyboard::getch(){
        char ch;

        if (peek_character != -1){
            ch = peek_character;
            peek_character = -1;
        }
        else read(0,&ch,1);
        return ch;
    }
#endif

struct Obj_position{int x, y;};
Obj_position car, bar;




int square_map[2] = {3, 9};
int speed = 500;
bool game_over = true;
int score = 0, rand_bar_symb = 0;
string car_symb = "H", obj = "*", bar_symb = "_-=+#$%&[]";
void default_position(void){
    car.x = 8;
    car.y = 2;
    srand(time(0));
    bar.x = -1;
    bar.y = rand() % square_map[0];
    rand_bar_symb = rand() % 10;
}
void respawn_bar(){
    srand(time(0));
    rand_bar_symb = rand() % 10;
    bar.x = -1;
    bar.y = rand() % square_map[0];
}
void map(){
    cout << "Score: " << score << endl;
    for(int i = 0; i < square_map[1] - 2; i++){
        cout << '#';
    }cout << '\n';
    for(int i = 0; i < square_map[1]; i++){
        for(int j = 0; j < square_map[0] + 1; j++){
            if(j == 0){
                if(i == bar.x && j == bar.y){
                    cout << "|" << bar_symb[rand_bar_symb];
                }
                else if(i == car.x && j == car.y){
                    cout  << "|" << car_symb;
                }else{
                    cout << "| ";
                }
                
            }else if(j == 1){
                if(i == bar.x && j == bar.y){
                    cout << "|" << bar_symb[rand_bar_symb];
                }
                else if(i == car.x && j == car.y){
                    cout << "|" << car_symb;
                }else{
                    cout << "| ";
                }
            }
            else if(j == 2){
                if(i == bar.x && j == bar.y){
                    cout << "|" << bar_symb[rand_bar_symb];
                }
                else if(i == car.x && j == car.y){
                    cout << "|" << car_symb;
                }else{
                    cout << "| ";
                }
            }
            else{cout << "|";}
        }
        cout << endl;
    }
    for(int i = 0; i < square_map[1] - 2; i++){
        cout << '#';
    }cout << '\n';

    // cout << car.x << "|" << car.y << " | "<<  bar.x << "|"<< bar.y << endl;
    bar.x++;
    this_thread::sleep_for(chrono::milliseconds(speed));
    clear();
}
void input_key(){
      keyboard keyb;
        if(keyb._kbhit()){
            switch (keyb.getch())
            {
            // car.x = 8;
            // car.y = 2; square_map[2] = {3, 9};
            case 'a':
                if(car.y != 0){car.y--;}
                break;
            case 'd':
                if(car.y != square_map[0] - 1){car.y++;}
                break;
            case 'w':
                if(car.x != 0){if(car.x - 1 == bar.x && car.y == bar.y){break;}else{car.x--;}}
                break;
            case 's':
                if(car.x != square_map[1] - 1){car.x++;}
                break;
        }
    }
}
void logic(){
    if(car.x == bar.x && car.y == bar.y){
        game_over = false;
    }
    if(bar.x > square_map[1] - 1){
        respawn_bar();
        if(speed > 15 && speed < 25){
            speed -= 12;
        }else if(speed > 25){
            speed -= 8;
        }else{
            speed -= 15;
        }
        score++;
    }
}
void game(){
    default_position();
    while(game_over){
        map();
        input_key();
        logic();
    }
    cout << "__________Game over__________\n" <<"___________Score: " << score << "__________"<< endl;
}
int main(void){
    game();
    // Должно быть 4 хуйни на дороге, + по две штуки за раз
    return 0;
}