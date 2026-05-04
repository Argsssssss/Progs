#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

int main(int argc, char *argv[]) {

  char *name_user = argv[1];
  char byte = char(9);
  int client;
  sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8080); /* рекомендуется всегда использовать htons() 
  для преобразования порта в сетевой порядок байт, чтобы гарантировать корректную 
  работу вашего сетевого приложения на разных платформах.
  */
  // addr.sin_addr.s_addr = htons(INADDR_LOOPBACK); // INADDR_LOOPBACK - адрес интерфейса внутренней петли (loopback interface)
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  

  // файловый дескриптор (число)
  client = socket(AF_INET, SOCK_STREAM, 0);

  if (client >= 0) 
    cout << "Сокет успешно создался" << endl;
  else {
    cout << "Проблема создания сокета";
    return 1;
  }

  if (connect(client, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
    cout << "Не удалось подключится";
    return 1;
  } else {
    cout << "TEST" << endl;
    send(client, name_user, sizeof(name_user), 0);
    string message = " ";
    while(true){
        message = "";
        getline(cin, message);
        cout << message;
        send(client, message.c_str(), message.size(), 0);
    }
    cout << "Отправил ваше сообщение: " << message << endl;
  }

  return 0;
}