PATH_SRC		=	./src/
PATH_OBJ		=	./obj/
PATH_LIBRARY	=	./libs/
PATH_INCLUDES	=	./includes/

NAME			=	minishell

CC				=	gcc $(CFLAGS)

CFLAGS			=	-Wall -Wextra -Werror -I $(PATH_INCLUDES) $(DEBUG)

LIBS			=	-lreadline -L $(PATH_LIBRARY) -lft

DEBUG			=	-g3

VALGRIND		=	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --quiet --tool=memcheck --suppressions=readline.supp --keep-debuginfo=yes --track-fds=yes

FILES			=	builtin_cd.c \
					builtin_echo.c \
					builtin_exit.c \
					builtin_env.c \
					builtin_export.c \
					builtin_pwd.c \
					builtin_unset.c \
					builtin_var_assignment.c \
					executor.c \
					exit_routines_2.c \
					exit_routines_3.c \
					exit_routines.c \
					expansor.c \
					hashtable.c \
					init_routines.c \
					lexer.c \
					minishell.c \
					parser.c \
					command_table.c \
					prompt.c \
					signal_handler.c \
					utils_env_vars.c \
					utils_executor_2.c \
					utils_executor_3.c \
					utils_executor.c \
					utils_expansor_2.c \
					utils_expansor.c \
					utils_export_2.c \
					utils_export.c \
					utils_file_check.c \
					utils_hashtable_2.c \
					utils_hashtable.c \
					utils_heredoc_2.c \
					utils_heredoc.c \
					utils_lexer.c \
					utils_parser_2.c \
					utils_parser.c \
					utils_redirections.c \
					utils_test.c

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
					@$(CC) $(addprefix $(PATH_OBJ),$(OBJS)) -o $(NAME) $(LIBS)
					@echo "\n\033[0;32mDone!"
					@echo -n "\033[0m"					

$(PATH_OBJ)%.o: 	$(PATH_SRC)%.c $(HEADERS)
					@printf "\033[0;33mGenerating libft objects... %-33.33s\r" $@
					@$(CC) -c -o $@ $< $(LIBS)

run:				all
					./$(NAME)

valgrind:			all
					$(VALGRIND) ./$(NAME)

clean:
					@$(RM) $(addprefix $(PATH_OBJ),$(OBJS))
					@echo "\033[0;32mObj. files cleaned!"
					@echo -n "\033[0m"

fclean:				clean
					@$(RM) $(NAME)
					@echo "\033[0;32mBinary Cleaned!"
					@echo -n "\033[0m"

re:					fclean all

.PHONY:				all clean fclean re run 

