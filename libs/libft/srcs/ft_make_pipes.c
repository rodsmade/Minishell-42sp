/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:38:02 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/04/07 23:56:04 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	**ft_make_pipes(int total_pipes)
{
	int	i;
	int	**pipes;

	if (total_pipes == 0)
		return (NULL);
	pipes = (int **)malloc(total_pipes * sizeof(int *));
	if (!pipes)
	{
		ft_putendl_fd("Malloc error", 2);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < total_pipes)
	{
		pipes[i] = (int *)malloc(2 * sizeof(int));
		if (!pipes[i])
		{
			ft_putendl_fd("Malloc error", 2);
			exit(EXIT_FAILURE);
		}
		pipe(pipes[i]);
		i++;
	}
	return (pipes);
}
