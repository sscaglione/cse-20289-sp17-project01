/* search.c */

#include "search.h"
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <dirent.h>

/**
 * Recursively search through the provided root directory
 * @param   root        Path to directory
 * @param   settings    Settings structure
 * @return  Whether or not the search was successful.
 */
int	    search(const char *root, const Settings *settings) {
    char* path = root; //we need to append all possible subdirectories
    DIR* dirp;
    struct dirent* entry;
    if (!(dirp = opendir(path))) {
        perror(path);
        return errno;
    }
    if (!(entry = readdir(dirp))) {
        perror(path);
        return errno;
    }
    char* newPath = "";
    sprintf(newPath, "%s/%s", path, entry->d_name);
    do {
        if (entry->d_type == DT_REG) {
            if (!filter(newPath, settings)) {
                execute(newPath, settings);
            }
        }
        else {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }
            if (!filter(newPath, settings)) {
                execute(newPath, settings);
            }
            search(newPath, settings);
        }
    } while ((entry = readdir(dirp)));
    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
