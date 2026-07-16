// Standard input/output functions
#include <stdio.h>

// Memory allocation functions
#include <stdlib.h>

// String handling functions
#include <string.h>

// Header file for view operations
#include "view.h"

// Header file for edit operations
#include "edit.h"

// Function to edit a selected MP3 tag
void edit_tag(FILE *src, char *tag_name, char *new_data)
{
    // Store frame ID
    char tag[5];

    // Store frame size bytes
    char size_buf[4];

    // Store frame flags
    char flag[2];

    // Store frame size
    int size;

    // Create temporary MP3 file
    FILE *temp = fopen("temp.mp3", "wb");

    // Check if temp file is created
    if(temp == NULL)
    {
        printf("Unable to create temp file\n");
        return;
    }

    // Store ID3 header
    char header[10];

    // Read ID3 header from source file
    fread(header, 1, 10, src);

    // Write ID3 header to temp file
    fwrite(header, 1, 10, temp);

    // Display status message
    printf("header copied\n");

    // Process first six frames
    for(int i = 0; i < 6; i++)
    {
        // Read frame ID
        fread(tag, 1, 4, src);

        // Add string terminator
        tag[4] = '\0';

        // Read frame size
        fread(size_buf, 1, 4, src);

        // Convert size bytes into integer
        size = get_size(size_buf);

        // Read frame flags
        fread(flag, 1, 2, src);

        // Check for selected tag
        if(strcmp(tag, tag_name) == 0)
        {
            // Calculate new tag size
            int new_size = strlen(new_data) + 1;

            // Store new size in big-endian format
            char be_size[4];

            // Convert size into byte format
            be_size[0] = (new_size >> 24) & 0xFF;
            be_size[1] = (new_size >> 16) & 0xFF;
            be_size[2] = (new_size >> 8) & 0xFF;
            be_size[3] = new_size & 0xFF;

            // Write frame ID to temp file
            fwrite(tag, 1, 4, temp);

            // Write updated size
            fwrite(be_size, 1, 4, temp);

            // Write frame flags
            fwrite(flag, 1, 2, temp);

            // Write text encoding byte
            fputc(0, temp);

            // Write updated tag data
            fwrite(new_data, 1, strlen(new_data), temp);

            // Skip old tag data
            fseek(src, size, SEEK_CUR);

            // Variable to copy remaining data
            char ch;

            // Copy remaining file content
            while(fread(&ch, 1, 1, src))
            {
                fwrite(&ch, 1, 1, temp);
            }

            // Exit loop after editing
            break;
        }
        else
        {
            // Copy frame ID
            fwrite(tag, 1, 4, temp);

            // Copy frame size
            fwrite(size_buf, 1, 4, temp);

            // Copy frame flags
            fwrite(flag, 1, 2, temp);

            // Allocate memory for frame data
            char *buffer = malloc(size);

            // Read frame data
            fread(buffer, 1, size, src);

            // Write frame data to temp file
            fwrite(buffer, 1, size, temp);

            // Free allocated memory
            free(buffer);
        }
    }

    // Close source file
    fclose(src);

    // Close temp file
    fclose(temp);

    // Delete old MP3 file
    remove("sample.mp3");

    // Rename temp file as original file
    rename("temp.mp3", "sample.mp3");

    // Display success message
    printf("Tag updated successfully\n");
}