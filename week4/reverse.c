#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

void readAndPrint(char *fileName) {

    int fd = open(fileName, O_RDWR);
    if (fd < 0) {
        write(2, strerror(errno), strlen(strerror(errno)));
        return;
    }

    int lastByte = lseek(fd, 0, SEEK_END); // get the total bytes of the file
    if (lastByte < 0) {
        write(2, strerror(errno), strlen(strerror(errno)));
        close(fd);
        return;
    }
    
    char buffer[1];
    int readResult = read(fd, buffer, 1);
    if (readResult < 0) {
        write(2, strerror(errno), strlen(strerror(errno)));
        return;
    }

    while (lastByte > 0) { // keep reading backward
	    --lastByte;
	    write(1, buffer, 1);
        lseek(fd, lastByte, SEEK_SET);

        readResult = read(fd, buffer, 1);
        if (readResult < 0) {
            write(2, strerror(errno), strlen(strerror(errno)));
            return;
        }
    }
    write(1, buffer, 1);
    write(1, "\n", 1);
    close(fd);
}

int main (int argc, char *argv[]) {
    if (argc == 2) {
        readAndPrint(argv[1]);
    }
    else {     
        fprintf(stderr, "Usage: ./main <textFileName>\n");
        return -1;
    }
    return 0;
}
