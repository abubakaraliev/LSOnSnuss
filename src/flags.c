#include "flags.h"
#include <stdlib.h>
#include <unistd.h>

// Analyse les options passées en ligne de commande et retourne une structure Flags
Flags parse_flags(int argc, char *argv[]) {
    Flags flags = {0}; // Initialise tous les flags à 0
    int opt;

    // Parcourt toutes les options avec getopt
    while ((opt = getopt(argc, argv, "alARrstL1gfFG")) != -1) {
        switch (opt) {
            case 'a': flags.ALL = 1; break;            // Affiche les fichiers cachés
            case 'A': flags.ALMOSTALL = 1; break;      // Affiche presque tout sauf . et ..
            case 'l': flags.LONG = 1; break;           // Format long
            case 'R': flags.RECURSIVE = 1; break;      // Récursif
            case 'r': flags.REVERSE = 1; break;        // Inverse l'ordre
            case 's': flags.SIZE = 1; break;           // Affiche la taille
            case 't': flags.TIME = 1; break;           // Trie par date
            case 'L': flags.DEREFERENCE = 1; break;    // Suit les liens symboliques
            case '1': flags.ONEFILEPERLINE = 1; break; // Un fichier par ligne
            case 'g': flags.NOLISTOWNER = 1; break;    // N'affiche pas le propriétaire
            case 'G': flags.NOGROUP = 1; break;        // N'affiche pas le groupe
            case 'F': flags.INDICATOR = 1; break;      // Ajoute indicateur de type
            case 'f':                                  // Pas de tri et montre tout
                flags.DIRECTORYORDER = 1;
                flags.ALMOSTALL = 1;
                break;
            default:
                exit(EXIT_FAILURE);
        }
    }

    return flags;
} 