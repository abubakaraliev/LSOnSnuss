#include "file_ops.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// Compare alphabétiquement deux chaînes de caractères (insensible à la casse)
static int compare_alpha(const void *a, const void *b) {
    return strcasecmp(*(const char**)a, *(const char**)b);
}

// Compare les dates de modification de deux fichiers
static int compare_time(const void *a, const void *b) {
    struct stat stat_a, stat_b;
    lstat(*(const char**)a, &stat_a);
    lstat(*(const char**)b, &stat_b);
    return stat_b.st_ctime - stat_a.st_ctime;
}

// Détermine si un fichier doit être inclus dans la liste selon les flags
static int should_include_file(const char *name, const Flags *flags) {
    if (name[0] == '.') {
        if (!flags->ALL && !flags->ALMOSTALL) {
            return 0;
        }
        if (flags->ALMOSTALL && (!strcmp(name, ".") || !strcmp(name, ".."))) {
            return 0;
        }
    }
    return 1;
}

// Récupère la liste des fichiers d'un répertoire
FileList* get_file_list(const char *path, const Flags *flags) {
    FileList *list = malloc(sizeof(FileList));
    list->names = NULL;
    list->count = 0;

    DIR *dir = opendir(path);
    if (!dir) return list;

    struct dirent *entry;
    while ((entry = readdir(dir))) {
        if (!should_include_file(entry->d_name, flags)) 
            continue;

        list->names = realloc(list->names, (list->count + 1) * sizeof(char*));
        list->names[list->count] = strdup(entry->d_name);
        list->count++;
    }

    closedir(dir);
    return list;
}

// Trie les fichiers selon les flags spécifiés
void sort_files(FileList *files, const Flags *flags) {
    if (flags->DIRECTORYORDER) 
        return;

    if (flags->TIME)
        qsort(files->names, files->count, sizeof(char*), compare_time);
    else
        qsort(files->names, files->count, sizeof(char*), compare_alpha);

    // Inverse l'ordre si demandé
    if (flags->REVERSE) {
        for (int i = 0; i < files->count / 2; i++) {
            char *temp = files->names[i];
            files->names[i] = files->names[files->count - 1 - i];
            files->names[files->count - 1 - i] = temp;
        }
    }
}