/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_signals_omg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 03:27:44 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/14 20:40:02 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	catch_sigquit(int sig_code)
{
	printf("Isto foi chamado dentro de um pai\n");
	printf("processo: %i\n", getpid());
	printf("sigcode: %i\n", sig_code);
	printf("SIGINT: %i\n", SIGINT);
	return ;
}

void	catch_sigquit_child(int sig_code)
{
	printf("Isto foi chamado dentro de um filho\n");
	printf("processo: %i\n", getpid());
	printf("sigcode: %i\n", sig_code);
	printf("SIGINT: %i\n", SIGINT);
	return ;
}

void	reset_signal(int signal, struct sigaction *act)
{
	act->sa_handler = SIG_IGN;
	sigaction(signal, act, NULL);
	return ;
}

void	set_signal(int signal, void handler(int), struct sigaction *act)
{
	act->sa_handler = handler;
	act->sa_flags = SA_RESTART;
	sigemptyset(&(act->sa_mask));
	sigaction(signal, act, NULL);
	return ;
}


int main(void)
{
	char				*str;
	struct sigaction	act;
	t_command			*cmd;
	int pid;

	// act.sa_handler = catch_sigquit;
	// act.sa_flags = SA_RESTART;
	// sigemptyset(&act.sa_mask);
	// sigaction(SIGINT, &act, NULL);
	set_signal(SIGINT, &catch_sigquit, &act);
	printf("vem aí \n");
	str = readline("> ");
	printf("ponteiro do string: %p\n", str);
	printf("seu string sr: %s\n", str);
	free(str);
	reset_signal(SIGINT, &act);
	pid = fork();
	if (pid == 0)
	{
		// act.sa_handler = catch_sigquit_child;
		// act.sa_flags = SA_RESTART;
		// sigemptyset(&act.sa_mask);
		// sigaction(SIGINT, &act, NULL);
		set_signal(SIGINT, &catch_sigquit_child, &act);
		write(1, "entrou no filho\n", 16);
		str = readline("dentro do fork: ");
		if (str)
		{
			write(1, str, ft_strlen(str));
			write(1, "\n", 1);
			free(str);
		}
		else
		{
			ft_putendl_fd("bash: warning: here-document at line 1 delimited by end-of-file (wanted `heredoc')", 2);
		}
		return (0);
	}
	wait(NULL);
	set_signal(SIGINT, &catch_sigquit, &act);
	ft_putendl_fd("voltou pro processo pai", 1);
	str = readline("que mais? ");
	printf("ponteiro do string: %p\n", str);
	printf("string em questão: %s\n", str);
	free(str);
	return (0);
}
