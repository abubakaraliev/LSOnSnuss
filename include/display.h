#ifndef DISPLAY_H
#define DISPLAY_H

#include "flags.h"
#include "file_ops.h"
#include <sys/stat.h>

void display_directory(const char *path, const Flags *flags);
void display_file_info(const char *filename, const struct stat *stats, const Flags *flags);

#endif 