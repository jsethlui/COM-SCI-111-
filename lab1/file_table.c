
#include "file_table.h"

//typedef struct {
//	int* file_descriptor_array;
//	int file_cap;
//	int file_index;
//} File_t;

//File_t* files_table_constructor();
//void add_file_descriptor(File_t** f, int fd);
//void close_file_table(File_t* f);
//void redirect_io(File_t* file, int old_fd, int new_fd);
//int check_file_descriptor_args(File_t* f, const char* command, const char* argv);

// Constructor, initializes file descriptor table
File_t* files_table_constructor() {
	File_t* file = malloc(sizeof(File_t));
	if (file == NULL) {
		perror("\tError: cannot allocate memory to file table\n");
		exit(1);
	}
	file->file_index = 0;
	file->file_cap = 19;
	file->file_descriptor_array = malloc(sizeof(int) * file->file_cap);
	if (file->file_descriptor_array == NULL) {
		perror("\tError: cannot allocate memory to file table\n");
		exit(1);
	}
	return file;
}

// adding file descriptor to file table
void add_file_descriptor(File_t** f, int fd) {
	File_t* file = NULL;	// maybe initialize?
	
	// checking if file table exists
//	int LHS = (f == NULL);
//	int RHS = ((file = *f) == NULL);
	if (f == NULL) {	//if file table parameter does not exist
		perror("\tError: file table does not exist\n");
		exit(1);
	}
	
	// adding file descriptor
	if (file->file_index == file->file_cap) {	// if file index is same as file cap
		File_t* new_file = realloc(file, 2 * file->file_cap);
		if (new_file == NULL) {
			perror("\tError: cannot increase file table\n");
			exit(1);
		}
		new_file->file_cap *= 2;
		file = new_file;
		*f = file;
	}
	file->file_descriptor_array[file->file_index++] = fd;
}

// closing file table
void close_file_table(File_t* file) {
	// searching through array for valid file descriptor values
	for (int i = 0; i < file->file_index; i++) {
		if (file->file_descriptor_array[i] == -1) {	// if value at i is -1, do nothing (since valid value)
			continue;
		} else if (file->file_descriptor_array[i] < 0) {	// if value at i is negative
			perror("\tError: file descriptor cannot negative \
							 cannot close table");
			exit(1);
		} else {	// else, set value at i to -1
			file->file_descriptor_array[i] = -1;
		}
	}
}

// redirecting IO
void redirect_io(File_t* file, int old_fd, int new_fd) {

}

// checking if fd args are valid
int check_file_descriptor_args(File_t* f, const char* command, const char* argv) {
	// checking if file parameter exists
	if (f == NULL) {
		perror("\tError: cannot allocate memory to file table\n");
		exit(1);
	}
	
	// checking if command is valid
	int file_descriptor = atoid(argv);	// converting char* to int
	if ( ! strcmp(argv, "0") && file_descriptor != 0) {
		fprintf(stderr, "\tError: %s should be followed by three correct file descriptor values\n", command);
		exit(1);
	}
	
	// checking if fd is valid
	if ((file_descriptor < 0) || (file_descriptor >= f->file_cap)) {
		fprintf(stderr, "\tError: %s contains incorrect file descriptor", command);
		exit(1);
	}
	return file_descriptor;
}
