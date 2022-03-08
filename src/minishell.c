/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 21:30:44 by roaraujo          #+#    #+#             */
/*   Updated: 2022/03/08 14:13:18 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

# define	TABLE_SIZE	50

typedef struct s_env_var
{
	char				*name;
	char				*content;
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

void	*key_value_to_t_env_var(char **key_value)
{
	t_env_var	element;

	element.name = ft_strdup(key_value[0]);
	element.content = ft_strdup(key_value[1]);
	return ((void *) element);
}

void	insert_in_hashtable(char *env_var, t_list *(*hashtable)[TABLE_SIZE])
{
	//Função que vai inserir dentro da hash
	//Criar função hash
	int		index;
	char	**key_value;

	key_value = ft_split(env_var, '=');
	index = hash_string(key_value[0]);
	
	ft_lstadd_front(&((*hashtable)[index]), ft_lstnew(key_value_to_t_env_var(key_value)));
	ft_free_arr((void *)&key_value);
	return ;
}

void	get_env_variables(char **envp)
{
	int			i;
	t_list		*hashtable[TABLE_SIZE];

	i = -1;
	init_hashtable(&hashtable);
	print_hashtable(&hashtable);
	// while (envp[++i])
	while (i < 1)
	{
		insert_in_hashtable(envp[i], &hashtable);
	}
	printf("nome: %s, conteúdo: %s\n", ((t_env_var) hashtable[0]->content).name, ((t_env_var) hashtable[0]->content).content);
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
