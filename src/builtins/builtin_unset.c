/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 20:15:11 by roaraujo          #+#    #+#             */
/*   Updated: 2022/05/10 17:41:20 by coder            ###   ########.fr       */
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
		g_data.hashtable[hash_string(var_name)] = \
				g_data.hashtable[hash_string(var_name)]->next;
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
	t_list	*pivot;

	if (!cmd_with_args->next)
		return ;
	pivot = cmd_with_args->next;
	while (pivot)
	{
		var_name = (char *) pivot->content;
		if (is_valid_identifier(var_name))
		{
			if (find_node_in_hashtable(var_name))
				delete_node(g_data.hashtable[hash_string(var_name)],
					find_node_in_hashtable(var_name), var_name);
		}
		else
		{
			g_data.exit.msg = ft_strjoin_3("unset: `", var_name,
					"': not a valid identifier");
			g_data.exit.code = EXIT_FAILURE;
			return ;
		}
		pivot = pivot->next;
	}
}
