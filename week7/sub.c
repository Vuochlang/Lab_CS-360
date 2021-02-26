#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <assert.h>

int main(int argc, char *argv[]){
	assert(argc % 2 == 1); // even number of command line arguments

	int fd[2];
	int reader, writer;
	char buffer[20];

	pipe(fd);
	reader = fd[0];
	writer = fd[1];

	if (fork()) {  // parent
	    close(reader);
	    while(read(0, buffer, 1)) {
	        write(writer, buffer, 1);
	    }
	    wait(0);  // wait for the child to finish
        close(writer);
	}
	else {
	    close(writer);
	    while(read(reader, buffer, 1)) {
	        for (int i = 1; i < argc; i += 2) {
	            if (buffer[0] == *argv[i])
	                buffer[0] = *argv[i + 1];
	        }
	        write(1, &buffer[0], 1);
	    }
	}

}