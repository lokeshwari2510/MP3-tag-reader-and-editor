/* Name: Lokeshwari
Description:MP3 Tag Reader and Editor is a C program that reads
and edits metadata information such as Title, Artist, Album, Year, 
Genre, and Comments from MP3 files using ID3v2 tags. It uses file
 handling and command-line arguments to perform view and edit operations. */
// Standard input/output functions
#include <stdio.h>

// Memory allocation functions
#include <stdlib.h>

// String handling functions
#include <string.h>

// Header file for view operation
#include "view.h"

// Header file for edit operation
#include "edit.h"

// Function to get frame ID based on edit option
char *get_frame_id(char *option)
{
    // Check for title option
    if(strcmp(option, "-t") == 0)
        return "TIT2";

    // Check for artist option
    else if(strcmp(option, "-A") == 0)
        return "TPE1";

    // Check for album option
    else if(strcmp(option, "-a") == 0)
        return "TALB";

    // Check for year option
    else if(strcmp(option, "-y") == 0)
        return "TYER";

    // Check for genre option
    else if(strcmp(option, "-m") == 0)
        return "TCON";

    // Check for comment option
    else if(strcmp(option, "-c") == 0)
        return "COMM";

    // Return NULL for invalid option
    return NULL;
}

// Main function
int main(int argc, char *argv[])
{
    // File pointer for MP3 file
    FILE *fp;

    // Check for read operation
    if(strcmp(argv[1], "-r")==0)
    {
        // Open MP3 file in read mode
        fp = fopen(argv[2], "rb");

        // Check whether file opened successfully
        if(fp == NULL)
        {
            printf("Unable to open file\n");
            return 1;
        }

        // Display MP3 tags
        view_tags(fp);

        // Close file
        fclose(fp);
    }

    // Check for edit operation
    else if(strcmp(argv[1], "-e")==0)
    {
        // Store corresponding frame ID
        char *frame_id;

        // Get frame ID from option
        frame_id = get_frame_id(argv[2]);

        // Validate edit option
        if(frame_id == NULL)
        {
            printf("Invalid edit option\n");
            return 1;
        }

        // Open MP3 file in read mode
        fp = fopen(argv[4], "rb");

        // Check whether file opened successfully
        if(fp == NULL)
        {
            printf("Unable to open file\n");
            return 1;
        }

        // Edit selected tag
        edit_tag(fp, frame_id, argv[3]);
    }

    // Return successful execution
    return 0;
}