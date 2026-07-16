// Prevent multiple inclusion of header file
#ifndef EDIT_H

// Define header guard
#define EDIT_H

// Standard input/output functions
#include <stdio.h>

// Function prototype to edit a selected MP3 tag
void edit_tag(FILE *src, char *tag_name, char *new_data);

// End of header guard
#endif