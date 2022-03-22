/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:15:44 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/03/21 23:59:48 by adrianofaus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_backslash_sequence(char *str)
{
	int	i;

	i = 0;
	if (str[i + 1])
	{
		i++;
		if (str[i] == 't')
			write(1, "\t", 1);
		else if (str[i] == 'b')
			write(1, "\b", 1);
		else if (str[i] == 'n')
			write(1, "\n", 1);
		else if (str[i] == 'r')
			write(1, "\r", 1);
		else if (str[i] == 'f')
			write(1, "\f", 1);
		else
			ft_putchar_fd(str[i], 1);
		return (i);
	}
	ft_putchar_fd('\\', 1);
	return (0);
}

void	process_str(char *str)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if (str[index] == '\\' && str[index + 1])
		{
			index++;
			if (str[index] == '\\')
				index += process_backslash_sequence(&str[index]);
		}
		else
		{
			ft_putchar_fd(str[index], 1);
			index++;
		}
	}
}

// void	builtin_echo(t_list *lst)
// {
// 	t_list	*pivot;
// 	int		option;
	
// 	pivot = lst;
// 	option = 0;
// 	while (pivot != NULL)
// 	{
// 		if (!ft_strncmp((char *)pivot->content, "-n", 3))
// 			option = 1;
// 		else
// 			process_str((char *)pivot->content);
// 		pivot = pivot->next;
// 	}
// 	if (!option)
// 		write(1, "\n", 1);
// }

void	builtin_echo(char *lst)
{
	int		option;
	
	option = 0;
	if (!ft_strncmp(&lst[5], "-n", 2))
		option = 1;
	if (option)
	{
		// process_str(&lst[8]);
		printf("%s", &lst[8]);
	}
	else
	{
		// process_str(&lst[5]);
		printf("%s\n", &lst[5]);
	}
}