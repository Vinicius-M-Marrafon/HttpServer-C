#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <windows.h>
#include <winsock2.h>


#define HTTP_PORT 3000
#define SERVER_IPv4 "192.168.1.10"

const char response_header[] = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: text/html; charset=UTF-8\r\n\r\n";

const char response[] = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: text/html; charset=UTF-8\r\n\r\n"
                        "<!DOCTYPE html>\r\n"
                        "<html>\r\n"
                        "<body>\r\n"
                        "<h1>Hello, Server</h1>\r\n"
                        "</body>\r\n"
                        "</html>\r\n";

SOCKET s;

void terminateSignalHandler(int signal)
{
    // ctrl + c pressed
    if (signal == SIGINT) {
        closesocket(s);
        WSACleanup();

        puts("[HTTP Server]: Closing service... Bye bye");
        exit(EXIT_SUCCESS);
    }
}

int main(void)
{
    WSADATA ws;
    // Initiates use of the Winsock DLL by a process. (DLL?)
    WSAStartup(0x0202, &ws);
    signal(SIGINT, terminateSignalHandler);

    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    SOCKADDR_IN httpServer = {0};
    
    httpServer.sin_family = AF_INET;
    httpServer.sin_port = htons(HTTP_PORT);
    httpServer.sin_addr.s_addr = inet_addr(SERVER_IPv4);

    // bind connection
    if (bind(s, (struct sockaddr *)& httpServer, sizeof httpServer) != SOCKET_ERROR) {
        listen(s, 1);

        printf("[HTTP Server]: Running on: http://%s:%d\n", SERVER_IPv4, HTTP_PORT);

        while (true) {
            // Wait for connection
            SOCKET client = accept(s, 0, 0);
            char request[1024] = {0};

            recv(client, request, sizeof request, 0);
            
            if ((int)client > 0)
                printf("Client's %d request %s\r\n", client, request);

            // Handle new User (THREADS)
            // (1) Declare the thread addr (As void *)
            // (2) Create the thread (CreateThread)

            // Send the response
            send(client, response, sizeof response, 0);
            // write(client, response, sizeof response);

            closesocket(client);
        }
    }
    else {
        // Show bad stuffs for the user
    }
}