
// contains all data

#ifndef COMMAND_H
#define COMMAND_H

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h> // for O_APPEND, O_CLOEXEC, etc

static struct option long_options[] = {
	// file flags
	{"append",      no_argument,       NULL, O_APPEND},
	{"cloexec",     no_argument,       NULL, O_CLOEXEC},
	{"creat",       no_argument,       NULL, O_CREAT},
	{"directory",   no_argument,       NULL, O_DIRECTORY},
	{"dsync",       no_argument,       NULL, O_DSYNC},
	{"excl",        no_argument,       NULL, O_EXCL},
	{"nofollow",    no_argument,       NULL, O_NOFOLLOW},
	{"nonblock",    no_argument,       NULL, O_NONBLOCK},
	// {"rsync",       no_argument,       NULL, O_RSYNC},	// on SEASNET, is O_SYNC
	{"sync",        no_argument,       NULL, O_SYNC},
	{"trunc",       no_argument,       NULL, O_TRUNC},

	// file-opening options
	{"rdonly",      required_argument, NULL, O_RDONLY},
	{"rdwr",        required_argument, NULL, O_RDWR},
	{"wronly",      required_argument, NULL, O_WRONLY},
	{"pipe",        no_argument,       NULL, '0'},

	// subcommands
	{"command",     required_argument, NULL, '1'},
	{"wait",        no_argument,       NULL, '2'},

	// misc options
	// {"chdir",       required_argument, NULL, O_CHDIR},
	{"close",       required_argument, NULL, '3'},
	{"verbose",     no_argument,       NULL, '4'},
	{"profile",     required_argument, NULL, '5'},
	// {"abort",       no_argument,       NULL, ABORT},
	// {"catch",       required_argument, NULL, CATCH},
	// {"ignore",      required_argument, NULL, IGNORE},
	// {"default",     required_argument, NULL, DEFAULT},
	// {"pause",       no_argument,       NULL, PAUSE},
	{NULL,          0,                 NULL, 0}
};

// file flags
int const APPEND = O_APPEND;
int const CLOEXEC = O_CLOEXEC;
int const CREAT = O_CREAT;
int const DIRECTORY = O_DIRECTORY;
int const DSYNC = O_DSYNC;
int const EXCL = O_EXCL;
int const NOFOLLOW = O_NOFOLLOW;
int const NONBLOCK = O_NONBLOCK;
int const SYNC = O_SYNC;
int const TRUNC = O_TRUNC;

// file opening options
int const RDONLY = O_RDONLY;
int const RDWR = O_RDWR;
int const WRONLY = O_WRONLY;
char const PIPE = '0';

// subcommands
char const COMMAND = '1';
char const WAIT = '2';

// misc options
char const CLOSE = '3';
char const VERBOSE = '4';
char const PROFILE = '5';



#endif
