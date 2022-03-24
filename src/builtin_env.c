/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:53:54 by afaustin          #+#    #+#             */
/*   Updated: 2022/03/23 19:04:21 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_env(void)
{
	int		i;
	t_list	*aux;

	i = -1;
	while (++i < TABLE_SIZE)
	{
		aux = g_tudao.hashtable[i];
		while (aux != NULL)
		{
			if (((t_env_var *)(aux->content))->is_env_var == true)
			{
				ft_putstr_fd(((t_env_var *)(aux->content))->name, \
				STDOUT_FILENO);
				write(STDOUT_FILENO, "=", 1);
				if (((t_env_var *)(aux->content))->value)
					ft_putstr_fd(((t_env_var *)(aux->content))->value, \
					STDOUT_FILENO);
				write(STDOUT_FILENO, "\n", 1);
			}
			aux = aux->next;
		}
	}
}
