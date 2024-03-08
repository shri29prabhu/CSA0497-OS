#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
void displayFileContent(int fileDescriptor) {
    char buffer[1024];
    ssize_t bytesRead;
    while ((bytesRead = read(fileDescriptor, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytesRead);
    }
    if (bytesRead < 0) {
        perror("Error reading file");
        exit(EXIT_FAILURE);
    }
}
int main() {
    int fileDescriptor = open("example.txt", O_RDONLY);
    if (fileDescriptor < 0) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    printf("File Content:\n");
    displayFileContent(fileDescriptor);
    off_t newPosition = lseek(fileDescriptor, 0, SEEK_SET);

    if (newPosition < 0) {
        perror("Error seeking file");
        exit(EXIT_FAILURE);
    }
    struct stat fileStat;
    if (fstat(fileDescriptor, &fileStat) < 0) {
        perror("Error getting file information");
        exit(EXIT_FAILURE);
    }
    printf("\nFile Information:\n");
    printf("File Size: %ld bytes\n", fileStat.st_size);
    printf("File Permissions: %o\n", fileStat.st_mode);
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }
    struct dirent *entry;
    printf("\nDirectory Contents:\n");
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    close(fileDescriptor);
    closedir(dir);
    return 0;
}

