#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char* argv[])
{
    struct timeval start, end;
    gettimeofday(&start, NULL);
    __pid_t pid;
    pid = fork();
    if (pid > 0)
    {
        wait(NULL); //chờ tiến trình con thực thi xong
        gettimeofday(&end, NULL);
        //lấy microseconds
        double thoigian = (end.tv_sec - start.tv_sec) +(end.tv_usec - start.tv_usec) / 1000000.0; 
        printf ("Thời gian thực thi: %.5f giây\n", thoigian);
    }
    if (pid == 0)
    {
        execl("/bin/sh", "sh", "-c", argv[1], NULL);
    }
    exit(0);
}