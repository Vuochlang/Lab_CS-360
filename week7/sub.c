/***********************************************************************
name:
	assignment4 -- acts as a pipe using ":" to seperate programs.
description:	
	See CS 360 Processes and Exec/Pipes lecture for helpful tips.
***********************************************************************/

/* Includes and definitions */
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <assert.h>

/**********************************************************************
./assignment4 <arg1> : <arg2>

    Where: <arg1> and <arg2> are optional parameters that specify the programs
    to be run. If <arg1> is specified but <arg2> is not, then <arg1> should be
    run as though there was not a colon. Same for if <arg2> is specified but
    <arg1> is not.
**********************************************************************/

int main(int argc, char *argv[]){
	assert(argc % 2 == 1);  // even number of argv

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
//	    close(writer);
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