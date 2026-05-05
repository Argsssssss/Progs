#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

void clear_buff(char mass[], int size){
    for(int i = 0; i < size; i++){
        mass[i] = char(NULL);
    }
}

int main(int argc, char *argv[]) {

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080); /* рекомендуется всегда использовать htons() 
    для преобразования порта в сетевой порядок байт, чтобы гарантировать корректную 
    работу вашего сетевого приложения на разных платформах.
    */
    addr.sin_addr.s_addr = htons(INADDR_ANY); // INADDR_LOOPBACK - адрес интерфейса внутренней петли (loopback interface)
    // addr.sin_addr.s_addr = inet_addr();

    int server = socket(AF_INET, SOCK_STREAM, 0);

    if (bind(server, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        cout << "Не удалось связать сокет сервера с адресом." << endl;
        return 1;
    }
    else 
        cout << "Порт открыт" << endl;
    
    if (listen(server, 1) == 0) {
        cout << "Сокет стал в режим прослушки" << endl;
        
        int client;
        char user[10];
        if ((client = accept(server, nullptr, nullptr)) < 0) {
            cout << "Не получилось соединится с клиентом" << endl;
            close(server);
            return -1;
        }
        else{
            recv(client, user, 1024, 0);
            cout << "Успешное соединение с клиентом" << endl;
            

        char buf[1024];
        int bytes_read;
        
        while(true){   
            clear_buff(buf, sizeof(buf) / 4); // обнуление строки, иначе запоминает и выводит старые записаные...
            if ((bytes_read = recv(client, buf, 1024, 0)) == 0) {
                cout << "Соединение разорвано";
                return 1;
            }
            else {
                if(buf[0] == '1'){
                    cout << "Welcome to game!!!\n";
                }else if(buf[0] == '0'){
                    close(client);
                    close(server);
                    return 1;
                }
                cout << user << ": " << buf << endl;
            }}

        // close(client);
        }
    }
    else {
        close(server);
        cout << "Какая то фигня";
        return 1;
    }

    close(server);


    return 0;
}
