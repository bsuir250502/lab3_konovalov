#include "stdlib.h"
#include "optlib.h"             /* getopt_c */
#include "service.h"
#define SERVICE 1

int options(int argc, char **argv)
{
    const int hyphen_count = 1;
    int no_arguments_needed = 1, i = 0;
    char *arg = NULL;
    for (i = 1; i < argc; i++) {
        arg = *(argv + i);
        switch (getopt_c(arg, hyphen_count)) {
        case 0:
            if (no_arguments_needed) {
                printf("Unknown command %s.\n", arg);
                return 0;
            }
            if (!freopen(arg, "r", stdin)) {
                printf("File does not exist or is inaccessible\n");
                return 0;
            }
            no_arguments_needed = 1;
            break;
        case 1:
            if (no_arguments_needed == 0)
                return 0;
            switch (*arg) {
            case 'h':
                no_arguments_needed = 1;
                display_usage();
                return 0;
                break;
            case 'f':
                no_arguments_needed = 0;
                break;
            default:
                printf("Unknown command -%s.\n", arg);
                return 0;
                break;
            }
            break;
        default:
            printf("Unknown command %s.\n", arg);
            return 0;
            break;
        }
    }
    return 1;
}

void display_usage(void)
{
    int i = 0;
    char *help[] = { "-h", "-f <path>" };
    char *help_def[] = { "Displays usage information",
        "Redirect input to file"
    };
    printf("Usage: lab3 [options]\n");
    for (i = 0; i < 2; i++)
        printf("%-12s %s\n", help[i], help_def[i]);
    return;
}
