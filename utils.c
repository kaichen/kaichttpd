#include "utils.h"

char*
get_time(void)
{
    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime ( &rawtime );
    return asctime(timeinfo);
}

int
not_exist(char *filename)
{
    struct stat info;
    return(stat(filename, &info) == -1);
}

void
logger(char *buf, char const log_level) {
    switch (log_level) {
        case 'I':
            logger_info(buf);
            break;
        case 'D':
            logger_debug(buf);
            break;
        case 'E':
            logger_error(buf);
        default:
            raise("Error log_level");
            break;
    }
}

void
logger_info(char *msg) {
    printf("INFO - %s\n", msg);
}

void
logger_debug(char *msg){
    printf("DEBUG - %s\n", msg);
}

void
logger_error(char *msg) {
    printf("ERROR - %s\n", msg);
}

void
raise(char *error_msg)
{
    printf("Raise Error:\n\t%s\n", error_msg);
}
