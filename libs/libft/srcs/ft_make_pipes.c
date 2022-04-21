/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:38:02 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/04/22 00:33:09 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_previous_pipes(int ***pipes_arr, int i)
{
	while (--i >= 0)
		ft_free_ptr((void *)pipes_arr[i]);
	return ;
}

int	**ft_make_pipes(int total_pipes)
{
	int	i;
	int	**pipes_arr;

	if (total_pipes == 0)
		return (NULL);
	pipes_arr = (int **)malloc(total_pipes * sizeof(int *));
	if (!pipes_arr)
		return (NULL);
	i = -1;
	while (++i < total_pipes)
	{
		pipes_arr[i] = (int *)malloc(2 * sizeof(int));
		if (!pipes_arr[i] || !pipe(pipes_arr[i]))
		{
			free_previous_pipes(&pipes_arr, i);
			return (NULL);
		}
	}
	return (pipes_arr);
}
