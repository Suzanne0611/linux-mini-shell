#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#define MAX_INPUT 256
#define MAX_ARGS 64
#include "parser.h"

/*處理 ctrl + C */
void sigint(int sig){
	printf("\nmysh> ");
	fflush(stdout);
}

int main() {
	signal(SIGINT, sigint);
	char input[MAX_INPUT];
	char *argv[MAX_ARGS];	
	while(1) {
		printf("mysh> ");
		
		if(!fgets(input, sizeof(input), stdin))
			break; 

		/* 自動尋找並刪除字串末尾的換行符號\n,替換成字串結束符號\0 */	
		input[strcspn(input, "\n")] = 0;
		
		if(strlen(input) == 0)
			continue;

		parse_input(input, argv);

		/*結束shell*/
		if(strcmp(argv[0], "exit") == 0){
			printf("Bye!^^\n");
			break;
		}

		/*fork*/
		pid_t pid = fork();
		
		if(pid < 0){
			perror("fork failed");
			continue;
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
	return 0;
}
