NAME			=	minishell

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror

DEBUG			=	-g3

VALGRIND		=	valgrind --leak-check=full --show-leak-kinds=all \
					--track-origins=yes -q --tool=memcheck \
					--suppressions=readline.supp \
					--track-fds=yes

PATH_SRC		=	./src/
PATH_OBJ		=	./obj/
PATH_LIBRARY	=	./library/
PATH_INCLUDES	=	./includes/

FILES			=	minishell.c

HEADERS			=	$(PATH_INCLUDES)minishell.h

OBJS			=	$(FILES:%.c=%.o)

MKDIR 			=	mkdir -p
RM				=	rm -rf

all:				makedir $(NAME)

$(NAME):			$(addprefix $(PATH_OBJ),$(OBJS))
					$(CC) $(addprefix $(PATH_OBJ),$(OBJS)) -o $(NAME)

$(PATH_OBJ)%.o: 	$(PATH_SRC)%.c $(HEADERS)
					$(CC) -c -o $@ $<

run:				$(NAME)
					./$(NAME)

valgrind:			$(NAME)
					$(VALGRIND) ./$(NAME)

makedir:			
					$(MKDIR) $(PATH_OBJ)

clean:
					$(RM) $(addprefix $(PATH_OBJ),$(OBJS))

fclean:				clean
					$(RM) $(NAME)

re:					fclean all

.PHONY:				all clean fclean re run 

