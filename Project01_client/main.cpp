//
//  main.cpp
//  Project01_client
//
//  Created by Ольга Полевик on 25.10.2021.
//

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>
#include <sys/socket.h> // Библиотека для работы с сокетами
#include <arpa/inet.h>
using namespace std;
 
 
// Максимальный размер буфера для приема и передачи
#define MESSAGE_BUFFER 1024
#define PORT 7777 // номер порта, который будем использовать для приема и передачи
 
 
char buffer[MESSAGE_BUFFER];
string message;
int socket_descriptor;
struct sockaddr_in serveraddress;
 
void sendRequest(){
    // Укажем адрес сервера
    serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    // Зададим номер порта для соединения с сервером
    serveraddress.sin_port = htons(PORT);
    // Используем IPv4
    serveraddress.sin_family = AF_INET;
    // Создадим сокет
    socket_descriptor = socket(AF_INET, SOCK_DGRAM, 0);
    // Установим соединение с сервером
    if(connect(socket_descriptor, (struct sockaddr*) &serveraddress, sizeof(serveraddress)) != 0) {
        cout << endl << " Something went wrong Connection Failed" << endl;
        exit(1);
    }
    
    //резервирует место под данные которые будем отправлять одним пакетом
    
    message.reserve(MESSAGE_BUFFER);
    
    while(1)
    {
        // cout << "Enter a message you want to send to the server: " << endl;
        cin >> message;
     
        sendto(socket_descriptor, message.data(), MESSAGE_BUFFER, 0, nullptr, sizeof(serveraddress));
                
        recvfrom(socket_descriptor, buffer, sizeof(buffer), 0, nullptr, nullptr);
        // cout << "Message Received From Server: " << endl;
        cout <<  buffer << endl;
       
        if (!strcmp( buffer, "c") )
        {
            break;
        }

    }
    cout << "Client work is done.!" << endl;
    // закрываем сокет, завершаем соединение
    close(socket_descriptor);
}
 
int main() {
    cout << "CLIENT IS ESTABLISHING A CONNECTION WITH SERVER THROUGH PORT: " << PORT << endl;
    cout << "Enter char to begin" << endl;
    sendRequest();
    return 0;
}

