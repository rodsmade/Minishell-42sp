/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 20:15:11 by roaraujo          #+#    #+#             */
/*   Updated: 2022/03/26 01:21:51 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lst_free_node(t_list *node)
{
	ft_free_ptr((void *)&((t_env_var *) node->content)->name);
	ft_free_ptr((void *)&((t_env_var *) node->content)->value);
	ft_free_ptr(&node->content);
	ft_free_ptr(&node->content);
	ft_free_ptr((void *)&node);
	node = NULL;
	return ;
}

void	find_node_and_delete(t_list *pivot, t_list *node_to_delete,
	char *var_name)
{
	if (pivot == node_to_delete)
	{
		g_tudao.hashtable[hash_string(var_name)] = \
				g_tudao.hashtable[hash_string(var_name)]->next;
		ft_lst_free_node(node_to_delete);
		return ;
	}
	while (pivot)
	{
		if (pivot->next == node_to_delete)
		{
			pivot->next = node_to_delete->next;
			ft_lst_free_node(node_to_delete);
			return ;
		}
		pivot = pivot->next;
	}
}

void	builtin_unset(t_list *cmd_with_args)
{
	char	*var_name;
	t_list	*node_to_delete;
	t_list	*pivot;

	if (!cmd_with_args->next)
		return ;
	var_name = (char *) cmd_with_args->next->content;
	node_to_delete = find_node_in_hashtable(var_name);
	if (!node_to_delete)
		return ;
	pivot = g_tudao.hashtable[hash_string(var_name)];
	find_node_and_delete(pivot, node_to_delete, var_name);
	return ;
}
