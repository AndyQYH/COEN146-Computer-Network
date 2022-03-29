$(CC) = gcc
all: step1.c step2.c step3.c step4.c step5-6.c
	 $(CC) -o test1 step1.c step2.c step3.c -lm
	 $(CC) -o test2 step4.c -lpthread
	 $(CC) -o test3 step5-6.c -lm
	 cat /dev/random | head -c 100000 > src1.dat
	 cat /dev/random | head -c 100000 > src2.dat
	 cat /dev/random | head -c 100000 > src3.dat

clean:
	 rm test*
	 rm *.dat
