/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_pipe_fds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 22:10:34 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/07 22:11:37 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_close_pipe_fds(int *pipe)
{
	if (pipe)
	{
		close(pipe[0]);
		close(pipe[1]);
	}
	return ;
}
