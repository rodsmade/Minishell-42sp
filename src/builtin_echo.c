/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:15:44 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/04/20 22:20:17 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_echo(t_list *lst)
{
	t_list	*pivot;
	int		option;

	pivot = lst->next;
	option = 0;
	if (pivot != NULL && !ft_strncmp((char *)pivot->content, "-n", 3))
	{
		option = 1;
		pivot = pivot->next;
	}
	while (pivot != NULL)
	{
		ft_putstr_fd((char *) pivot->content, 1);
		ft_putchar_fd(' ', 1);
		pivot = pivot->next;
	}
	if (!option)
		write(1, "\n", 1);
	g_tudao.ext_routine.code = 0;
}
