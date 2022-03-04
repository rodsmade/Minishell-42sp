NAME			= minishell

CC				= gcc

CFLAGS			= -Wall -Wextra -Werror

DEBUG			= -g3

PATH_SRC		= ./src/
PATH_OBJ		= ./obj/
PATH_LIBRARY	= ./library/
PATH_INCLUDES	= ./includes/

FILES			=	${PATH_SRC}minishell.c

HEADERS			=	${PATH_INCLUDES}minishell.h

OBJS			=	${FILES:%.c=%.o}

MKDIR 			= 	mkdir -p
RM				=	rm -rf

all:				makedir ${NAME}

${NAME}:			${OBJS}
					${CC} ${OBJS} -o ${NAME}

%.o: %.c ${HEADERS}
					${CC} -c -o $@ $<

run:				${NAME}
					./${NAME}

makedir:			
					${MKDIR} ${PATH_OBJ}

clean:
					${RM} ${OBJS}

fclean:				clean
					${RM} ${NAME}

re:					fclean all

.PHONY:				all clean fclean re

