NAME	=	minishell

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

SRCDIR	=	srcs/

PARSINGDIR	=	parsing/

PARSINGSRC	=	$(addprefix ${PARSINGDIR}, \
				second_circle_of_parsing.c \
				filling_command_structure.c \
				memory_cleaning.c \
				validation.c \
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
				is_valid_param_exp.c \
				is_digit.c \
				is_alpha.c \
				putchar.c \
				putendl.c \
				putstr.c \
				strlcat.c \
				str_to_lowercase.c \
				strncmp.c \
				iterators_to_zero.c \
				skip_spaces.c \
				stop_buffering.c \
				strjoin.c \
				change_last_process_code.c \
				itoa.c \
				request_validation_after_first_circle.c \
				pipeline_utils.c \
				env_for_minishell.c )

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

IMPORTANTDIR =   important/

IMPORTANTSRC =	$(addprefix ${IMPORTANTDIR}, \
				pregame_ritual.c \
				signal_handling.c \
				parsing_and_execution.c \
				redirects.c \
				pipe_execution.c \
				execution.c)

SRC		=	$(addprefix ${SRCDIR}, ${BUILTINSSRC} \
				${PARSINGSRC} \
				${UTILSSRC} \
				${IMPORTANTSRC} \
				main.c)

INCDIR	=	includes/

INC		=	$(addprefix ${INCDIR}, minishell.h)

all: ${NAME}

${NAME}: ${SRC} ${INC}
	${CC} ${CFLAGS} -I ${INCDIR} ${SRC} -o ${NAME}

launch:
	./${NAME}

fclean:
	rm ${NAME}

re:
	make fclean
	make all
	make launch
