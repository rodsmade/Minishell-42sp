/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:50:53 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/03/28 14:53:50 by adrianofaus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	iter_quoted_value(char *line_read, int *i, char *value, int *j)
{
	char	qtype;

	qtype = line_read[(*i)];
	*i = *i + 1;
	while (line_read[*i] != qtype && line_read[(*i)] && line_read[(*i)] != '=')
	{
		value[(*j)] = line_read[(*i)];
		*i = *i + 1;
		*j = *j + 1;
	}
}
