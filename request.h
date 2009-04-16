#include <string.h>
#include <stdio.h>

typedef struct {
    char* header;
    char* http_verb;
    char* path;
    //char* host;
} Request;

void parse_request(char *request_content, char *verb, char *path);

