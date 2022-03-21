/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:15:44 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/03/21 19:09:05 by adrianofaus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_escape_sequence(char c)
{
	if (c == 't' || c == 'b' || c == 'n' \
		|| c == 'r' || c == 'f')
		return (true);
	return (false);
}

void	builtin_echo(char *str)
{
	int	index;
	int	flag;

	index = 0;
	flag = 0;
	while (str[index])
	{
		if (str[index] == '\\')
		{
			if (str[(index + 1)] == '\\')
		}
			flag++;
		else
		{
			if (is_escape_sequence(str[index]) && flag == 2)
				process_backslash(str[index]);
			else if (ft_isdigit(str[index]))
				ft_putnbr_fd(str[index], 1);
			else
				ft_putchar_fd(str[index], 1);
			flag = 0;
		}
		index++;
	}
}