#ifndef PARSER_H
#define PARSER_H

#define PIPE_NONE 0
#define PIPE_OK 1
#define PIPE_INVALID -1
#define PIPE_UNSUPPORTED -2

void parse_input(char *input, char **argv);
/*輸入字串 + 兩個輸出指標*/
int split_pipeline(char *input, char **left_cmd, char **right_cmd);

#endif

