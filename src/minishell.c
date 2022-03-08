/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 21:30:44 by roaraujo          #+#    #+#             */
/*   Updated: 2022/03/07 22:01:40 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	main(int argc, char *argv[])
{
	char	*line_read;

	(void)argv;
	line_read = NULL;
	if (argc != 1)
		return (1);
	write(1, "Hello World !\n", 14);
	while (1)
	{
		if (line_read)
			ft_free_ptr((void *)&line_read);
		line_read = readline("Type yr command (type \'quit\' to exit): ");
		add_history(line_read);
		if (ft_strncmp(line_read, "quit", 5) == 0)
			break ;
	}
	ft_free_ptr((void *)&line_read);
	rl_clear_history();
	close(0);
	close(1);
	close(2);
	return (0);
}
