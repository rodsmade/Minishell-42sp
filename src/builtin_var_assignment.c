/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_var_assignment.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 00:34:57 by roaraujo          #+#    #+#             */
/*   Updated: 2022/03/24 20:03:32 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_vars(t_command *command)
/**
 * NOK.
 * TODO: lembrar de setar o is_env pra false! ñ esquecer
 */
{
	t_list	*pivot;

	pivot = command->cmds_with_flags;
	while (pivot)
	{
		printf("this is a variable assignment\n");
		pivot = pivot->next;
	}
	return ;
}

static bool	is_var_assignment(char *str)
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

bool	has_only_var_assignments(t_list *pipeline)
{
	t_list	*pivot;

	pivot = ((t_command *)pipeline->content)->cmds_with_flags;
	while (pivot)
	{
		if (!is_var_assignment(pivot->content))
			return (false);
		pivot = pivot->next;
	}
	return (true);
}
