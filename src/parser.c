#include <string.h>
#define MAX_ARGS 64

/* 切割字串存入argv */
void parse_input(char *input, char **argv) {
	int argc = 0;
	char *token = strtok(input, " ");//告訴系統切割input 
	
	while(token != NULL && argc < MAX_ARGS - 1) {
		argv[argc++] = token;
		token = strtok(NULL, " ");//持續切割直到指向NULL
	}
	argv[argc] = NULL;//陣列要以NULL收尾
}
