#ifndef HTTP_H
#define HTTP_H

#include <winsock2.h>

typedef enum HttpMethod {
    HTTP_GET,
    HTTP_POST,
    HTTP_HEAD,
    HTTP_PUT,
    HTTP_DELETE,
    HTTP_OPTIONS,
    HTTP_CONNECT,
    HTTP_TRACE,
    HTTP_PATCH
} HttpMethod;

typedef struct HttpPackage {
    char *header, *body;
}
HttpPackage;

// Just method and path right now
typedef struct Request {
    HttpMethod method;
    char *path;
    // Parameters
}
Request;

HttpPackage *newHttpPackage(char *header, char *body);
void deleteHttpPackage(HttpPackage *hp);
void displayHttpPackage(HttpPackage *hp);
Request *httpPackToRequest(HttpPackage *hp);

Request *newRequest(HttpMethod hm, char *path);
Request *parseRequest(char *request);
void deleteRequest(Request *r);

void sendFile(SOCKET s, char *path);

#endif//HTTP_H