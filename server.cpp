#include <iostream>
#include <winsock2.h>
#include <fstream>
#include <string>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080);

    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 5);

    cout << "SERVER IS ON. Waiting for clients..." << endl;
    cout << "Server will NOT close even if client disconnects." << endl;

    // This file will keep appending, not overwrite
    ofstream file("data.txt", ios::app);

    // --- MAIN CHANGE: Server Loop ---
    while (true) {
        cout << "\nWaiting for new client..." << endl;
        SOCKET clientSocket = accept(serverSocket, NULL, NULL);
        cout << "Client Connected!" << endl;

        char buffer[1024];
        while (true) {
            int bytes = recv(clientSocket, buffer, sizeof(buffer)-1, 0);
            
            // CLIENT DISCONNECTED
            if (bytes <= 0) {
                cout << "Client Disconnected! But Server is STILL ON." << endl;
                break; // Break inner loop, go back to accept()
            }

            buffer[bytes] = '\0';
            file << buffer;
            file.flush(); // Save immediately
            cout << buffer;
        }

        closesocket(clientSocket); // Close only CLIENT socket
        cout << "Ready for next client..." << endl;
        // Server Socket is NOT closed here, so loop continues
    }

    // This will never run unless you force close server
    closesocket(serverSocket);
    WSACleanup();
    return 0;
}
