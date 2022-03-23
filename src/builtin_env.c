/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 12:45:49 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/03/23 15:34:00 by adrianofaus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_env(void)
{
	// int		i;
	// t_list	*aux;

	// i = -1;
	// while (++i < TABLE_SIZE)
	// {
	// 	aux = g_tudao.hashtable[i];
	// 	printf("%d\t: ", i);
	// 	while (aux != NULL)
	// 	{
	// 		printf("{nome: %s, value: %s}",
	// 			((t_env_var *)(aux->content))->name,
	// 			((t_env_var *)(aux->content))->value);
	// 		if (aux->next != NULL)
	// 			printf(",\n\t ");
	// 		aux = aux->next;
	// 	}
	// 	printf("\n");
	// }
	int		i;
	t_list	*aux;

	i = -1;
	while (++i < TABLE_SIZE)
	{
		aux = g_tudao.hashtable[i];
		while (aux != NULL)
		{
				ft_putstr_fd(((t_env_var *)(aux->content))->name, STDOUT_FILENO);
				write(STDOUT_FILENO, "=", 1);
				//check if value is null
				ft_putstr_fd(((t_env_var *)(aux->content))->value, STDOUT_FILENO);
				write(STDOUT_FILENO, "\n", 1);
			aux = aux->next;
		}
	}
	return ;	
}