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
				atoi.c \
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
				strlcat.c \
				str_to_lowercase.c \
				strncmp.c \
				iterators_to_zero.c \
				skip_spaces.c \
				stop_buffering.c \
				strjoin.c )

BUILTINSDIR =   builtins/

BUILTINSSRC =	$(addprefix ${BUILTINSDIR}, \
				cd.c \
				cd_utils.c \
				echo.c \
				env.c \
				exit.c \
				export.c \
				pwd.c \
				unset.c \
				env_export_utils.c)

SRC		=	$(addprefix ${SRCDIR}, ${BUILTINSSRC} \
				${PARSINGSRC} \
				${UTILSSRC})

INCDIR	=	includes/

INC		=	minishell.h

all: ${NAME}

${NAME}:
	${CC} ${CFLAGS} -I ${INCDIR} ${SRC} srcs/important/pregame_ritual.c srcs/important/signal_handling.c main.c -o ${NAME}

launch:
	./${NAME}

fclean:
	rm ${NAME}

re:
	fclean
	all
	launch