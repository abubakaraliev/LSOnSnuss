#include "flags.h"
#include "file_ops.h"
#include "display.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    Flags flags = parse_flags(argc, argv);
    
    // Utilise le répertoire courant si aucun chemin n'est fourni
    char *default_path = ".";
    int path_count = 0;
    char **paths = NULL;

    // Récupère les chemins des arguments après les flags
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-') {
            paths = realloc(paths, (path_count + 1) * sizeof(char*));
            paths[path_count] = strdup(argv[i]);
            path_count++;
        }
    }

    // Utilise le chemin par défaut si aucun n'est fourni
    if (path_count == 0) {
        paths = malloc(sizeof(char*));
        paths[0] = strdup(default_path);
        path_count = 1;
    }

    for (int i = 0; i < path_count; i++) {
        if (path_count > 1 || flags.RECURSIVE) {
            printf("%s:\n", paths[i]);
        }
        display_directory(paths[i], &flags);
    }

    // Nettoyage
    for (int i = 0; i < path_count; i++) {
        free(paths[i]);
    }
    free(paths);

    return EXIT_SUCCESS;
}