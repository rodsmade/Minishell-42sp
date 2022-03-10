/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 22:15:02 by roaraujo          #+#    #+#             */
/*   Updated: 2022/03/10 11:51:53 by roaraujo         ###   ########.fr       */
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
			printf("{nome: %s, value: %s}",
				((t_env_var *)(pivot->content))->name,
				((t_env_var *)(pivot->content))->value);
			if (pivot->next != NULL)
				printf(",\n\t  ");
			pivot = pivot->next;
		}
		printf("\n");
	}
	return ;
}
