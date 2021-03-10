cmake_minimum_required(VERSION 3.17)
project(another_shell)

set(CMAKE_CXX_STANDARD 98)

add_executable(another_shell
		srcs/main.c
		includes/minishell.h
		srcs/utils/strlen.c
		srcs/utils/split.c
		srcs/utils/calloc.c
		srcs/utils/bzero.c
		srcs/utils/substr.c
		srcs/utils/strdup.c
		srcs/utils/strlcpy.c
		srcs/utils/strcmp.c
		srcs/builtins/env_export_utils.c
		srcs/utils/gnl.c srcs/utils/strcpy.c
		srcs/utils/is_shielded.c
		srcs/parsing/first_circle_of_parsing.c
		srcs/utils/is_special_symbol.c
		srcs/important/pregame_ritual.c
		srcs/parsing/request_separation.c
		srcs/builtins/env.c
		srcs/builtins/pwd.c
		srcs/utils/putchar.c
		srcs/utils/putendl.c
		srcs/utils/putstr.c
		srcs/important/signal_handling.c
		srcs/parsing/second_circle_of_parsing.c
		srcs/builtins/env.c
		srcs/builtins/echo.c
		srcs/builtins/cd.c
		srcs/builtins/export.c
		srcs/builtins/unset.c
		srcs/builtins/exit.c
		srcs/utils/strlcat.c
		srcs/parsing/filling_command_structure.c
		srcs/parsing/memory_cleaning.c
		srcs/utils/strncmp.c
		srcs/utils/str_to_lowercase.c
		srcs/utils/strjoin.c
		srcs/utils/skip_spaces.c
		srcs/utils/stop_buffering.c
		srcs/utils/iterators_to_zero.c
		srcs/builtins/cd_utils.c
		srcs/utils/is_alpha.c
		srcs/utils/atoi.c
		srcs/important/parsing_and_execution.c
		srcs/utils/itoa.c
		srcs/utils/change_last_process_code.c
		srcs/parsing/validation.c
		srcs/important/redirects.c
		srcs/utils/is_digit.c
		srcs/utils/is_valid_param_exp.c
		srcs/important/pipe_execution.c
		srcs/important/execution.c
		srcs/utils/pipeline_utils.c
		srcs/utils/request_validation_after_first_circle.c
		srcs/utils/validation_after_filling.c srcs/utils/realloc.c)
