NAME	=	minishell

CC		=	gcc

CFLAGS	=

SRCDIR	=	srcs/

PARSINGDIR	=	parsing/

PARSINGSRC	=	$(addprefix ${PARSINGDIR}, \
				second_circle_of_parsing.c \
				filling_command_structure.c \
				memory_cleaning.c \
				request_separation.c \
				first_circle_of_parsing.c)

UTILSDIR    =   utils/

UTILSSRC    =   $(addprefix ${UTILSDIR}, \
				strlen.c \
				split.c \
				calloc.c \
				bzero.c \
				substr.c \
				strdup.c \
				strlcpy.c \
				strcmp.c \
				gnl.c \
				strcpy.c \
				is_shielded.c \
				is_special_symbol.c \
				putchar.c \
				putendl.c \
				putstr.c \
				make_way_to_binary.c \
				strlcat.c \
				str_to_lowercase.c \
				strncmp.c)

BUILTINSDIR =   builtins/

BUILTINSSRC =	$(addprefix ${BUILTINSDIR}, \
				cd.c \
				echo.c \
				env.c \
				exit.c \
				export.c \
				pwd.c \
				unset.c \
				work_with_environments.c)

SRC		=	$(addprefix ${SRCDIR}, ${BUILTINSSRC} \
				${PARSINGSRC} \
				${UTILSSRC})

INCDIR	=	includes/

INC		=	minishell.h

all: ${NAME}

${NAME}:
	${CC} ${CFLAGS} -I ${INCDIR} ${SRC} srcs/pregame_ritual.c srcs/signal_handling.c main.c -o ${NAME}

fclean:
	rm ${NAME}

re: fclean all