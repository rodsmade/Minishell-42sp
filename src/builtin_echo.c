/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:15:44 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/04/22 19:07:48 by coder            ###   ########.fr       */
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
		if ((pivot->next != NULL && !option) || option == 1)
		{
			ft_putstr_fd((char *) pivot->content, 1);
			if (pivot->next != NULL)
				ft_putchar_fd(' ', 1);
		}
		else
			ft_putendl_fd((char *) pivot->content, 1);
		pivot = pivot->next;
	}
	g_tudao.exit.code = 0;
}
