/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:15:44 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/03/22 11:29:17 by adrianofaus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_str(char *str)
{
	int		index;
	char	quote_type;

	index = 0;
	while (str[index])
	{
		if (str[index] == 39 || str[index] == 34)
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
}

void	builtin_echo(t_list *lst)
{
	t_list	*pivot;
	int		option;
	
	pivot = lst;
	option = 0;
	while (pivot != NULL)
	{
		if (!ft_strncmp((char *)pivot->content, "-n", 3))
			option = 1;
		else
			process_str((char *)pivot->content);
		pivot = pivot->next;
	}
	if (!option)
		write(1, "\n", 1);
}

// void	builtin_echo(char *lst) Teste with string
// {
// 	int		option;
	
// 	option = 0;
// 	if (!ft_strncmp(&lst[5], "-n", 2))
// 		option = 1;
// 	if (option)
// 	{
// 		process_str(&lst[8]);
// 		// printf("%s", &lst[8]);
// 	}
// 	else
// 	{
// 		process_str(&lst[5]);
// 		write(1, "\n", 1);
// 		// printf("%s\n", &lst[5]);
// 	}
// }