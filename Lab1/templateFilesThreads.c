// COEN 146L : Lab 1 - template to use for creating multiple thread to make file transfers (step 4)

#include <stdio.h>   // fprintf(), fread(), fwrite(), fopen(), fclose()
#include <stdlib.h>  // malloc(), free()
#include <pthread.h> // pthread_create()
#include <unistd.h>  // read(), write()
#include <fcntl.h>   // open(), close()
#include <errno.h>   // errno
#include <time.h>    // clock()

#define BUF_SIZE 2048 //buffer size

// data structure to hold copy
struct copy_struct {
	int thread_id; 
	char* src_filename;
	char* dst_filename; 
};

// copies a files from src_filename to dst_filename using functions fopen(), fread(), fwrite(), fclose()
int func_copy(char* src_filename, char* dst_filename) {
	void *buf;
	
	src = fopen(src_filename, "r");	// opens a file for reading
	if (src == NULL) { // fopen() error checking
		fprintf(stderr, "unable to open %s for reading: %i\n", src_filename, errno);
		exit(0);
	}
	dst = fopen(dst_filename, "w");	// opens a file for writing; erases old file/creates a new file
	if (dst == NULL) { // fopen() error checking
		fprintf(stderr, "unable to open/create %s for writing: %i\n", dst_filename, errno);
		exit(0);
	}

	buf = malloc((size_t)BUF_SIZE);  // allocate a buffer to store read data
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

// thread function to copy one file
void* copy_thread(void* arg) {
	struct copy_struct params = *(struct copy_struct*)arg;  // cast/dereference void* to copy_struct
	printf("thread[%i] - copying %s to %s\n", params.thread_id, params.src_filename, params.dst_filename);
	//call file copy function
	func_copy(params.src_filename, params.dst_filename);
	pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
	// check correct usage of arguments in command line
	int numFiles = atoi(argv[1])
	
	if(argc != 1 + 1 + 2 * numFiles)
	{
		printf("in correct format (should be in the form of ./programName numFiles src1 src2 ... dst1 dst2)");
		return -1;
	}
	
	char* src_filenames[]; // array of source files
	char* dst_filenames[]; // array of destination files
	int num_threads; // number of threads to create

	num_threads = numFiles;
	src_filenames = malloc(numFiles * sizeof(char*));
	dst_filenames = malloc(numFiles * sizeof(char*));

	int i;
	for(i = 0; i < numFiles; i++)
	{
		src_filenames[i] = argv[2 + i];
		dst_filenames[i] = argv[2 + 2 * numFiles + i];
	}
	
	pthread_t threads[num_threads]; //initialize threads
	struct copy_struct thread_params[num_threads]; // structure for each thread
	int i;
	for (i = 0; i < num_threads; i++) {
		// initialize thread parameters
		thread_params[i].thread_id = i;
		thread_params[i].src_filename = src_filenames[i];
		thread_params[i].dst_filename = dst_filenames[i];
		// create each copy thread
		// use pthread_create(.....);
		pthread_create(&threads[i], NULL, copy_thread, (void*)&thread_params[i])
	
	}

	// wait for all threads to finish
	for (i = 0; i < num_threads; i++) {
		pthread_join(threads[i], NULL);
	}
	pthread_exit(NULL);
}