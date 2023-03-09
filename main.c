#include <stdio.h>
#include <stdlib.h>

void print_filedata(unsigned char* tmp, long size)
{
    printf("\n\nFirst 3072 bytes of hexadecimal binary data :---------- \n\n");

    for(long i=0; i<size; i++)
    {
        printf("%X", tmp[i]);
    }

    printf("\n\nDecoded data:---------- \n\n");

    for(long j=0; j<size; j++)
    {
        printf("%c", tmp[j]);
    }
}

int main(int argc, char *argv[])
{
    printf("-- FILE SHREDDER v1.0.0 by Iqmal Jamaludin. Created on March 4, 2023 --");

    FILE *file = fopen(argv[1], "r+");

    if(file == NULL)
    {
        printf("\n\nOops! Fail to open file.\n");
        return -1;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);   //last position so it will tell file size
    fseek(file, 0, SEEK_SET);

//    unsigned char buffer[file_size];
    unsigned char *temp = (unsigned char*)calloc(file_size, sizeof(unsigned char));

    fread(temp, 1, file_size, file);

    //show first 3 kB
    unsigned int file_preview_size = 3072 * sizeof(unsigned char);
    print_filedata(temp, file_preview_size);

    // overwrite the file
    printf("\n\nNow overwriting file with zeroes binary digit...\n\n");
    for(long k=0; k<file_size; k++)
    {
        temp[k] = 0;
    }

    fseek(file, 0, SEEK_SET);
    fwrite(temp, 1, file_size, file);

    printf("\n\nDone overwriting file data...\n\n");

    //reprint data for confirmation
    print_filedata(temp, file_preview_size);

    fclose(file);
    free(temp);

    return 0;
}
