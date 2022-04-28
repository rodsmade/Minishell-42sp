# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/28 22:21:35 by roaraujo          #+#    #+#              #
#    Updated: 2022/04/28 23:02:01 by roaraujo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ################################################################### VARIABLES
# BINARY NAME
NAME			=	minishell

# BASH COMMANDS
MKDIR 			=	mkdir -p
RM				=	rm -rf

# COMPILATION
CC				=	gcc $(CFLAGS)
CFLAGS			=	-Wall -Wextra -Werror -I $(PATH_INCLUDES) $(DEBUG)
LIBS			=	-lreadline -L $(PATH_LIBRARY) -lft
DEBUG			=	-g3
VALGRIND		=	valgrind \
					--leak-check=full \
					--show-leak-kinds=all \
					--track-origins=yes \
					--quiet \
					--tool=memcheck \
					--suppressions=readline.supp \
					--keep-debuginfo=yes \
					--track-fds=yes \
					--trace-children=yes

# HEADERS
HEADERS			=	$(PATH_INCLUDES)minishell.h \
					$(PATH_INCLUDES)libft.h \
					$(PATH_INCLUDES)ansi_color_codes.h

# PATHS
PATH_SRC		=	./src/
PATH_OBJ		=	obj/
PATH_LIBRARY	=	./libs/
PATH_INCLUDES	=	./includes/
PATH_BUILTINS	=	builtins/
PATH_EXECUTOR	=	executor/
PATH_EXIT		=	exit_routines/
PATH_EXPANSOR	=	expansor/
PATH_HASHTABLE	=	hashtable/
PATH_INIT		=	init_routines/
PATH_LEXER		=	lexer/
PATH_PARSER		=	parser/
PATH_PROMPT		=	prompt/
PATH_REDIRECTS	=	redirections/
PATH_SIGNALS	=	signals/
PATH_TESTS		=	test_utils/

# FILES
SOURCES			=	minishell.c \
					$(PATH_BUILTINS)builtin_cd.c \
					$(PATH_BUILTINS)builtin_echo.c \
					$(PATH_BUILTINS)builtin_exit.c \
					$(PATH_BUILTINS)builtin_env.c \
					$(PATH_BUILTINS)builtin_export.c \
					$(PATH_BUILTINS)builtin_pwd.c \
					$(PATH_BUILTINS)builtin_unset.c \
					$(PATH_EXECUTOR)executor.c \
					$(PATH_EXIT)exit_routines_2.c \
					$(PATH_EXIT)exit_routines_3.c \
					$(PATH_EXIT)exit_routines.c \
					$(PATH_EXPANSOR)expansor.c \
					$(PATH_HASHTABLE)hashtable.c \
					$(init_routines)init_routines.c \
					$(PATH_LEXER)lexer.c \
					$(PATH_PARSER)parser.c \
					$(PATH_EXECUTOR)command_table.c \
					$(PATH_PROMPT)prompt.c \
					$(PATH_SIGNALS)signal_handler.c \
					$(PATH_HASHTABLE)utils_env_vars.c \
					$(PATH_EXECUTOR)utils_executor_2.c \
					$(PATH_EXECUTOR)utils_executor_3.c \
					$(PATH_EXECUTOR)utils_executor_4.c \
					$(PATH_EXECUTOR)utils_executor.c \
					$(PATH_EXPANSOR)utils_expansor_2.c \
					$(PATH_EXPANSOR)utils_expansor.c \
					$(PATH_BUILTINS)utils_export_2.c \
					$(PATH_BUILTINS)utils_export.c \
					$(PATH_REDIRECTS)utils_file_check.c \
					$(PATH_HASHTABLE)utils_hashtable_2.c \
					$(PATH_HASHTABLE)utils_hashtable.c \
					$(PATH_REDIRECTS)utils_heredoc_2.c \
					$(PATH_REDIRECTS)utils_heredoc.c \
					$(PATH_LEXER)utils_lexer.c \
					$(PATH_PARSER)utils_parser_2.c \
					$(PATH_PARSER)utils_parser.c \
					$(PATH_REDIRECTS)utils_redirections.c \
					$(PATH_TESTS)utils_test.c
OBJS			=	$(SOURCES:%.c=%.o)


# #################################################################### TARGETS
all:				libft makedir $(NAME)

# -> compiles libft all over
libft:
					cd $(PATH_LIBRARY)libft && $(MAKE)

makedir:			
					$(MKDIR) $(PATH_OBJ) $(PATH_OBJ)$(PATH_BUILTINS) $(PATH_OBJ)$(PATH_EXECUTOR) $(PATH_OBJ)$(PATH_EXIT) $(PATH_OBJ)$(PATH_EXPANSOR) $(PATH_OBJ)$(PATH_HASHTABLE) $(PATH_OBJ)$(PATH_INIT) $(PATH_OBJ)$(PATH_LEXER) $(PATH_OBJ)$(PATH_PARSER) $(PATH_OBJ)$(PATH_PROMPT) $(PATH_OBJ)$(PATH_REDIRECTS) $(PATH_OBJ)$(PATH_SIGNALS) $(PATH_OBJ)$(PATH_TESTS)

$(NAME):			$(addprefix $(PATH_OBJ),$(OBJS))
					@$(CC) $(addprefix $(PATH_OBJ),$(OBJS)) -o $(NAME) $(LIBS)
					@echo "\n\033[0;32mCompilation done! No errors found"
					@echo -n "\033[0m"					

$(PATH_OBJ)%.o: 	$(PATH_SRC)%.c $(HEADERS)
					@printf "\033[0;33mGenerating object files %-33.33s\r" $@
					@$(CC) -c -o $@ $< $(LIBS)

run:				all
					./$(NAME)

valgrind:			all
					$(VALGRIND) ./$(NAME)

clean:
					@echo "\033[0;33mCleaning up object files ..."
					@$(RM) $(addprefix $(PATH_OBJ),$(OBJS))
					@echo "\033[0;32mObject files cleaned up!"
					@echo -n "\033[0m"

fclean:				clean
					@echo "\033[0;33mCleaning up binary files ..."
					@$(RM) $(NAME)
					@echo "\033[0;32mBinary files cleaned up!"
					@echo -n "\033[0m"

re:					fclean all

.PHONY:				all clean fclean re run valgrind
