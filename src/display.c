#include "display.h"
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

// Affiche les permissions d'un fichier sous forme de chaîne de caractères (ex: drwxr-xr-x)
static void print_permissions(mode_t mode) {
    printf("%c%c%c%c%c%c%c%c%c%c",
        S_ISDIR(mode) ? 'd' : '-',
        mode & S_IRUSR ? 'r' : '-',
        mode & S_IWUSR ? 'w' : '-',
        mode & S_IXUSR ? 'x' : '-',
        mode & S_IRGRP ? 'r' : '-',
        mode & S_IWGRP ? 'w' : '-',
        mode & S_IXGRP ? 'x' : '-',
        mode & S_IROTH ? 'r' : '-',
        mode & S_IWOTH ? 'w' : '-',
        mode & S_IXOTH ? 'x' : '-');
}

// Affiche les informations d'un fichier selon les flags spécifiés
void display_file_info(const char *filename, const struct stat *stats, const Flags *flags) {
    if (flags->LONG) {
        print_permissions(stats->st_mode);
        printf(" %lu", stats->st_nlink);
        
        // Affiche le propriétaire si demandé
        if (!flags->NOLISTOWNER) {
            struct passwd *pw = getpwuid(stats->st_uid);
            printf(" %s", pw ? pw->pw_name : "unknown");
        }
        
        // Affiche le groupe si demandé
        if (!flags->NOGROUP) {
            struct group *gr = getgrgid(stats->st_gid);
            printf(" %s", gr ? gr->gr_name : "unknown");
        }
        
        // Affiche la taille si demandé
        if (flags->SIZE) {
            printf(" %ld", stats->st_size);
        }
        
        // Affiche la date de dernière modification
        char time_str[20];
        strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&stats->st_mtime));
        printf(" %s", time_str);
    }
    
    printf(" %s", filename);
    
    // Ajoute un / après les noms de répertoires si l'indicateur est activé
    if (flags->INDICATOR && S_ISDIR(stats->st_mode)) {
        printf("/");
    }
    
    // Nouvelle ligne ou espace selon le format demandé
    printf(flags->ONEFILEPERLINE ? "\n" : "  ");
}

// Affiche le contenu d'un répertoire selon les flags spécifiés
void display_directory(const char *path, const Flags *flags) {
    // Récupère la liste des fichiers
    FileList *files = get_file_list(path, flags);
    if (!files) {
        printf("Cannot open directory %s\n", path);
        return;
    }
    
    // Trie les fichiers selon les critères demandés
    sort_files(files, flags);
    
    struct stat stats;
    char filepath[4096];
    
    // Affiche chaque fichier
    for (int i = 0; i < files->count; i++) {
        snprintf(filepath, sizeof(filepath), "%s/%s", path, files->names[i]);
        if (lstat(filepath, &stats) == 0) {
            display_file_info(files->names[i], &stats, flags);
        }
    }
    
    // Ajoute une nouvelle ligne si nécessaire
    if (!flags->ONEFILEPERLINE) {
        printf("\n");
    }
    
    // Traitement récursif des sous-répertoires si demandé
    if (flags->RECURSIVE) {
        for (int i = 0; i < files->count; i++) {
            // Ignore . et ..
            if (files->names[i][0] == '.' && 
               (!strcmp(files->names[i], ".") || !strcmp(files->names[i], ".."))) {
                continue;
            }
            
            snprintf(filepath, sizeof(filepath), "%s/%s", path, files->names[i]);
            if (lstat(filepath, &stats) == 0 && S_ISDIR(stats.st_mode)) {
                printf("\n%s:\n", filepath);
                display_directory(filepath, flags);
            }
        }
    }
    
    // Libération de la mémoire
    for (int i = 0; i < files->count; i++) {
        free(files->names[i]);
    }
    free(files->names);
    free(files);
}