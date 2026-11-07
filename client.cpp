#include <iostream>
#include <winsock2.h>
#include <cstdio>
#include <string>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    
    // --- CHANGE THIS IP TO YOUR SERVER LAPTOP'S IP ---
    string serverIP;
    cout << "Enter Server Laptop IP: ";
    cin >> serverIP;
    serverAddr.sin_addr.s_addr = inet_addr(serverIP.c_str());

    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        cout << "Failed to connect! Check IP and Firewall." << endl;
        return 1;
    }

    cout << "Connected to Server!" << endl;

    for (int i = 1; i <= 100; i++) {
        double t = 7.21 + (i-1) * 0.01; // 7.21s to 8.20s
        int temp = 20 + rand() % 15; // 20C to 34C
        
        char buffer[100];
        sprintf(buffer, "Record %d time=%.2fs temp=%dC\n", i, t, temp);
        
        send(clientSocket, buffer, strlen(buffer), 0);
        cout << "Sent: " << buffer;
    }

    // At the end of client.cpp
cout << "\nAll 100 records sent! Disconnecting..." << endl;
closesocket(clientSocket); // <-- This disconnects client
WSACleanup();
return 0; // Client program ends
}
