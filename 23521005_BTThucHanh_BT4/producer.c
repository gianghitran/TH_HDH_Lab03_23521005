#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>

int main() {
    const int SIZE = 10; // Kích thước buffer
    const char *name = "bounded_buffer"; // Tên shared memory
    int fd;
    char *ptr;

    // Tạo shared memory
    fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, SIZE);
    ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    srand(time(NULL)); //Tạo số ngẫu nhiên
    strcpy(ptr, "cho phep ghi"); // Khởi tạo buffer cho phép ghi

    while (1) {
        if (strcmp(ptr, "cho phep ghi") == 0) {
            /* generate a random number in the range [10, 20] */
            int random_num = rand() % 11 + 10;
            char buffer[SIZE]; // Temporary buffer to store the random number as a string
            snprintf(buffer, SIZE, "%d", random_num); // Convert number to string

            strcpy(ptr, buffer); // Ghi chuỗi vào shared memory
            printf("Memory update: %d\n", random_num);
        } else if (strcmp(ptr, "-1") == 0) {
            printf("Tong lon hon 100. Ket thuc chuong trinh!.\n");
            break;
        }
        sleep(1); // Thêm độ trễ nhỏ để tránh busy-waiting
    }
    
    munmap(ptr, SIZE);
    close(fd);
    return 0;
}
