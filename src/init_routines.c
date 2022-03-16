/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_routines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:08:00 by roaraujo          #+#    #+#             */
/*   Updated: 2022/03/15 22:17:09 by adrianofaus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_hashtable(t_list *(*hashtable)[TABLE_SIZE])
{
	int	i;

	i = -1;
	while (++i < TABLE_SIZE)
	{
		(*hashtable)[i] = NULL;
	}
	return ;
}

void	init_tudao(void)
{
	g_tudao.token_list = NULL;
	g_tudao.command_table.has_and_operator = false;
	g_tudao.command_table.has_or_operator = false;
	return ;
}
