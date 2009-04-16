#include "response.h"

void
do_501(char *buf)
{
    strcpy(buf, "HTTP/1.0 501 Not Implemented\r\n");
    strcat(buf, "Content-type: text/plain\r\n");
    strcat(buf, "\r\n");
    strcat(buf, "That command is not yet implemented\r\n");
}

void
do_404(char *item, char *buf)
{
    strcpy(buf, "HTTP/1.0 404 Not Found\r\n");
    strcat(buf, "Content-type: text/plain\r\n");
    strcat(buf, "\r\n");
    strcat(buf, "The item you requested: ");
    strcat(buf, "\r\n");
    strcat(buf, item);
    strcat(buf, " is not found\r\n");
}

void
do_cat_file(char *filename, char *buf)
{
    char *extension = file_type(filename);
    char *content = "text/plain";
    FILE *fp;
    int	c;

    if ( strcmp(extension,"html") == 0 )
        content = "text/html";
    else if ( strcmp(extension, "gif") == 0 )
        content = "image/gif";
    else if ( strcmp(extension, "jpg") == 0 )
        content = "image/jpeg";
    else if ( strcmp(extension, "jpeg") == 0 )
        content = "image/jpeg";
    else if ( strcmp(extension, "png") == 0 )
        content = "image/png";

    fp = fopen(filename, "r");

    if (fp != NULL) {
        header(buf, content);
        strcat(buf, "\r\n");
        int i = 0;
        printf("start read file by char to buf...\n");
        while ( (c = getc(fp) ) != EOF ) {
            printf("read file by char '%c' to buf...\n", c);
            buf[i++] = c;
        }
        buf[i-1] = "\0";
        fclose(fp);
    }
}

char*
file_type(char *filename)
{
    char *cp;
    if ( (cp = strrchr(filename, '.' )) != NULL )
        return cp+1;
    return "";
}

void
header(char *buf, char *content_type)
{
    strcpy(buf, "HTTP/1.0 200 OK\r\n");
    if ( content_type ) {
        strcat(buf, "Content-type: \r\n");
        strcat(buf, content_type );
        strcat(buf, "\r\n");
    }
}

