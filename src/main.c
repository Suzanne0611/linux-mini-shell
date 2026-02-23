#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#define MAX_INPUT 256
#define MAX_ARGS 64
#include "parser.h"
#include "executor.h"

/*處理 ctrl + C */
void sigint(int sig){
	(void)sig; //避免未使用參數警告
	printf("\nmysh> ");
	fflush(stdout); //立即把輸出送到終端
}

int main() {
	signal(SIGINT, sigint);
	char input[MAX_INPUT];
	char *argv[MAX_ARGS];
	char *left_argv[MAX_ARGS];
	char *right_argv[MAX_ARGS];
	
	while(1) {
		/*每一輪先把左右命令指標設成NULL(安全初值)*/
		char *left_cmd = NULL;
		char *right_cmd = NULL;
		int pipe_state;
		printf("mysh> ");
		
		if(!fgets(input, sizeof(input), stdin))
			break; 

		/* 自動尋找並刪除字尾的\n,替換成\0 */	
		input[strcspn(input, "\n")] = 0;
		
		if(strlen(input) == 0)
			continue;

		/*檢查是否為pipe指令*/
		pipe_state = split_pipeline(input, &left_cmd, &right_cmd);
		
		if(pipe_state == PIPE_UNSUPPORTED) {
			fprintf(stderr, "only one pipe is supported\n");
			continue;
		}

		/*pipe grammatical error*/
		if(pipe_state == PIPE_INVALID){
			fprintf(stderr, "invalid pipe command\n");
			continue;
		}

		/*解析左右參數後執行pipeline*/
		if(pipe_state == PIPE_OK){
			parse_input(left_cmd, left_argv);
			parse_input(right_cmd, right_argv);
			execute_pipeline(left_argv, right_argv);
			continue;
		}
		
		parse_input(input, argv);//pipe none
		
		/*保險：若切完沒有命令,直接下一輪*/		
		if(argv[0] == NULL)
			continue;

		/*結束shell*/
		if(strcmp(argv[0], "exit") == 0){
			printf("Bye!^^\n");
			break;
		}
		execute_command(argv);
	}
	return 0;
}
