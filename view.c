#include <stdio.h>
#include <string.h>
#include "view.h"

// Function to convert 4-byte frame size into integer
int get_size(char *size_buf)
{
    int size;

    // Combine 4 bytes to get actual frame size
    size = ((unsigned char)size_buf[0] << 24) |
           ((unsigned char)size_buf[1] << 16) |
           ((unsigned char)size_buf[2] << 8)  |
           ((unsigned char)size_buf[3]);

    // Return frame size
    return size;
}

// Function to display MP3 tag information
void view_tags(FILE *fp)
{
    // Store frame ID
    char tag[5];

    // Store frame size bytes
    char size_buf[4];

    // Store frame size
    int size;

    // Store frame data
    char data[1000];

    // Display project header
    printf("---------------------------------------------------------\n");
    printf("        MP3 Tag Reader and Editor for ID3v2\n");
    printf("---------------------------------------------------------\n\n");

    // Skip 10-byte ID3 header
    fseek(fp, 10, SEEK_SET);

    // Read six metadata frames
    for(int i = 0; i < 6; i++)
    {
        // Read frame ID
        fread(tag, 4, 1, fp);

        // Add string terminator
        tag[4] = '\0';

        // Read frame size
        fread(size_buf, 4, 1, fp);

        // Convert size bytes into integer
        size = get_size(size_buf);

        // Skip flags and encoding byte
        fseek(fp, 3, SEEK_CUR);

        // Read frame content
        fread(data, 1, size - 1, fp);

        // Add string terminator
        data[size - 1] = '\0';

        // Check for title frame
        if(strcmp(tag, "TIT2") == 0)
        {
            printf("%-10s : %s\n", "Title", data);
        }

        // Check for artist frame
        else if(strcmp(tag, "TPE1") == 0)
        {
            printf("%-10s : %s\n", "Artist", data);
        }

        // Check for album frame
        else if(strcmp(tag, "TALB") == 0)
        {
            printf("%-10s : %s\n", "Album", data);
        }

        // Check for year frame
        else if(strcmp(tag, "TYER") == 0)
        {
            printf("%-10s : %s\n", "Year", data);
        }

        // Check for genre frame
        else if(strcmp(tag, "TCON") == 0)
        {
            printf("%-10s : %s\n", "Music", data);
        }

        // Check for comment/composer frame
        else if(strcmp(tag, "COMM") == 0)
        {
            printf("%-10s : %s\n", "Composer", data);
        }
    }

    // Display footer
    printf("\n---------------------------------------------------------\n");
}