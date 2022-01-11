#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>

#define BLOCK_SIZE 512
typedef uint8_t BYTE;

bool isJpeg(BYTE *block);

int main(int argc, char *argv[])
{
    //for naming
    int jpgnum = 0;
    //error and input checks
    if(argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open.\n");
        return 2;
    }

    //initally have not found a JPEG
    bool foundJpeg = false;
    //create a storage file and buffer block
    FILE* img;
    BYTE buffer[BLOCK_SIZE];
    //while we read, we tkae that and write it elsewhere
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, file))
    {
        //if we detect a jpeg, start writing
        if(isJpeg(buffer))
        {
            //initialize the name
            char filename[8];
            sprintf(filename, "%03i.jpg", jpgnum);

            //if jpeg is already found beforehand, then that means it is in the buffer, we have to close it.
            if(foundJpeg)
            {
                fclose(img);
            }
            else
            {
                foundJpeg = true;
            }

            //open new file to write into and write into it
            img = fopen(filename, "w");
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
            jpgnum++;

        }
        else
        {
            //not the start of a new jpeg but continuing from old jpeg
            if(foundJpeg)
            {
                //keep writing to it
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
            }

        }
    }
    //close files after we are done.
    fclose(file);
    fclose(img);
}

bool isJpeg(BYTE *block)
{
    //header check for jpeg traces
    if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
    {
        return true;
    }
    else
    {
        return false;
    }
}