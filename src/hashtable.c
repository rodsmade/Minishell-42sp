/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 11:56:49 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/11 16:36:21 by roaraujo         ###   ########.fr       */
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
	element->key = ft_strdup(key_value[0]);
	if (!ft_strncmp(key_value[0], "OLDPWD", 7))
		element->value = NULL;
	else
		element->value = ft_strdup(key_value[1]);
	element->is_env_var = is_env_var;
	return (element);
}

void	insert_in_hashtable(char *string, int is_env_var
	, t_list *(*hashtable)[TABLE_SIZE])
{
	int			index;
	char		**key_value;
	t_env_var	*env_var;

	key_value = split_key_and_value(string);
	env_var = key_value_to_t_env_var(key_value, is_env_var);
	index = hash_string(key_value[0]);
	ft_lst_add_back(&((*hashtable)[index]), ft_lst_new((void *)env_var));
	ft_free_arr((void *)&key_value);
	return ;
}

void	insert_or_update_hashtable(char *string, int is_env_var
	, t_list *(*hashtable)[TABLE_SIZE])
{
	char		**key_value;

	key_value = split_key_and_value(string);
	if (find_node_in_hashtable(key_value[0]) == NULL)
		insert_in_hashtable(string, is_env_var, hashtable);
	else
		update_hashtable(key_value[0], key_value[1], is_env_var);
	ft_free_arr((void *)&key_value);
}
