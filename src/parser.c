#include <ctype.h>
#include <string.h>
#include "parser.h"
#define MAX_ARGS 64

/*處理前後空白處*/
static char *trim_spaces(char *s){
	char *end;
	/*處理開頭空白,不是空白就停止*/
	while(*s != '\0' && isspace((unsigned char)*s))
		s++;

	/*空字串保護*/
	if(*s == '\0')
		return s;

	/*處理結尾*/
	end = s + strlen(s) - 1;
	while(end > s && isspace((unsigned char)*end)){
		*end = '\0'; //把空白變結束符號
		end--; //往回走
	}
	return s;
}

/* 切割字串存入argv */
void parse_input(char *input, char **argv) {
	int argc = 0;
	char *token = strtok(input, " \t\n");//第一次呼叫告訴系統切割input 
	
	while(token != NULL && argc < MAX_ARGS - 1) {
		argv[argc++] = token;
		token = strtok(NULL, " \t\n");//持續切割直到指向NULL
	}
	argv[argc] = NULL;//陣列要以NULL收尾
}

/*pipe左右拆解成兩個獨立的指令*/
int split_pipeline(char *input, char **left_cmd, char **right_cmd) {
	char *pipe_pos = strchr(input, '|'); //在字串中搜尋第一個出現的'|'
	char *second_pipe;
	
	/*ordinary instructions*/
	if(pipe_pos == NULL)
		return PIPE_NONE; //0
 	
	/*check for miltiple pipelines*/
	second_pipe = strchr(pipe_pos + 1, '|');
	if(second_pipe != NULL)
		return PIPE_UNSUPPORTED; //-2
	
	*pipe_pos = '\0'; //將｜位置替換成\0
	/*呼叫trim_spaces,把指令前後多餘的空格刪掉*/
	*left_cmd = trim_spaces(input);
	*right_cmd = trim_spaces(pipe_pos + 1);

	if(**left_cmd == '\0' || **right_cmd == '\0')
		return PIPE_INVALID; //-1
	
	return PIPE_OK;
}


















