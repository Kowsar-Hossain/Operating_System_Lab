#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main(){
	int fd[2];

	pid_t pid;
	char buffer[100];

	pid=fork();
	if(pipe(fd)==-1){
		perror("Pipe Failed");
		return 1;
	}
	if(pid<0){
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}
	else if(pid>0){
		close(fd[0]); // Close read end
        char message[] = "Hello from Parent!";
        write(fd[1], message, strlen(message) + 1); // Write to pipe
        close(fd[1]); // Close write end

		

		//printf("Child process:PID=%d\n",getpid());
	}
	else{
	close(fd[1]); // Close write end
        read(fd[0], buffer, sizeof(buffer)); // Read from pipe
        printf("Child received: %s\n", buffer);
        close(fd[0]); // Close read end


            

		//printf("Parent process: ParentPid=%d\n, Child pid=%d\n",getpid(),pid);


	
	}
	return 0;
}
