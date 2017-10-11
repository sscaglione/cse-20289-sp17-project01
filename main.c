/* driver.c */

#include "search.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <unistd.h>

/* Functions */

void	    usage(const char *program_name, int status) {
    fprintf(stderr, "Usage: %s PATH [OPTIONS] [EXPRESSION]\n", program_name);
    fprintf(stderr, "\nOptions:\n");
    fprintf(stderr, "    -executable     File is executable or directory is searchable to user\n");
    fprintf(stderr, "    -readable       File readable to user\n");
    fprintf(stderr, "    -writable       File is writable to user\n\n");
    fprintf(stderr, "    -type [f|d]     File is of type f for regular file or d for directory\n\n");
    fprintf(stderr, "    -empty          File or directory is empty\n\n");
    fprintf(stderr, "    -empty          File or directory is empty\n\n");
    fprintf(stderr, "    -name  pattern  Base of file name matches shell pattern\n");
    fprintf(stderr, "    -path  pattern  Path of file matches shell pattern\n\n");
    fprintf(stderr, "    -perm  mode     File's permission bits are exactly mode (octal)\n");
    fprintf(stderr, "    -newer file     File was modified more recently than file\n\n");
    fprintf(stderr, "    -uid   n        File's numeric user ID is n\n");
    fprintf(stderr, "    -gid   n        File's numeric group ID is n\n");
    fprintf(stderr, "\nExpressions:\n\n");
    fprintf(stderr, "    -print          Display file path (default)\n");
    fprintf(stderr, "    -exec cmd {} ;  Execute command on path\n");
    exit(status);
}

/* Main Execution */

int	    main(int argc, char *argv[]) {
	Settings settings ={
		.access	= 0,
		.empty = 0,
		.uid	= -1,
		.gid	= -1,
		.exec_argc = 0;
	};
	int arg = 0;
	argv[arg] = rootDirectory;
	arg = arg + 1;
	while (arg < argc){
		if (streq(argv[arg], "-executable")) {
			settings.access |= X_OK;
		}
		else if (streq(argv[arg], "-readable")) {
			settings.access |= R_OK;
		}
		else if (streq(argv[arg], "-writable")) {
			settings.access |= W_OK;
		}
		else if (streq(argv[arg], "-type")) {
			arg = arg + 1;
			if (streq(argv[arg], "f"){
				settings.type = (int)'f';
			}
			else if (streq(argv[arg], "d"){
				settings.type = (int)'d';
			}
		}
		else if (streq(argv[arg], "-empty")) {
				settings.type = 1;
		}
		else if (streq(argv[arg], "-name")) {
			arg = arg + 1;
			pattern = argv[arg];
			// base of file name matches shell pattern
		}
		else if (streq(argv[arg], "-path")) {
			arg = arg + 1;
			pattern = argv[arg];
			// path of file matches shell pattern
		}
		else if (streq(argv[arg], "-perm")) {
			arg = arg + 1;
			// file's permission bits are exactly mode (octal)
			settings.access = argv[arg]; //NOTE: I don't know if this is right
		}
		else if (streq(argv[arg], "-newer")) {
			arg = arg + 1;
			settings.newer = get_mtime(argv[arg]); //NOTE: I also don't know if this is right
			// can we use get_mtime? so confused
			// file was modified more recently than file
		}
		else if (streq(argv[arg], "-uid")) {
			arg = arg + 1;
			settings.uid = argv[arg];
		}
		else if (streq(argv[arg], "-gid")) {
			arg = arg + 1;
			settings.gid = argv[arg];
		}
		else if (streq(argv[arg], "-print")) {
			settings.print = 1;
		}
		else if (streq(argv[arg], "-exec")) {
			arg = arg + 1;
			settings.exec_argc = settings.exec_argc + 1;
			settings.argv[settings.argc-1] = argv[arg]; // this could be wrong too
			// execute argv[arg] command
		}
    	arg = arg + 1;
	}
	search(rootDirectory, settings);
    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
