#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "executor.h"
	
void execute_command(char **argv) {
	pid_t pid = fork();
		
	if(pid < 0){
		perror("fork failed");
		return;
	}
	if(pid == 0){ //chid
		/*將目前的child ps Image替換成argv[0]指定的可執行檔*/
		execvp(argv[0], argv);
		perror("execvp failed");
		_exit(1);
	}
	waitpid(pid, NULL, 0);
}

void execute_pipeline(char **left_argv, char **right_argv){
	int pipefd[2]; //pipefd[0]:read pipefd[1]:write
	pid_t left_pid;
	pid_t right_pid;
	
	if(pipe(pipefd) < 0) {
		perror("pipe failed");
		return;
	}

	left_pid = fork();
	if(left_pid < 0){
		perror("fork failed");
		close(pipefd[0]);
		close(pipefd[1]);
		return;
	}
	
	if(left_pid == 0){
		if(dup2(pipefd[1], STDOUT_FILENO) < 0){ //stdout > pipefd[1]
			perror("dup2 failed");
			_exit(1);
		}
		close(pipefd[0]);
		close(pipefd[1]);
		execvp(left_argv[0], left_argv);		
		perror("execvp failed");
		_exit(1);	
	}

	right_pid = fork();
	if(right_pid <	0){
		perror("fork failed");
		close(pipefd[0]);
		close(pipefd[1]);
		return;
	}
	
	if(right_pid == 0){
		if(dup2(pipefd[0], STDIN_FILENO) < 0){
			perror("dup2 failed");
			_exit(1);
		}
		close(pipefd[1]);
		close(pipefd[0]);
		execvp(right_argv[0], right_argv);
		perror("execvp failed");
		_exit(1);
	}
	
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, NULL, 0);
}


