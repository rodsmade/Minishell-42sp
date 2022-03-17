/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 11:56:49 by roaraujo          #+#    #+#             */
/*   Updated: 2022/03/16 18:46:31 by adrianofaus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	hash_string(char *str)
{
	int	hash;
	int	i;

	i = -1;
	hash = 0;
	while (str[++i])
	{
		hash += str[i];
		hash *= str[i];
		hash = hash % TABLE_SIZE;
	}
	return (hash);
}

static t_env_var	*key_value_to_t_env_var(char **key_value, int is_env_var)
{
	t_env_var	*element;

	element = (t_env_var *)malloc(sizeof(t_env_var));
	element->name = ft_strdup(key_value[0]);
	element->value = ft_strdup(key_value[1]);
	element->is_env_var = is_env_var;
	return (element);
}

void	insert_in_hashtable(char *string, int is_env_var
	, t_list *(*hashtable)[TABLE_SIZE])
{
	int			index;
	char		**key_value;
	t_env_var	*key_value_alloc;

	key_value = ft_split(string, '=');
	index = hash_string(key_value[0]);
	key_value_alloc = key_value_to_t_env_var(key_value, is_env_var);
	ft_lstadd_back(&((*hashtable)[index]), ft_lstnew((void *)key_value_alloc));
	ft_free_arr((void *)&key_value);
	return ;
}
