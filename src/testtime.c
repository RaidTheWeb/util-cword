#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int main(int argc, char** argv) {
    FILE* fp = fopen("/dev/serial", "r");
    printf("Opened serial stream\n");
    fprintf(fp, "Hello Serial World!\n");
    fclose(fp);
    free(fp);

    printf("Attempting to write to framebuffer!\n");

    int fd = open("/dev/fb0", O_RDWR);

    if(!fd) {
        printf("Failed to open framebuffer.\n");
        exit(1);
    }

    int i = 0;

    char filePath[128];
    fcntl(fd, 100, filePath);
    printf("file path is %s\n", filePath);

    printf("Funny!\n");
    ioctl(fd, 1, &i);
    printf("Funny done!\n");

    return 0;
}