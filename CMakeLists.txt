cmake_minimum_required(VERSION 3.17)
project(another_shell)

set(CMAKE_CXX_STANDARD 14)

add_executable(another_shell
        main.c
        interpreter.c
        minishell.h
        utils/strlen.c
        utils/split.c
        utils/calloc.c
        utils/bzero.c
        utils/substr.c
        utils/strdup.c
        utils/strlcpy.c
        utils/strcmp.c
        work_with_environments.c
        utils/flags_shutting_up.c
        utils/gnl.c utils/strcpy.c
        utils/is_shielded.c
        first_circle_of_parsing.c
        utils/is_special_symbol.c)
