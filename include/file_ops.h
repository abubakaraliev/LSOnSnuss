#ifndef FILE_OPS_H
#define FILE_OPS_H

#include "flags.h"
#include <sys/stat.h>

typedef struct {
    char **names;
    int count;
} FileList;

FileList* get_file_list(const char *path, const Flags *flags);
void sort_files(FileList *files, const Flags *flags);
void free_file_list(FileList *files);
char** get_paths(int argc, char *argv[], int *path_count);

#endif 