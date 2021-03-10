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
				validation_after_filling.c \
				realloc.c )

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

OBJS	=	${SRC:.c=.o}

GREEN	=	\033[0;32m

CYAN	=	\033[0;36m

MAGENTA	=	\033[0;35m

LGREEN	=	\033[1;32m

LYELLOW	=	\033[1;33m

LRED	=	\033[1;31m

LBLUE	=	\033[1;34m

WHITE	=	\033[1;39m

all: ${NAME}

${NAME}: ${SRC} ${INC} ${OBJS}
	@${CC} ${CFLAGS} -I ${INCDIR} ${OBJS} -o ${NAME}
	@echo "${CYAN}Our shell is ready to use${WHITE}"

launch:
	@./${NAME}

%.o: %.c
	@${CC} ${CFLAGS} -I ${INCDIR} -c $< -o $@
	@echo "${MAGENTA}Object file: ${LYELLOW}$@ ${GREEN}successfully compiled${WHITE}"

clean:
	@rm ${OBJS}
	@echo "${LRED}Object files successfully deleted${WHITE}"

fclean: clean
	@rm ${NAME}

re: fclean all
