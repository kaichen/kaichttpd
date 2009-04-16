#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>

/* return current time */
char* get_time(void);
/* return file exist or not */
int not_exist(char *filename);
/* record the message with log leverl */
void logger(char * message, char const log_level);
/* record the message with log leverl */
void logger_info(char * message);
/* record the message with log leverl */
void logger_debug(char * message);
/* record the message with log leverl */
void logger_error(char * message);
/* raise the error and exist application */
void raise(char *error_message);
