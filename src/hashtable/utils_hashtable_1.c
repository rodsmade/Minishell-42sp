/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_hashtable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 20:14:20 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/04/08 18:47:52 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_hashtable(char *key, char *new_value, int new_env_var)
{
	int		index;
	int		len;
	t_list	*tmp;

	len = ft_strlen(key);
	index = hash_string(key);
	tmp = g_tudao.hashtable[index];
	while (g_tudao.hashtable[index] != NULL)
	{
		if (ft_strncmp(((t_env_var *) \
		g_tudao.hashtable[index]->content)->key, key, len) == 0)
		{
			ft_free_ptr((void *)&(((t_env_var *) \
			g_tudao.hashtable[index]->content)->value));
			((t_env_var *) \
			g_tudao.hashtable[index]->content)->value = ft_strdup(new_value);
			((t_env_var *) \
			g_tudao.hashtable[index]->content)->is_env_var = new_env_var;
			break ;
		}
		g_tudao.hashtable[index] = g_tudao.hashtable[index]->next;
	}
	g_tudao.hashtable[index] = tmp;
}

char	*read_hashtable(t_list *head, char *key)
{
	t_list	*pivot;
	int		len;

	len = ft_strlen(key);
	pivot = head;
	while (pivot != NULL)
	{
		if (ft_strncmp(((t_env_var *)pivot->content)->key, key, len) == 0)
			return (((t_env_var *)pivot->content)->value);
		pivot = pivot->next;
	}
	return (NULL);
}

t_list	*find_node_in_hashtable(char *var_name)
{
	t_list	*pivot;
	char	*pivot_var_name;

	pivot = g_tudao.hashtable[hash_string(var_name)];
	while (pivot)
	{
		pivot_var_name = (char *)((t_env_var *) pivot->content)->key;
		if (ft_strncmp(pivot_var_name, var_name, ft_strlen(var_name) + 1) == 0)
			return (pivot);
		pivot = pivot->next;
	}
	return (NULL);
}

char	**hashtable_to_array(void)
{
	int		env_vars_count;
	int		i;
	int		j;
	t_list	*pivot;
	char	**hashtable_arr;

	env_vars_count = count_env_vars();
	hashtable_arr = (char **) malloc((env_vars_count + 1) * sizeof(char *));
	hashtable_arr[env_vars_count] = NULL;
	i = -1;
	j = -1;
	while (++i < TABLE_SIZE)
	{
		pivot = g_tudao.hashtable[i];
		while (pivot)
		{
			hashtable_arr[++j] = \
				env_var_to_string((t_env_var *) pivot->content);
			pivot = pivot->next;
		}
	}
	return (hashtable_arr);
}
