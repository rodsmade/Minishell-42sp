PATH_SRC		=	./src/
PATH_OBJ		=	./obj/
PATH_LIBRARY	=	./libs/
PATH_INCLUDES	=	./includes/

NAME			=	minishell

CC				=	gcc $(CFLAGS)

CFLAGS			=	-Wall -Wextra -Werror -I $(PATH_INCLUDES) $(DEBUG)

LIBS			=	-lreadline -L $(PATH_LIBRARY) -lft

DEBUG			=	-g3

VALGRIND		=	valgrind --leak-check=full \
					--show-leak-kinds=all \
					--track-origins=yes \
					--quiet \
					--tool=memcheck \
					--suppressions=readline.supp \
					--keep-debuginfo=yes \
					--track-fds=yes

FILES			=	builtin_cd.c \
					builtin_echo.c \
					builtin_exit.c \
					builtin_env.c \
					builtin_pwd.c \
					builtin_unset.c \
					builtin_var_assignment.c \
					executor.c \
					exit_routines_2.c \
					exit_routines.c \
					hashtable.c \
					init_routines.c \
					lexer.c \
					minishell.c \
					parser.c \
					utils_hashtable.c \
					utils_lexer_mock.c \
					utils_lexer.c \
					utils_parser_2.c \
					utils_parser.c \
					utils_test.c \
					builtin-export.c \
					utils_export.c

HEADERS			=	$(PATH_INCLUDES)minishell.h \
					$(PATH_INCLUDES)libft.h

OBJS			=	$(FILES:%.c=%.o)

MKDIR 			=	mkdir -p
RM				=	rm -rf

all:				libft makedir $(NAME)

# -> compiles libft all over
libft:
					cd $(PATH_LIBRARY)libft && $(MAKE)

makedir:			
					$(MKDIR) $(PATH_OBJ)

$(NAME):			$(addprefix $(PATH_OBJ),$(OBJS))
					$(CC) $(addprefix $(PATH_OBJ),$(OBJS)) -o $(NAME) $(LIBS)

$(PATH_OBJ)%.o: 	$(PATH_SRC)%.c $(HEADERS)
					$(CC) -c -o $@ $< $(LIBS)

run:				$(NAME)
					./$(NAME)

valgrind:			$(NAME)
					$(VALGRIND) ./$(NAME)

clean:
					$(RM) $(addprefix $(PATH_OBJ),$(OBJS))

fclean:				clean
					$(RM) $(NAME)

re:					fclean all

.PHONY:				all clean fclean re run 

