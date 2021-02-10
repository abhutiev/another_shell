cmake_minimum_required(VERSION 3.17)
project(another_shell)

set(CMAKE_CXX_STANDARD 14)

add_executable(another_shell
        main.c
        includes/minishell.h
        srcs/utils/strlen.c
        srcs/utils/split.c
        srcs/utils/calloc.c
        srcs/utils/bzero.c
        srcs/utils/substr.c
        srcs/utils/strdup.c
        srcs/utils/strlcpy.c
        srcs/utils/strcmp.c
        srcs/builtins/work_with_environments.c
        srcs/utils/flags_shutting_up.c
        srcs/utils/gnl.c srcs/utils/strcpy.c
        srcs/utils/is_shielded.c
        srcs/parsing/first_circle_of_parsing.c
        srcs/utils/is_special_symbol.c srcs/pregame_ritual.c srcs/parsing/request_separation.c
        srcs/builtins/env.c srcs/builtins/pwd.c srcs/utils/putchar.c srcs/utils/putendl.c srcs/utils/putstr.c srcs/signal_handling.c srcs/parsing/second_circle_of_parsing.c srcs/builtins/env.c srcs/builtins/echo.c srcs/builtins/cd.c srcs/builtins/export.c srcs/builtins/unset.c srcs/builtins/exit.c)
