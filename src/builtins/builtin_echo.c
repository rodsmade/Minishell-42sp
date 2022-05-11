/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:15:44 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/05/11 20:47:39 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_echo_arg(t_list *pivot)
{
	if (pivot->content)
	{
		ft_putstr_fd((char *) pivot->content, 1);
		if (pivot->next != NULL)
			ft_putchar_fd(' ', 1);
	}
	return ;
}

void	builtin_echo(t_list *lst)
{
	t_list	*pivot;
	int		option;

	pivot = lst->next;
	option = 0;
	if (pivot != NULL)
	{
		if (pivot->content != NULL
			&& !ft_strncmp((char *)pivot->content, "-n", 3))
		{
			option = 1;
			pivot = pivot->next;
		}
		while (pivot != NULL)
		{
			print_echo_arg(pivot);
			pivot = pivot->next;
		}
	}
	if (!option)
		ft_putchar_fd('\n', 1);
}
