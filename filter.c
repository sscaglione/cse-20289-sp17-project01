/* filter.c */

#include "search.h"

#include <errno.h>
#include <fcntl.h>
#include <string.h>

#include <dirent.h>
#include <fnmatch.h>
#include <sys/stat.h>
#include <unistd.h>
#include <libgen.h>

/**
 * Test whether or not the given path should be filtered out of the output.
 * @param   path        Path to file or directory.
 * @param   settings    Settings structure.
 * @return  Whether or not the path should be excluded from the output (true to
 * exclude, false to include).
 */
bool        filter(const char *path, const Settings *settings) {
    char* tempPath = "";
    strcpy(tempPath, path);
    struct stat attributes;
    if (lstat(tempPath, &attributes) == -1) {
        perror(tempPath);
        return errno;
    }
    if (settings->access && access(tempPath, settings->access) != 0) {
        return true;
    }
    if (settings->type != 0 && ((attributes.st_mode & S_IFMT) != settings->type)) {
        return true;
    }
    if (settings->empty == is_directory_empty(tempPath)) {
        return true;
    }
    if (fnmatch(settings->name, basename(tempPath), FNM_PATHNAME) != 0) {
        return true;
    }
    if (fnmatch(settings->path, tempPath, FNM_PATHNAME) != 0) {
        return true;
    }
    if (difftime(settings->newer, get_mtime(path)) < 0) {
        return true;
    }
    if (settings->uid != attributes.st_uid) {
        return true;
    }
    if (settings->gid != attributes.st_gid) {
        return true;
    }
    return false;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
