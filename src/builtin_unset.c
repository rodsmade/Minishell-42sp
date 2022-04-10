/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 20:15:11 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/10 23:12:11 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lst_free_node(t_list *node)
{
	ft_free_ptr((void *)&((t_env_var *) node->content)->key);
	ft_free_ptr((void *)&((t_env_var *) node->content)->value);
	ft_free_ptr(&node->content);
	ft_free_ptr(&node->content);
	ft_free_ptr((void *)&node);
	node = NULL;
	return ;
}

void	delete_node(t_list *hashtable_pvt, t_list *node_to_delete,
	char *var_name)
{
	if (hashtable_pvt == node_to_delete)
	{
		g_tudao.hashtable[hash_string(var_name)] = \
				g_tudao.hashtable[hash_string(var_name)]->next;
		ft_lst_free_node(node_to_delete);
		return ;
	}
	while (hashtable_pvt)
	{
		if (hashtable_pvt->next == node_to_delete)
		{
			hashtable_pvt->next = node_to_delete->next;
			ft_lst_free_node(node_to_delete);
			return ;
		}
		hashtable_pvt = hashtable_pvt->next;
	}
}

void	builtin_unset(t_list *cmd_with_args)
{
	char	*var_name;
	t_list	*node_to_delete;
	t_list	*pivot;

	if (!cmd_with_args->next)
		return ;
	pivot = cmd_with_args->next;
	while (pivot)
	{
		var_name = (char *) pivot->content;
		if (is_valid_identifier(var_name))
		{
			node_to_delete = find_node_in_hashtable(var_name);
			if (node_to_delete)
				delete_node(g_tudao.hashtable[hash_string(var_name)],
					node_to_delete, var_name);
		}
		else
		{
			ft_putendl_fd(ft_strjoin_3("minishell: unset: `", var_name,
					"': not a valid identifier"), 2);
			return ;
		}
		pivot = pivot->next;
	}
}
