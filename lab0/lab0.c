//
//  main.c
//  cs111
//
//  Created by Jeremy Louie on 6/14/20.
//  Copyright © 2020 Jeremy Louie. All rights reserved.
//

/*
Name:
UID:  
Date: 6/14/20
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <getopt.h>
#include <signal.h>

static struct option long_opt[] = {
    {"input", required_argument, NULL, 'i'},
    {"output", required_argument, NULL, 'o'},
    {"segfault", no_argument, NULL, 's'},
    {"catch", no_argument, NULL, 'c'},
    {0, 0, 0, 0}
};

void handle_segmentation_fault(int signal) {
    if (signal == SIGSEGV) {
        fprintf(stderr, "\tSegmentation fault caught\n");
        exit(4);
    }
}

int main(int argc, const char* argv[]) {
    int opt;
    int opt_index;
    opt_index = 0;

    int i_flag, o_flag, s_flag, c_flag;
    i_flag = 0;
    o_flag = 0;
    s_flag = 0;
    c_flag = 0;

    char* i_file, o_file;

    // getting options
    while ((opt = getopt_long (argc, argv, "i:o:sc", long_opt, &opt_index)) != -1) {
        switch (opt) {
            case 'i':   // input
                i_flag = 1;     // setting input flag to true
                i_file = optarg;
                break;
            case 'o':   // output
                o_flag = 1;     // setting output flag to true
                o_file = optarg;
                break;
            case 's':   // segmentation fault
                s_flag = 1;     // setting segmentation fault to true
                break;
            case 'c':   // catch
                c_flag = 1;     // setting catch flag to true
                break;
            default:    // default, print error
                fprintf(stderr, "\tlab0: illegal option -- %s", opt);
                printf("\tSyntax: lab0 [--input filename] [--output filename] [--segfault] [--catch]")
                exit(1);
        }
    }

    // if input flag is true
    if (i_flag == 1) {
        int input_file_descriptor = open(i_file, O_RDONLY);
        if (input_file_descriptor < 0) {
            fprintf(stderr, "\tError: cannot open --input file %s %s\n", i_file, strerror(errno));
            exit(2);
        } else {
            close(STDIN_FILENO);
            dup(input_file_descriptor);
            close(input_file_descriptor);
        }
    }

    // if output flag is true
    if (o_flag == 1) {
        int output_file_descriptor = creat(output_filename, 0666);
        if (output_file_descriptor < 0) {
            fprintf(stderr, "\tError: cannot create --ouput file %s %s\n", o_file, strerror(errno));
            exit(3);
        } else {
            close(STDIN_FILENO);
            dup(output_file_descriptor);
            close(output_file_descriptor);
        }
    }

    // if segmentation fault flag is true
    if (s_flag == 1) {
        char* a_char = NULL;
        a_char[0] = ' '; // subroutine that forces segmentation fault
    }

    // if catch flag is true
    if (c_flag == 1) {
        signal(SIGSEGV, handle_segmentation_fault);
    }

    // reading from stdin and writing to stdout
    const int BUFF_SIZE = 32;
    char* buffer = (char*) malloc(BUFF_SIZE);
    int nread, nwrite;
    nread = read(STDIN_FILENO, buffer, BUFF_SIZE);

    while (nread > 0) {
        nwrite = write(STDOUT_FILENO, buffer, nread);
        if (nwrite < 0) {
            fprintf(stderr, "\tError: cannot write to output file %s\n", strerror(errno));
            exit(3);
        }
        nread = read(STDIN_FILENO, buffer, BUFF_SIZE);
    }

    if (nread < 0) {
        fprintf(stderr, "\tError: cannot read from input file %s\n", strerror(errno));
        exit(2);
    }

    free(buffer);
    exit(0);
}
