/*
 *  Filename:  main.c
 *  Description:  kaichttpd server main program
 *  Author:  Kai Chen (chenk85@gmail.com)
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

#include "utils.h"
#include "request.h"
#include "response.h"

#define BUFFER_SIZE 1024
#define SMALL_BUFFER_SIZE 128
#define LARGE_BUFFER_SIZE 1024 * 1024
#define DEFAULT_PORT 5000

int generate_mock_response(char *buf);
void log_request(Request *req);
void dispatcher(Request *req, char *result);

int
main(int argc, char const* argv[])
{
    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_in server_address, client_address;

    unlink("server_socket");
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(server_sockfd < 0) {
        raise("Can't create socket!!!");
        return -1;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(DEFAULT_PORT);
    server_len = sizeof(server_address);

    logger_info("Server Ready to Start");
    if(bind(server_sockfd, (struct sockaddr *)&server_address, server_len) < 0) {
        close(server_sockfd);
        raise("Can't bind socket!!!");
        return -1;
    }
    listen(server_sockfd, 5);
    logger_info("Server started");

    while(1) {
        char request_content[BUFFER_SIZE];
        char response_content[BUFFER_SIZE];
        Request req;

        logger_info("Server waiting request...");

        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);

        read(client_sockfd, request_content, BUFFER_SIZE);
        char verb[64], path[64];
        parse_request(request_content, verb, path);
        req.http_verb = verb;
        req.path = path;
        log_request(&req);
        dispatcher(&req, response_content);
        write(client_sockfd, response_content, strlen(response_content));
        close(client_sockfd);
        logger_info("Process the request successfully\n");
    }
    return 0;
}

void
dispatcher(Request *req, char *result)
{
    if ( strcmp(req->http_verb,"GET") != 0 ) {
        logger_info("Do not implement this operation yet\n");
        do_501(result);
    } else if (not_exist(req->path)) {
        printf("Can't find request path %s\n", req->path);
        do_404(req->path, result);
    } else {
        printf("Find request path %s\n", req->path);
        do_cat_file(req->path, result);
    }
}

void log_request(Request *req)
{
    logger_info(req->http_verb);
    logger_info(req->path);
    logger_info(get_time());
}

