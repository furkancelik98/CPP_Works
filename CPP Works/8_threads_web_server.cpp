/*

Web Sunucusu:
Bu basit web sunucusu, gelen HTTP GET isteklerine yanıt vermek için çoklu iş parçacıklarını kullanır. İstemcilerin sunucuya bağlanmasına izin 
verir ve basit bir "Merhaba, Dünya!" yanıtı gönderir.

Kullanım:

1.Kodu derleyin: g++ -o webserver 8_threads_web_server.cpp

2.Uygulamayı çalıştırın: ./webserver

3.Web tarayıcınızı veya bir HTTP istemci aracını kullanarak http://localhost:8080 adresine erişin.

*/

#include <iostream>
#include <thread>
#include <string>
#include <cstring>
#include <netinet/in.h>
#include <unistd.h>

const int PORT = 8080;

void handleClient(int clientSocket) {
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    ssize_t bytesRead = read(clientSocket, buffer, sizeof(buffer) - 1);
    if (bytesRead <= 0) {
        close(clientSocket);
        return;
    }

    // Basit bir "Merhaba, Dünya!" yanıtı oluştur
    std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello, World!";
    write(clientSocket, response.c_str(), response.size());

    close(clientSocket);
}

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Sunucu soketi oluşturulamadı." << std::endl;
        return 1;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Bağlama hatası." << std::endl;
        return 1;
    }

    if (listen(serverSocket, 5) == -1) {
        std::cerr << "Dinleme hatası." << std::endl;
        return 1;
    }

    std::cout << "Sunucu " << PORT << " portunda çalışıyor..." << std::endl;

    while (true) {
        sockaddr_in clientAddress;
        socklen_t clientAddressLength = sizeof(clientAddress);
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);

        if (clientSocket == -1) {
            std::cerr << "İstemci kabul hatası." << std::endl;
            continue;
        }

        // Her istemciyi ayrı bir iş parçacığı ile işle
        std::thread clientThread(handleClient, clientSocket);
        clientThread.detach();
    }

    close(serverSocket);

    return 0;
}
