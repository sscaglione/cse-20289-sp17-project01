/* utilities.c */

#include "search.h"

#include <errno.h>
#include <string.h>
#include <time.h>

#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * Test whether or not a directory is empty.
 * @param   path        Path to directory.
 * @return  Whether or not a directory is empty.
 */
bool        is_directory_empty(const char *path) {
   struct dirent* d;
   DIR* ourdir = opendir(path);
   if (ourdir == NULL){
        perror(path);
   	return errno;
   }
   int i = 0; // iterator to count entries since "." and ".." will always be entries
   while ((d = readdir(ourdir)) != NULL){
   	i++;
   }
   closedir(ourdir);
   return (i > 2) ? false : true;
}

/**
 * Retrieve the modification time of the given file.
 * @param   path        Path to file of directory.
 * @return  The modification time of the given file.
 */
time_t      get_mtime(const char *path) {
    struct stat attribute;
    if (lstat(path, &attribute) != -1) {
    	return attribute.st_mtime;
    }
    else {
    	perror(path); // if it doesn't work, print the error so we know what happened
    	return errno; // I guess we should exit with an error too
    }
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
