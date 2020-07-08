
#ifndef FILE_TABLE_H
#define FILE_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
	int* file_descriptor_array;
	int file_cap;
	int file_index;
} File_t;

File_t* files_table_constructor(void);	// void is to silence warnings
void add_file_descriptor(File_t** f, int fd);
void close_file_table(File_t* f);
void redirect_io(File_t* file, int old_fd, int new_fd);
int check_file_descriptor_args(File_t* f, const char* command, const char* argv);

#endif
