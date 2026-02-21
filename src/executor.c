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
			if(execvp(argv[0], argv) < 0)
				perror("execvp failed");
			exit(1);
		}
		else { //parent
			waitpid(pid, NULL, 0);
		}
}
