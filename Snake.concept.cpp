#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <random>
#include <time.h>
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

struct Point{
    int x;
    int y;
};
//Дефолтные значения
int square_map[2]={15,15}; // Размер карты
int speed_snake = 500; // Скорость, по факту тайминг обновления карты в МС
bool game_over = false; // Флаг проигрыша
int score = 0;
string snake_str = "0 ";
string symb_fruit = "F ";


enum eDirection{ Stop = 0, Left, Right, Down, Up};
eDirection dir;
Point generate_fruit(int sqare_map[], Point snake);
Point generate_snake(int sqare_map[]);
bool game(int square_map[], int speed_snake);
void logic();
void input();
void map();
int start();
int negat_mod(int num, int mod);

int main(){ /////////////////////////////////////////////////////////////////////////////////MAIN
    start();
    return 0;
}

int negat_mod(int num, int mod){
    if(num < 0){
        while(num < 0){
            num += mod;
        }
        return num;
    }
    return num;
}
Point generate_snake(int sqare_map[]){
    srand(time(0));
    Point snake;
    snake.x = rand() % sqare_map[0], snake.y = rand() % sqare_map[1];
    return snake;
}
Point generate_fruit(int sqare_map[], Point snake){
    srand(time(0));
    Point fruit;
    fruit.x = rand() % sqare_map[0], fruit.y = rand() % sqare_map[1];
    if(snake.x == fruit.x && snake.y == fruit.y){   
        while(snake.x != fruit.x && snake.y != fruit.y){fruit.x = rand() % sqare_map[0], fruit.y = rand() % sqare_map[1];}
    }
    return fruit;
}
Point snake = generate_snake(square_map);
Point fruit = generate_fruit(square_map, snake);

bool game(){
    
    while(game_over == false){
        map();
        input();
        logic();
    }
    return 0;
}
int start(){
    
    menu:
        clear();
        string pick[] = {
            "--------Select--------\n",
            "|      1 - Start     |\n",
            "|      2 - Searting  |\n",
            "|      3 - Exit      |\n",
            "----------------------\n",
            "U pick: "
            };
        for (size_t i = 0; i < 6; i++)
        {
            for (size_t j = 0; j < pick[i].size(); j++)
            {
                cout << pick[i][j];
            }
        }
        switch (getch())
        {
            case '1': goto game;
            case '2': goto searting;
            case '3': exit;
            default: break;
        };

    exit:return 0;

    game:
        clear();
        game();

        goto menu;

    searting:
        clear();
        printf("-------------Searting-------------\n");
        printf("|  1 - Screen Resolution %d x %d |\n",square_map[0], square_map[1]);
        printf("|  2 - Velocity          %d (MS)|\n",speed_snake);
        printf("|  3 - Exit                      |\n----------------------------------\n");
        switch (getch())
        {
            case '1': 
                cout << "\nEnter X: ";
                cin >> square_map[0];
                cout << endl;
                cout << "Enter Y: ";
                cin >> square_map[1];
                goto searting;
            case '2':
                cout << "\nEnter the speed parameter: ";
                cin >> speed_snake;
                goto searting;
            case '3': goto menu;
            default: goto searting;
        };

    return 0;
}
void map(){
    cout << "Score: " << score << endl;
        for (size_t i = 0; i < square_map[1] + 2; i++)
        {
            cout << "# ";
        }cout << endl;
        
        for (size_t i = 0; i < square_map[0] + 1; i++)
        {
            for (size_t j = 0; j < square_map[1] + 1; j++)
            {
                if(j == 0 || j == square_map[1]){
                    cout << "# ";
                }
                
                if(i == snake.y && j == snake.x){
                    cout << snake_str;
                }else if(i == fruit.y && j == fruit.x){
                    cout << symb_fruit;
                }else{
                    cout << "  ";
                }
                
                
                
            }
            cout << endl;
        }
        for (size_t i = 0; i < square_map[1] + 2; i++)
        {
            cout << "# ";
        }cout << endl;
        this_thread::sleep_for(chrono::milliseconds(speed_snake));
        clear();
}
void input()
{
    keyboard keyb;
        if(keyb._kbhit()){
            switch (keyb.getch())
            {
            case 'a':
                dir = Left;
                break;
            case 'w':
                dir = Up;
                break;
            case 's':
                dir = Down;
                break;
            case 'd':
                dir = Right;
                break;
            case 'p':
                dir = Stop;
                start();
                break;
        }
    }
}
void logic(){
    switch (dir)
    {
    case Left:
        snake.x--;
        snake.x = negat_mod(snake.x, square_map[1]);
        break;
    case Right:
        snake.x++;
        snake.x %= square_map[1];
        break;
    case Up:
        snake.y--;
        snake.y = negat_mod(snake.y, square_map[1]);
        break;
    case Down:
        snake.y++;
        snake.y %= square_map[0];
        break;
    }
    
    if(snake.x == fruit.x && snake.y == fruit.y){
        score++;
        fruit = generate_fruit(square_map, snake);
        // snake_str += '0';
    }
}
