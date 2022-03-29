//Name : Yihui(Andy) Qin
//Date : 01/06/2022
//Title : Lab1 – task 3
//Description : This program copies files using command line
//with function calls in built-in libraries and system calls
//to compare and contrast the time each takes.

#include <time.h>
#include <errno.h> // errno
#include <stdlib.h>
#include <stdio.h>

// checks the runtime to copy a file using functions vs syscalls
void check_copy_times(char *src_filename, char *dst_filename)
{
    clock_t func_start, func_end, syscall_start, syscall_end;

    // capture runtime of func_copy() using start clock, call the copy, end the clock
    double func_time;
    double syscall_time;

    func_start = clock();
    func_copy(src_filename, dst_filename);
    func_end = clock();
    func_time = ((double)(func_end - func_start)) / CLOCKS_PER_SEC;

    // capture runtime of syscall_copy() using start clock, call the copy, end the clock
    syscall_start = clock();
    syscall_copy(src_filename, dst_filename);
    syscall_end = clock();
    syscall_time = ((double)(syscall_end - syscall_start)) / CLOCKS_PER_SEC;

    printf("time to copy using functions: %.7f\n", func_time);
    printf("time to copy using syscalls: %.7f\n", syscall_time);
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
    check_copy_times(src, dst);
}
