# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/04 19:44:22 by roaraujo          #+#    #+#              #
#    Updated: 2022/04/28 23:32:52 by roaraujo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# PATH VARIABLES
HEADERS_PATH = ../../includes/
SRCS_PATH = ./srcs/
OBJS_PATH = ./objs/
LIBS_PATH = ../

# COMPILATION
CC = gcc -g3
FLAGS = -Wall -Wextra -Werror

# BASH COMMANDS
RM = rm -f
MKDIR = mkdir -p

# FILES
LIBNAME = libft.a
SRC_FILES =	ft_append_char.c \
			ft_atoi.c \
			ft_atoli.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_close_pipe_fds.c \
			ft_free_arr.c \
			ft_free_ptr.c \
			ft_get_next_line.c \
			ft_get_next_line_utils.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isnumeric_s.c \
			ft_isprint.c \
			ft_is_blankspace.c \
			ft_itoa.c \
			ft_lst_add_back.c \
			ft_lst_add_front.c \
			ft_lst_clear.c \
			ft_lst_del_one.c \
			ft_lst_iter.c \
			ft_lst_last.c \
			ft_lst_new.c \
			ft_lst_remove_node.c \
			ft_lst_size.c \
			ft_lst_map.c \
			ft_memccpy.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
			ft_split.c \
			ft_strchr.c \
			ft_strdup.c \
			ft_strjoin.c \
			ft_strjoin_3.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strmapi.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_uitoa.c \
			ft_uitohex.c \
			ft_ulitohex.c \
			ft_free_pipe_arr.c \
			ft_make_pipes.c
			
SOURCES = $(addprefix $(SRCS_PATH), $(SRC_FILES))
OBJ_FILES = $(patsubst %.c, %.o, $(SRC_FILES))
OBJECTS = $(addprefix $(OBJS_PATH), $(OBJ_FILES))

# TARGETS
all: prep $(LIBNAME)

prep:
	@$(MKDIR) $(SRCS_PATH) $(OBJS_PATH)

$(LIBNAME): $(OBJECTS)
	@ar -rcs $(LIBS_PATH)$(LIBNAME) $(OBJECTS)

$(OBJS_PATH)%.o : $(SRCS_PATH)%.c $(HEADERS_PATH)*.h
	@$(CC) $(FLAGS) -c -I $(HEADERS_PATH) $< -o $@

clean:
	@$(RM) $(OBJECTS)

fclean: clean
	@$(RM) $(LIBS_PATH)$(LIBNAME)

re: fclean all

.PHONY:	all clean fclean re