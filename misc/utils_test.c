/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 22:15:02 by roaraujo          #+#    #+#             */
/*   Updated: 2022/03/28 21:03:39 by adrianofaus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_hashtable(t_list *(*hashtable)[TABLE_SIZE])
{
	int		i;
	t_list	*pivot;

	i = -1;
	while (++i < TABLE_SIZE)
	{
		pivot = (*hashtable)[i];
		printf("%d\t: ", i);
		while (pivot != NULL)
		{
			printf("{nome: %s, value: %s}", \
			((t_env_var *)(pivot->content))->key, \
			((t_env_var *)(pivot->content))->value);
			if (pivot->next != NULL)
				printf(",\n\t  ");
			pivot = pivot->next;
		}
		printf("\n");
	}
	return ;
}
