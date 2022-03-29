/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:15:44 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/03/23 23:18:44 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_arg(char *str)
{
	int		index;
	char	quote_type;

	index = 0;
	while (str[index])
	{
		if (str[index] == '\'' || str[index] == '\"')
		{
			quote_type = str[index];
			index++;
			while (str[index] && str[index] != quote_type)
			{
				ft_putchar_fd(str[index], 1);
				index++;
			}
		}
		else
		{
			ft_putchar_fd(str[index], 1);
			index++;
		}
	}
	ft_putchar_fd(' ', 1);
}

void	builtin_echo(t_list *lst)
{
	t_list	*pivot;
	int		option;

	pivot = lst->next;
	option = 0;
	while (pivot != NULL)
	{
		if (!ft_strncmp((char *)pivot->content, "-n", 3))
			option = 1;
		else
			print_arg((char *)pivot->content);
		pivot = pivot->next;
	}
	if (!option)
		write(1, "\n", 1);
}
