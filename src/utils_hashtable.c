/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_hashtable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 20:14:20 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/03/22 20:20:18 by adrianofaus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_hashtable(char *key, char *new_value)
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
		g_tudao.hashtable[index]->content)->name, key, len) == 0)
		{
			ft_free_ptr((void *)&(((t_env_var *) \
			g_tudao.hashtable[index]->content)->value));
			((t_env_var *) \
			g_tudao.hashtable[index]->content)->value = ft_strdup(new_value);
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
		if (ft_strncmp(((t_env_var *)pivot->content)->name, key, len) == 0)
			return (((t_env_var *)pivot->content)->value);
		pivot = pivot->next;
	}
	return (NULL);
}
