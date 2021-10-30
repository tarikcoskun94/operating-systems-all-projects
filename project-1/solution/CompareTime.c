//Usage: ./ComapareTime <ProgramToTest> <src> <dst> <bufferSize>
//Measure the time elapsed during MyCopy, ForkCopy & PipeCopy
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if(argc != 5)
	{
		printf("\n usage: ./TimeTest <ProgramToTest> <src> <dst> <bufferSize>\n");
		return -1;
	}
	pid_t pid;
	clock_t t_begin=clock();
	pid=fork();
	switch(pid)
	{
		case -1: //error
			fprintf(stderr, "Fork Failed\n");
			exit(-1);
		case 0: //child process
			if(execl(argv[1],argv[1],argv[2],argv[3],argv[4],(char*)0)==-1)
			{
				fprintf(stderr, "Call Failed\n");
				exit(-1);
			}
			exit(0);
		default: //parent process
			wait(NULL); //wait for the child process to terminate
			clock_t t_end=clock();
            printf("%s's Time Elapsed: %.2fms\n", argv[1],
				(double)(t_end-t_begin)*1000/CLOCKS_PER_SEC
				);
			exit(0);
	}
	return 0;
}
