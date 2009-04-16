#include <string.h>
#include <stdio.h>

char* file_type(char *f);
void header(char *buf, char *content_type);
void do_501(char *buf);
void do_404(char *item, char *buf);
void do_cat_file(char *filename, char *buf);
