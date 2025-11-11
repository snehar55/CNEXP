#include <stdio.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    SOCKET s, c;
    struct sockaddr_in server, client;
    char msg[100];
    int len, bytes;

    WSAStartup(MAKEWORD(2, 2), &wsa);

    s = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(s, (struct sockaddr*)&server, sizeof(server));
    listen(s, 1);

    printf("Server started... waiting for client\n");
    len = sizeof(client);
    c = accept(s, (struct sockaddr*)&client, &len);

    // Clear buffer before use
    memset(msg, 0, sizeof(msg));

    // Receive message
    bytes = recv(c, msg, sizeof(msg) - 1, 0); // leave room for '\0'
    msg[bytes] = '\0'; // ✅ Null-terminate manually

    printf("Client says: %s\n", msg);

    // Send the same message back
    send(c, msg, strlen(msg), 0);
    printf("Echoed back to client.\n");

    closesocket(c);
    closesocket(s);
    WSACleanup();
}
