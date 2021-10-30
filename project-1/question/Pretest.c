//Zuhal Can

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

//Maximum size of the array
#define MAX_SIZE  200
typedef struct
{
    int pos;
    int line;
} sMismatchingPos;

int isFileSame(char *src, char *dest, sMismatchingPos *psMismatchPos);
void checkFileSimilarity(char *name, char *src, char *dest);
int testMyShell();
int testMoreShell();
int testDupShell();

int main(void)
{
    //int i, size;
    char command[200];
    
    char srcFile[] = "SourceFile.txt";
    char dstFile1[] = "DestFile1.txt";
    char dstFile2[] = "DestFile2.txt";
    char dstFile3[] = "DestFile3.txt";
    int bufferSize = 1024;
    
    sprintf(command,"make");
    system(command);
    
    //Test MakeCopy.c
    sprintf(command,"./MakeCopy %s %s %d", srcFile, dstFile1, bufferSize);
    system(command);
    checkFileSimilarity("MakeCopy", srcFile, dstFile1);
    
    
    //Test ForkCopy.c
    sprintf(command,"./ForkCopy %s %s %d", srcFile, dstFile2, bufferSize);
    system(command);
    checkFileSimilarity("ForkCopy", srcFile, dstFile2);
    
    
    //Test PipeCopy.c
    sprintf(command,"./PipeCopy %s %s %d", srcFile, dstFile3, bufferSize);
    system(command);
    checkFileSimilarity("PipeCopy", srcFile, dstFile3);
    
    
    //Test Performance: CompareTime.c
    sprintf(command,"./CompareTime MakeCopy %s MCTestdest.txt %d", srcFile, bufferSize);
    system(command);
    sprintf(command,"./CompareTime ForkCopy %s FCTestdest.txt %d", srcFile, bufferSize);
    system(command);
    sprintf(command,"./CompareTime PipeCopy %s PCTestdest.txt %d", srcFile, bufferSize);
    system(command);
    
    
    //Test MyShell.c
    testMyShell();
    
    
    //Test MoreShell.c
    testMoreShell();
    
    
    //Test DupShell.c
    testDupShell();

    
    //Check Readme
    printf("10 points for appropriate Readme file\n");
    
    return 0;
}


int isFileSame(char *src, char *dest, sMismatchingPos *psMismatchPos)
{
    FILE *fp1, *fp2;
    fp1  = fopen(src, "r");
    fp2  = fopen(dest, "r");
    // pos and line to track of position of mismatch
    int pos = 0, line = 1;
    int ch1 =0, ch2 = 0;
    int isContentMatch = 0;
    // iterate loop until EOF
    do
    {
        //fetch character of both file
        ch1 = fgetc(fp1);
        ch2 = fgetc(fp2);
        ++pos;
        // if both variable encounters new
        // line then line variable is incremented
        // and pos variable is set to 0
        if ((ch1 == '\n') && (ch2 == '\n'))
        {
            ++line;
            pos = 0;
        }
        //update structure variable
        psMismatchPos->pos = pos;
        psMismatchPos->line = line;
        // if fetched data is not equal then
        // set the mismatched flag
        if(ch1!= ch2)
        {
            isContentMatch =1;
            break;
        }
    }
    while (ch1 != EOF && ch2 != EOF);
    
    fclose(fp1);
    fclose(fp2);
    
    //return flag status
    return isContentMatch;
}

void checkFileSimilarity(char *name, char *src, char *dest)
{
    int isContentMatch = 0;
    sMismatchingPos misMatchPos = {0};
    
    isContentMatch = isFileSame(src, dest, &misMatchPos);
    if(isContentMatch)
    {
        printf(">>%s FAILED the test: Files are different\n", name);
        //print line and pos where both file mismatch
        printf(">>Check %s, Line Number : %d ",dest, misMatchPos.line);
        printf("Position : %d \n",misMatchPos.pos);
        
    }
    else
    {
        printf(">>%s PASSED the test: Files are same\n", name);
    }
}

