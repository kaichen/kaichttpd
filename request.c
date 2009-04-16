#include "request.h"

void
parse_request(char *request_content, char *verb, char *path)
{
    char buf[64];
    char meta1[64];
    char meta2[64];
    printf("Parse request line 9...\n");
    strcpy(buf, strtok(request_content, "\r\n"));
    printf("Parse request line 11...\n");
    strcpy(meta2, ".");
    printf("Parse request line 13...\n");
    sscanf(buf, "%s %s", meta1, meta2 + 1);
    printf("Parse request line 15...\n");
    strcpy(verb, meta1);
    printf("Parse request line 17...\n");
    strcpy(path, meta2);
}
