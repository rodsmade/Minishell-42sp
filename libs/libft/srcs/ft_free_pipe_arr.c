/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_pipe_arr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:33:19 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/04/07 17:37:53 by adrianofaus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_pipe_arr(int ***pipe_arr, int n)
{
	int	i;

	i = -1;
	if (*pipe_arr)
	{
		while (++i < n)
		{
			if ((*pipe_arr)[i])
			{
				close((*pipe_arr)[i][0]);
				close((*pipe_arr)[i][1]);
				ft_free_ptr((void *)&(*pipe_arr)[i]);
			}
		}
		ft_free_ptr((void *)&(*pipe_arr));
	}
	return ;
}
