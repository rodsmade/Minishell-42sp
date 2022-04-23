/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:15:44 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/04/23 00:25:01 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_echo(t_list *lst)
{
	t_list	*pivot;
	int		option;

	pivot = lst->next;
	option = 0;
	if (pivot != NULL && pivot->content != NULL)
	{
		if (!ft_strncmp((char *)pivot->content, "-n", 3))
		{
			option = 1;
			pivot = pivot->next;
		}
		while (pivot != NULL)
		{
			ft_putstr_fd((char *) pivot->content, 1);
			if (pivot->next != NULL)
				ft_putchar_fd(' ', 1);
			pivot = pivot->next;
		}
	}
	if (!option)
		ft_putchar_fd('\n', 1);
	g_tudao.exit.code = 0;
}
