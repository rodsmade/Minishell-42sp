/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 20:40:41 by roaraujo          #+#    #+#             */
/*   Updated: 2022/03/08 19:42:00 by adrianofaus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_arr(void ***arr)
{
	int	i;

	i = -1;
	while ((*arr)[++i])
	{
		ft_free_ptr((void *)&(*arr)[i]);
		(*arr)[i] = NULL;
	}
	free(*arr);
}
