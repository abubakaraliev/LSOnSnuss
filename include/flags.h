#ifndef FLAGS_H
#define FLAGS_H

typedef struct {
    int ALL;            // -a
    int LONG;           // -l
    int ALMOSTALL;      // -A
    int RECURSIVE;      // -R
    int REVERSE;        // -r
    int SIZE;           // -s
    int TIME;           // -t
    int DEREFERENCE;    // -L
    int ONEFILEPERLINE; // -1
    int NOLISTOWNER;    // -g
    int NOGROUP;        // -G
    int DIRECTORYORDER; // -f
    int INDICATOR;      // -F
} Flags;

Flags parse_flags(int argc, char *argv[]);

#endif