/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 21:30:44 by roaraujo          #+#    #+#             */
/*   Updated: 2022/03/08 18:39:39 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

# define	TABLE_SIZE	50

typedef struct s_env_var
{
	char				*name;
	char				*value;
}				t_env_var;

void	repl(void)
{
	char	*line_read;

	line_read = NULL;
	while (1)
	{
		line_read = readline("Type yr command (type \'quit\' to exit): ");
		add_history(line_read);
		if (ft_strncmp(line_read, "quit", 5) == 0)
			break ;
		if (line_read)
			ft_free_ptr((void *)&line_read);
	}
	ft_free_ptr((void *)&line_read);
	rl_clear_history();
	return ;
}

void	init_hashtable(t_list *(*hashtable)[TABLE_SIZE])
{
	int	i;

	i = -1;
	while (++i < TABLE_SIZE)
	{
		(*hashtable)[i] = NULL;
	}
	return ;
}

void	free_env_var(void *element)
{
	ft_free_ptr((void *)&(((t_env_var *) element)->name));
	ft_free_ptr((void *)&(((t_env_var *) element)->value));
	ft_free_ptr((void *)&element);
	return ;
}

void	free_hashtable(t_list *(*hashtable)[TABLE_SIZE])
{
	int	i;

	i = -1;
	while (++i < TABLE_SIZE)
		ft_lstclear(&(*hashtable)[i], free_env_var);
	return ;
}

void	print_hashtable(t_list *(*hashtable)[TABLE_SIZE])
{
	int	i;

	i = -1;
	while (++i < TABLE_SIZE)
	{
		printf(">: Position %d - %p\n", i, (*hashtable)[i]);
	}
	return ;
}

int		hash_string(char *str)
{
	int	hash;
	// todo
	(void) str;
	hash = 0;
	return (hash);
}

t_env_var	*key_value_to_t_env_var(char **key_value)
{
	t_env_var	*element;

	element = (t_env_var *)malloc(sizeof(t_env_var));
	element->name = ft_strdup(key_value[0]);
	element->value = ft_strdup(key_value[1]);
	return (element);
}

void	insert_in_hashtable(char *env_var, t_list *(*hashtable)[TABLE_SIZE])
{
	// Função que vai inserir dentro da hash
	// Criar função hash
	int			index;
	char		**key_value;
	t_env_var	*key_value_alloc;

	key_value = ft_split(env_var, '=');
	index = hash_string(key_value[0]);
	key_value_alloc = key_value_to_t_env_var(key_value);
	ft_lstadd_front(&((*hashtable)[index]), ft_lstnew((void *)key_value_alloc));
	// free(key_value_alloc);
	ft_free_arr((void *)&key_value);
	return ;
}

void	get_env_variables(char **envp)
{
	int			i;
	t_list		*hashtable[TABLE_SIZE];

	i = -1;
	init_hashtable(&hashtable);
	// print_hashtable(&hashtable);
	while (++i < 1)
	{
		insert_in_hashtable(envp[i], &hashtable);
	}
	printf("nome: %s\n", ((t_env_var *)(hashtable[0]->content))->name);
	free_hashtable(&hashtable);
	return ;
}

int	main(int argc, char *argv[], char **envp)
{
	(void)argv;
	(void)envp;
	if (argc != 1)
		return (1);
	write(1, "Hello World !\n", 14);
	get_env_variables(envp);
	repl();
	close(0);
	close(1);
	close(2);
	return (0);
}