int testMyShell()
{
    
    char command[200];
    int fds[2];                      // an array that will hold two file descriptors
    pipe(fds);                       // populates fds with two file descriptors
    pid_t pid = fork();              // create child process that is a clone of the parent
    
    
    int fx = open("_MyShellFile.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    FILE *fy = fopen("_testMyShellFile.txt", "w+");
    
    if (pid == 0) {                  // if pid == 0, then this is the child process
        dup2(fds[0], STDIN_FILENO);    // fds[0] (the read end of pipe) donates its data to file descriptor 0
        close(fds[0]);                 // file descriptor no longer needed in child since stdin is a copy
        close(fds[1]);                 // file descriptor unused in child
        char *argv[] = {(char *)"sort", NULL};   // create argument vector
        dup2(fx, 1);
        execlp("./MyShell", "MyShell", NULL); // run sort command (exit if something went wrong)
        close(fx);
    }
    
    // if we reach here, we are in parent process
    close(fds[0]);                 // file descriptor unused in parent
    const char *words[] = {"ls", "q"};
    // write input to the writable file descriptor so it can be read in from child:
    size_t numwords = sizeof(words)/sizeof(words[0]);
    for (size_t i = 0; i < numwords; i++) {
        dprintf(fds[1], "%s\n", words[i]);
    }
    
    // send EOF so child can continue (child blocks until all input has been processed):
    close(fds[1]);
    
    sprintf(command,"ls > _testMyShellFile.txt");
    system(command);
    sprintf(command,"sed -i \'\' \'$d\' _MyShellFile.txt >> _MyShellFile.txt");
    system(command);
    sprintf(command,"sed -i \'\' -e \'$a\\' _MyShellFile.txt >> _MyShellFile.txt");
    system(command);
    
    checkFileSimilarity("MyShell", "_MyShellFile.txt", "_testMyShellFile.txt");
    fclose(fy);
    
    int status;
    pid_t wpid = waitpid(pid, &status, 0); // wait for child to finish before exiting
    return wpid == pid && WIFEXITED(status) ? WEXITSTATUS(status) : -1;
    
}

int testMoreShell()
{
    
    char command[200];
    int fds[2];                      // an array that will hold two file descriptors
    pipe(fds);                       // populates fds with two file descriptors
    pid_t pid = fork();              // create child process that is a clone of the parent
    
    
    int fx = open("_MoreShellFile.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    FILE *fy = fopen("_testMoreShellFile.txt", "w+");
    
    if (pid == 0) {                  // if pid == 0, then this is the child process
        dup2(fds[0], STDIN_FILENO);    // fds[0] (the read end of pipe) donates its data to file descriptor 0
        close(fds[0]);                 // file descriptor no longer needed in child since stdin is a copy
        close(fds[1]);                 // file descriptor unused in child
        char *argv[] = {(char *)"sort", NULL};   // create argument vector
        dup2(fx, 1);
        execlp("./MoreShell", "MoreShell", NULL); // run sort command (exit if something went wrong)
        close(fx);
    }
    
    // if we reach here, we are in parent process
    close(fds[0]);                 // file descriptor unused in parent
    const char *words[] = {"ls –l ./tmp", "q"};
    // write input to the writable file descriptor so it can be read in from child:
    size_t numwords = sizeof(words)/sizeof(words[0]);
    for (size_t i = 0; i < numwords; i++) {
        dprintf(fds[1], "%s\n", words[i]);
    }
    
    // send EOF so child can continue (child blocks until all input has been processed):
    close(fds[1]);
    
    sprintf(command,"ls –l ./tmp > _testMoreShellFile.txt");
    system(command);
    sprintf(command,"sed -i \'\' \'$d\' _MoreShellFile.txt >> _MoreShellFile.txt");
    system(command);
    sprintf(command,"sed -i \'\' -e \'$a\\' _MoreShellFile.txt >> _MoreShellFile.txt");
    system(command);
    
    checkFileSimilarity("MoreShell", "_MoreShellFile.txt", "_testMoreShellFile.txt");
    fclose(fy);
    
    int status;
    pid_t wpid = waitpid(pid, &status, 0); // wait for child to finish before exiting
    return wpid == pid && WIFEXITED(status) ? WEXITSTATUS(status) : -1;
    
}

int testDupShell()
{
    
    char command[200];
    int fds[2];                      // an array that will hold two file descriptors
    pipe(fds);                       // populates fds with two file descriptors
    pid_t pid = fork();              // create child process that is a clone of the parent
    
    
    int fx = open("_DupShellFile.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    FILE *fy = fopen("_testDupShellFile.txt", "w+");
    
    if (pid == 0) {                  // if pid == 0, then this is the child process
        dup2(fds[0], STDIN_FILENO);    // fds[0] (the read end of pipe) donates its data to file descriptor 0
        close(fds[0]);                 // file descriptor no longer needed in child since stdin is a copy
        close(fds[1]);                 // file descriptor unused in child
        char *argv[] = {(char *)"sort", NULL};   // create argument vector
        dup2(fx, 1);
        execlp("./DupShell", "DupShell", NULL); // run sort command (exit if something went wrong)
        close(fx);
    }
    
    // if we reach here, we are in parent process
    close(fds[0]);                 // file descriptor unused in parent
    const char *words[] = {"ls -l | wc", "q"};
    // write input to the writable file descriptor so it can be read in from child:
    size_t numwords = sizeof(words)/sizeof(words[0]);
    for (size_t i = 0; i < numwords; i++) {
        dprintf(fds[1], "%s\n", words[i]);
    }
    
    // send EOF so child can continue (child blocks until all input has been processed):
    close(fds[1]);
    
    sprintf(command,"ls -l | wc > _testDupShellFile.txt");
    system(command);
    sprintf(command,"sed -i \'\' \'s/^>//\' _DupShellFile.txt >> _DupShellFile.txt");
    system(command);
    sprintf(command,"sed -i \'\' \'$d\' _DupShellFile.txt >> _DupShellFile.txt");
    system(command);
    sprintf(command,"sed -i \'\' -e \'$a\\' _DupShellFile.txt >> _DupShellFile.txt");
    system(command);
    
    checkFileSimilarity("DupShell", "_DupShellFile.txt", "_testDupShellFile.txt");
    fclose(fy);
    
    int status;
    pid_t wpid = waitpid(pid, &status, 0); // wait for child to finish before exiting
    return wpid == pid && WIFEXITED(status) ? WEXITSTATUS(status) : -1;
    
}
