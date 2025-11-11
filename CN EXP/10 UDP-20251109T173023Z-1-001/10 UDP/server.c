#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA w;
    SOCKET s;
    struct sockaddr_in server, client;
    int len = sizeof(client);
    char msg[100];
    int bytes;

    WSAStartup(MAKEWORD(2,2), &w);
    s = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(s, (struct sockaddr*)&server, sizeof(server));

    printf("Server started... waiting for message\n");

    memset(msg, 0, sizeof(msg));
    bytes = recvfrom(s, msg, sizeof(msg) - 1, 0, (struct sockaddr*)&client, &len);
    msg[bytes] = '\0';  // ✅ Null-terminate properly

    printf("Client says: %s\n", msg);

    sendto(s, msg, strlen(msg), 0, (struct sockaddr*)&client, len);
    printf("Echoed back: %s\n", msg);

    closesocket(s);
    WSACleanup();
}
