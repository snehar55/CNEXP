#include <stdio.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
    char msg[100], reply[100];
    int bytes;

    WSAStartup(MAKEWORD(2, 2), &wsa);

    s = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(s, (struct sockaddr*)&server, sizeof(server));

    printf("Enter message: ");
    fgets(msg, sizeof(msg), stdin);
    msg[strcspn(msg, "\n")] = '\0'; // remove newline

    send(s, msg, strlen(msg), 0);

    memset(reply, 0, sizeof(reply));
    bytes = recv(s, reply, sizeof(reply) - 1, 0);
    reply[bytes] = '\0'; // ✅ ensure clean output

    printf("Server echoed: %s\n", reply);

    closesocket(s);
    WSACleanup();
}
