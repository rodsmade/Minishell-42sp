/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_var_assignment.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 00:34:57 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/01 20:21:37 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_new_local_env_var(t_list *var)
{
	(void) var;
	return ;
}

void	assign_vars(t_command *command)
/**
 * NOK.
 * TODO: lembrar de setar o is_env pra false! ñ esquecer
 */
{
	t_list	*pivot;
	t_list	*temp;
	t_list	**lst_head;

	lst_head = &command->cmds_with_flags;
	pivot = *lst_head;
	while (pivot && is_var_assignment(pivot->content))
	{
		printf("%s: this is a variable assignment\n", (char *) pivot->content);
		create_new_local_env_var(pivot);
		temp = pivot->next;
		ft_lst_remove_node(lst_head, pivot);
		pivot = temp;
	}
	return ;
}

bool	is_var_assignment(char *str)
{
	int	equal_sign;

	equal_sign = 0;
	if (!str)
		return (false);
	while (*str)
	{
		if (*str == '=')
			equal_sign++;
		str++;
	}
	if (equal_sign != 1)
		return (false);
	else
		return (true);
}
