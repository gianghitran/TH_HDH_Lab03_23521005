#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
int main() {
    const int SIZE = 10; // Kích thước buffer
    const char *name = "bounded_buffer"; // Tên shared memory
    int fd;
    char *ptr;
    int total =0;
    // Kết nối tới shared memory
    fd = shm_open(name, O_RDWR, 0666);
    ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    
    while (1) {
        if (strcmp(ptr, "cho phep ghi") != 0 && strcmp(ptr, "-1") != 0) {
            int number = atoi(ptr);
            total += number;
            printf("Consumer read: %d -> Total: %d\n", number, total);

            if (total > 100) {
                strcpy(ptr, "-1"); // Gửi tín hiệu dừng tới producer
                break;
            } else {
                strcpy(ptr, "cho phep ghi"); // Cho phép producer ghi tiếp
            }
        }
        sleep(1); // Thêm độ trễ nhỏ để tránh busy-waiting
    }

    munmap(ptr, SIZE);
    close(fd);
    shm_unlink(name);

    return 0;
}
