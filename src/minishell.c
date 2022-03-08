/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 21:30:44 by roaraujo          #+#    #+#             */
/*   Updated: 2022/03/07 21:11:15 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	main(void)
{
	char	*line_read;

	line_read = NULL;
	write(1, "Hello World !\n", 14);

	line_read = readline("Type yr command: ");
	add_history(line_read);
	printf("Line read: %s\n", line_read);
	free(line_read);
	
	line_read = readline("Type yr command: ");
	add_history(line_read);
	printf("Line read: %s\n", line_read);
	free(line_read);
	
	line_read = readline("Type yr command: ");
	add_history(line_read);
	printf("Line read: %s\n", line_read);
	free(line_read);

	rl_clear_history();
	close(0);
	close(1);
	close(2);

	return (0);
}
