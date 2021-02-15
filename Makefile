NAME    =   minishell

CC      =   gcc

CFLAGS  =   -Wall -Wextra -Werror

SRCDIR  =   srcs/

PARSINGDIR  = $(addprefix $SRCDIR, parsing/)

PARSINGSRC  =   $(addprefix $PARSINGDIR, \
                second_circle_of_parsing.c \
                filling_command_structure.c \
                memory_cleaning.c \
                request_separation.c \
                first_circle_of_parsing.c)

UTILSDIR    =   utils/

UTILSSRC    =   $(addprefix $UTILSDIR, \
                strlen.c \
                split.c \
                calloc.c \
                bzero.c \
                substr.c \
                strdup.c \
                strlcpy.c \
                strcmp.c \
                gnl.c srcs/utils/strcpy.c \
                is_shielded.c \
                is_special_symbol.c \
                putchar.c \
                putendl.c \
                putstr.c \
                make_way_to_binary.c \
                strlcat.c)

BUILTINSDIR =   builtins/

BUILTINSSRC =   $(addprefix $BUILTINSDIR, \
                cd.c \
                echo.c \
                env.c \
                exit.c \
                export.c \
                pwd.c \
                unset.c \
                work_with_environments.c)

INCDIR  =   includes/

INC     =   minishell.h

all: $NAME