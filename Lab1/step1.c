//Name : Yihui(Andy) Qin
//Date : 01/06/2022
//Title : Lab1 – task 1
//Description : This program copies files using command line
//with function calls in built-in libraries

#include <stdio.h>
#include <stdlib.h> // malloc(), free()
#include <errno.h> // errno

#define BUF_SIZE 2048 //buffer size

// copies a files from src_filename to dst_filename using functions fopen(), fread(), fwrite(), fclose()
int func_copy(char *src_filename, char *dst_filename)
{
    FILE *src;
    FILE *dst;
    char *buf;

    src = fopen(src_filename, "r"); // opens a file for reading
    if (src == NULL)
    { // fopen() error checking
        fprintf(stderr, "unable to open %s for reading: %i\n", src_filename, errno);
        exit(0);
    }
    dst = fopen(dst_filename, "w"); // opens a file for writing; erases old file/creates a new file
    if (dst == NULL)
    { // fopen() error checking
        fprintf(stderr, "unable to open/create %s for writing: %i\n", dst_filename, errno);
        exit(0);
    }

    buf = malloc((size_t)BUF_SIZE); // allocate a buffer to store read data
    // reads content of file is loop iterations until end of file

    while (fread(buf, sizeof(buf), 1, src) == 1)
    {
        // writes bytes_read to dst_filename
        fwrite(buf, sizeof(buf), 1, dst);
    }
    // closes src file pointer
    fclose(src);
    // closes dst file pointer
    fclose(dst);
    // frees memory used for buf
    free(buf);

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    { // check correct usage
        fprintf(stderr, "usage: %s <src_filename> <dst_filename>\n", argv[0]);
        exit(1);
    }
    char* src = argv[1];
    char* dst = argv[2];
    func_copy(src,dst);

}

