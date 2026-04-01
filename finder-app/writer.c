#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Open connection to syslog
    openlog("writer", LOG_PID | LOG_CONS, LOG_USER);

    // Validate arguments
    if (argc != 3)
    {
        syslog(LOG_ERR, "Invalid number of arguments. Expected 2, got %d", argc - 1);
        fprintf(stderr, "Usage: %s <writefile> <writestr>\n", argv[0]);
        closelog();
        exit(1);
    }

    const char *writefile = argv[1];
    const char *writestr = argv[2];

    // Open file for writing
    FILE *fp = fopen(writefile, "w");
    if (fp == NULL)
    {
        syslog(LOG_ERR, "Failed to open file: %s", writefile);
        perror("fopen");
        closelog();
        exit(1);
    }

    // Write string to file
    if (fprintf(fp, "%s", writestr) < 0)
    {
        syslog(LOG_ERR, "Failed to write to file: %s", writefile);
        perror("fprintf");
        fclose(fp);
        closelog();
        exit(1);
    }

    syslog(LOG_DEBUG, "Writing \"%s\" to %s", writestr, writefile);

    fclose(fp);
    closelog();

    return 0;
}

