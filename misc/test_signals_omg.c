/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_signals_omg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 03:27:44 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/14 04:26:17 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	catch_sigquit(int sig_code)
{
	printf("capturou o quit hein\n");
	printf("sigcode: %i\n", sig_code);
	printf("SIGINT: %i\n", SIGINT);
	return ;
}

int main(void)
{
	char		*str;
	struct sigaction	act;
	t_command	*cmd;

	act.sa_handler = catch_sigquit;
	sigaction(SIGINT, &act, NULL);
	printf("vem aí \n");
	str = readline("> ");
	printf("seu string sr: %s\n", str);
	return (0);
}
