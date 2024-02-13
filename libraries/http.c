#include "http.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char HTTP_200[59] = "HTTP/1.1 200 OK\r\n"
                    "Content-Type: text/html; charset=UTF-8\r\n\r\n";

const char HTTP_404[59] = "HTTP/1.1 404 OK\r\n"
                    "Content-Type: text/html; charset=UTF-8\r\n\r\n";


HttpPackage *newHttpPackage(char *header, char *body)
{
    size_t headerSize = 0;
    size_t bodySize = 0;

    if (header != NULL)
        headerSize = strlen(header);
    
    if (body != NULL)
        bodySize = strlen(body);

    HttpPackage *httpPackage = malloc(sizeof(HttpPackage));

    if (httpPackage == NULL) {
        fprintf(stderr, "[HTTPPackage - new]: Allocation failure\n");
        return NULL;
    }

    if (header != NULL) httpPackage->header = calloc((headerSize + 1), sizeof(char));
    else httpPackage->header = NULL;

    if (body != NULL) httpPackage->body = calloc((bodySize + 1), sizeof(char));
    else httpPackage->body = NULL;

    if (header != NULL) memcpy(httpPackage->header, header, headerSize);
    if (body != NULL) memcpy(httpPackage->body, body, bodySize);

    return httpPackage;
}

Request *httpPackToRequest(HttpPackage *hp)
{
    if (hp != NULL) {
        if (hp->header != NULL) {
            size_t headerSize = strlen(hp->header);
            char h[headerSize];
            memcpy(h, hp->header, headerSize);

            HttpMethod httpMethod;
            char *path;

            int splitCount = 0;
            for (char *p = strtok(h," "); p != NULL && splitCount < 2; p = strtok(NULL, " "), splitCount++) {
                if (splitCount == 0) {
                    if (strcmp(p, "GET") == 0) {
                        httpMethod = HTTP_GET;
                    }
                    else if (strcmp(p, "POST") == 0) {
                        httpMethod = HTTP_POST;
                    }
                    else if (strcmp(p, "PUT") == 0) {
                        httpMethod = HTTP_PUT;
                    }
                    else if (strcmp(p, "DELETE") == 0) {
                        httpMethod = HTTP_DELETE;
                    }
                    else if (strcmp(p, "PATCH") == 0) {
                        httpMethod = HTTP_PATCH;
                    }
                    else if (strcmp(p, "TRACE") == 0) {
                        httpMethod = HTTP_TRACE;
                    }
                    else if (strcmp(p, "OPTIONS") == 0) {
                        httpMethod = HTTP_OPTIONS;
                    }
                    else if (strcmp(p, "CONNECT") == 0) {
                        httpMethod = HTTP_CONNECT;
                    }
                    else if (strcmp(p, "HEAD") == 0) {
                        httpMethod = HTTP_HEAD;
                    }
                    else {
                        fprintf(stderr, "[REQ PARSER]: Invalid request method!\n");
                        return NULL;
                    }
                }
                else {
                    path = p;
                }
            }

            return newRequest(httpMethod, path);
        }

        return NULL;
    }
    return NULL;
}

void deleteHttpPackage(HttpPackage *hp)
{
    if (hp != NULL) {
        free(hp->body);
        free(hp->header);
        free(hp);
    }
}

void displayHttpPackage(HttpPackage *hp)
{
    if (hp != NULL) {
        if (hp->header != NULL) {
            printf("%s", hp->header);
        }
        if (hp->body != NULL) {
            printf("%s", hp->body);
        }
    }
}

Request *newRequest(HttpMethod hm, char *path)
{
    Request *req = malloc(sizeof(Request));
    if (req == NULL) {
        return NULL;
    }

    req->method = hm;

    if (path != NULL) {
        size_t pathSize = strlen(path);
        req->path = calloc((pathSize + 1), sizeof(char));

        memcpy(req->path, path, pathSize);
    }
    else {
        req->path = NULL;
    }

    return req;
}

Request *parseRequest(char *request)
{
    if (request != NULL) {
        size_t reqSize = strlen(request);
        char reqBuff[reqSize + 1];

        memcpy(reqBuff, request, reqSize);

        HttpMethod httpMethod;
        char *path;

        int splitCount = 0;
        for (char *p = strtok(reqBuff," "); p != NULL && splitCount < 2; p = strtok(NULL, " "), splitCount++) {
            if (splitCount == 0) {
                if (strcmp(p, "GET") == 0) {
                    httpMethod = HTTP_GET;
                }
                else if (strcmp(p, "POST") == 0) {
                    httpMethod = HTTP_POST;
                }
                else if (strcmp(p, "PUT") == 0) {
                    httpMethod = HTTP_PUT;
                }
                else if (strcmp(p, "DELETE") == 0) {
                    httpMethod = HTTP_DELETE;
                }
                else if (strcmp(p, "PATCH") == 0) {
                    httpMethod = HTTP_PATCH;
                }
                else if (strcmp(p, "TRACE") == 0) {
                    httpMethod = HTTP_TRACE;
                }
                else if (strcmp(p, "OPTIONS") == 0) {
                    httpMethod = HTTP_OPTIONS;
                }
                else if (strcmp(p, "CONNECT") == 0) {
                    httpMethod = HTTP_CONNECT;
                }
                else if (strcmp(p, "HEAD") == 0) {
                    httpMethod = HTTP_HEAD;
                }
                else {
                    fprintf(stderr, "[REQ PARSER]: Invalid request method!\n");
                    return NULL;
                }
            }
            else {
                path = p;
            }
        }

        return newRequest(httpMethod, path);
    }


    return NULL;
}

void deleteRequest(Request *r)
{
    if (r != NULL) {
        if (r->path != NULL) {
            free(r->path);
        }
        free(r);
    }
}

void sendFile(SOCKET s, char *path)
{
    if (path != NULL && (int)s > 0) {
        FILE *html = fopen(path, "rb");
        if (html == NULL) 
            fprintf(stderr, "[HTTP SERVER]: HTML file not found\n");
            
        else {
            fseek(html, 0L, SEEK_END);

            // Get the position
            size_t sizeHTML = ftell(html);
            rewind(html);

            // size_t sizeHeader = strlen(HTTP_200);

            char htmlContent[sizeHTML];
            // char socketBuffer[sizeHeader + sizeHTML + 2];

            fread(htmlContent, sizeHTML, 1, html);

            send(s, HTTP_200, sizeof HTTP_200, 0);
            send(s, htmlContent, sizeof htmlContent, 0);
        }
    }
}