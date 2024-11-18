#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#include <ctype.h>

// Hàm kiểm tra input có phải số nguyên dương không
int NguyenDuong(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) 
    {
        if (!isdigit(str[i])) return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    // Kiểm tra tham số là số nguyên dương
    if (!NguyenDuong(argv[1])) 
    {
        fprintf(stderr, "Tham so nhap vao khong phai so nguyen duong!\n");
        exit(1);
    }
    int n = atoi(argv[1]);
    int *buffer = mmap(0, 1024, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    pid_t pid = fork();
    if (pid >0)
    {
        wait(NULL);
        // In chuỗi từ shared memory
        for (int i = 0; buffer[i] != -1; i++) 
        {
            printf("%d", buffer[i]);
            if (buffer[i + 1] != -1) printf(", ");
        }
        printf("\n");
        munmap(buffer, 1024);
    }   
    if (pid == 0) 
    {
        int i = 0;
        while (n != 1) 
        {
            buffer[i++] = n;
            if (n % 2 == 0) n /= 2;
            else n = 3 * n + 1;
        }
        buffer[i++] = 1; // thêm 1 vào cuối chuỗi
        buffer[i] = -1; // kết thúc chuỗi
        exit(0); 
    }
    return 0;
}
