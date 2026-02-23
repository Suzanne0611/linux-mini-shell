#ifndef EXECUTOR_H
#define EXECUTOR_H

void execute_command(char **argv);
void execute_pipeline(char **left_argv, char **right_argv);

#endif
