//Name : Yihui(Andy) Qin
//Date : 01/06/2022
//Title : Lab1 – task 2
//Description : This program copies files using command line
//with system calls in operating system

#include <unistd.h> // read(), write()
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h> // errno
#include <stdio.h>
#include <stdlib.h>


#define BUF_SIZE 2048 //buffer size
// copies a files form src_filename to dst_filename using syscalls open(), read(), write(), close()
int syscall_copy(char *src_filename, char *dst_filename)
{
    int src_fd, dst_fd;
    void *buf;

    src_fd = open(src_filename, O_RDONLY); // opens a file for reading
    if (src_fd < 0)
    { // open() error checking
        fprintf(stderr, "unable to open %s for reading: %i\n", src_filename, errno);
        close(src_fd);
        exit(0);
    }
    // O_WRONLY - write only
    // O_CREAT - create file if it doesn't exist
    // O_TRUNC - truncates file to length 0 if it already exists (deletes existing file)
    // opens a file for writing; erases old file/creates a new file
    dst_fd = open(dst_filename, O_WRONLY | O_CREAT | O_TRUNC,0644);
    if (dst_fd < 0)
    { // open() error checking
        fprintf(stderr, "unable to open/create %s for writing: %i\n", dst_filename, errno);
        close(dst_fd);
        exit(0);
    }

    // read/ write loop
    buf = malloc((size_t)BUF_SIZE); // allocate a buffer to store read data
    // reads up to BUF_SIZE bytes from src_filename
    
    while(read(src_fd, buf, sizeof(buf)) > 0)
    {
        // writes bytes_read to dst_filename
         write(dst_fd, buf, sizeof(buf));
    }
        

    // closes src_fd file descriptor
    close(src_fd);
    // closes dst_fd file descriptor
    close(dst_fd);
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
    char *src = argv[1];
    char *dst = argv[2];
    syscall_copy(src, dst);
}

