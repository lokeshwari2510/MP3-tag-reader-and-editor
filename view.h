#ifndef VIEW_H
// Prevent multiple inclusion of header file
#define VIEW_H

// Standard input/output functions
#include <stdio.h>

// Function prototype to calculate frame size
int get_size(char *size_buf);

// Function prototype to display MP3 tags
void view_tags(FILE *fp);

// End of header guard
#endif