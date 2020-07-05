
// 1a: implement options --rdonly, --wronly, --command, and --verbose

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int main(int argc, const char* argv[]) {
    int c;
    int rdonly_flag, wronly_flag, command_flag, verbose_flag;
    rdonly_flag = 0;
    wronly_flag = 0;
    command_flag = 0;
    verbose_flag = 0;

    while (1) {
        int option_index = 0;
        static struct option long_options[] = {
            {"rdonly", no_argument, NULL, 'r'},
            {"wronly", no_argument, NULL, 'w'},
            {"command", required_argument, NULL, 'c'},
            {"verbose", no_argument, NULL, 'v'},
            {0, 0, 0, 0,}
        };

        c = getopt_long(argc, argv, "r:w:c:v", long_options, &option_index);

        if (c == -1) {
            break;
        }

        switch (c) {
            case 'r':
                rdonly_flag = 1;
                // 
                break;
            case 'w':
                wronly_flag = 1;
                break;
            case 'c':
                command_flag = 1;

                break;
            case 'v':
                verbose_flag = 1;
                break;
            case '?':
                // getopt_long already printed an error message
                break;
            default:
                abort();
        }
    }

    // if rdonly flag is set
    if (rdonly_flag) {
        printf("rdonly\n");
    }

    // if wronly flag is set
    if (wronly_flag) {
        printf("wronly\n");
    }

    // if command flag is set
    if (command_flag) {
        printf("command\n");
    }

    // if verbose flag is set
    if (verbose_flag) {
        printf("verbose\n");
    }

    // print any remaining line arguments that are not options
    if (optind < argc) {
        printf ("non-option ARGV-elements: ");
        while (optind < argc)
        printf ("%s ", argv[optind++]);
        putchar ('\n');
    }
    exit(0);
}